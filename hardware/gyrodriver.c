// https://www.codeproject.com/Articles/1032794/Simple-I-O-device-driver-for-RaspberryPi
// http://ozzmaker.com/berryimu/
// Hello
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alejandro Dominguez");
MODULE_DESCRIPTION("A device driver to simplify reading from the gyroscope.");
MODULE_VERSION("1.0.0");
MODULE_SUPPORTED_DEVICE("RaspberryPI Model B");

#define DEVICE_NAME "gyrodriver"
#define CLASS_NAME "gyro"

static struct class*	gyroClass  = NULL;
static struct device* gyroDevice = NULL;

int register_device(void);
static int gyro_open(struct inode *i, struct file *f);
static ssize_t gyro_read(struct file *, char *, size_t, loff_t *);
static ssize_t gyro_write(struct file *, const char *, size_t, loff_t *);

struct file_operations fops = {
    .open = gyro_open,
    .read = gyro_read,
	 .write = gyro_write
};

static int __init gyro_init(void)
{
   if(!register_device()){
      printk(KERN_INFO "[GYRODRIVER]: All things registered correctly.");
   }
   return 0;
}

static void __exit gyro_exit(void)
{
   device_destroy(rootkitClass, MKDEV(majorNumber, 0));     // remove the device
	class_unregister(rootkitClass);                          // unregister the device class
	class_destroy(rootkitClass);                             // remove the device class
	unregister_chrdev(majorNumber, DEVICE_NAME);             // unregister the major number
	printk(KERN_INFO "[GYRODRIVER]: Et tu, Brute.\n");
   return;
}

module_init(gyro_init);
module_exit(gyro_exit);

int register_device(void)
{
   printk(KERN_INFO "[GYRODRIVER]: Device Driver has been called.");
	
	majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
	if (majorNumber<0){
		printk(KERN_ALERT "[GYRODRIVER]: Failed to register a major number\n");
		return majorNumber;
	}
	else printk(KERN_INFO "[GYRODRIVER]: Registered correctly with major number %d\n", majorNumber);
	
	gyroClass = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(gyroClass)){                // Check for error and clean up if there is
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "[GYRODRIVER]: Failed to register device class\n");
		return PTR_ERR(gyroClass);          // Correct way to return an error on a pointer
	}	
	else printk(KERN_INFO "[GYRODRIVER]: Device class registered correctly\n");
	
	gyroDevice = device_create(gyroClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
	if (IS_ERR(gyroDevice)){               // Clean up if there is an error
		class_destroy(gyroClass);           // Repeated code but the alternative is goto statements
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "[GYRODRIVER]: Failed to create the device\n");
		return PTR_ERR(gyroDevice);
	}
	else printk(KERN_INFO "[GYRODRIVER]: Device class created correctly\n");

   return 0;
}

static int gyro_open(struct inode *i, struct file *f)
{
   printk(KERN_INFO "[GYRODRIVER]: Device opened succesfully.");
   return 0;
}

static ssize_t gyro_read(struct file *filep, char *buffer, size_t len, loff_t *offset) // not done
{
	int error_count = 0;
   // copy_to_user has the format ( * to, *from, size) and returns 0 on success
   error_count = copy_to_user(buffer, message, size_of_message);
 
   if (error_count==0){            // if true then have success
      printk(KERN_INFO "TESTChar: Sent %d characters to the user\n", size_of_message);
      return (size_of_message=0);  // clear the position to the start and return 0
   }
   else {
      printk(KERN_INFO "TESTChar: Failed to send %d characters to the user\n", error_count);
      return -EFAULT;              // Failed -- return a bad address message (i.e. -14)
   }
}

static ssize_t gyro_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) // not done
{
	sprintf(message, "%s(%lu letters)", buffer, len);   // appending received string with its length, We use %lu because len is a size_t 
   size_of_message = strlen(message);                 // store the length of the stored message
   printk(KERN_INFO "TESTChar: Received %lu characters from the user\n", len); // We use %lu because len is an long unsigned int
   return len;
}