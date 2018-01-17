# Import Required Libraries
import math
from smbus import SMBus
import time

# Defining required functions
def twos_comp_combine(msb, lsb):
        twos_comp = 256*msb + lsb
        if twos_comp >= 32768:
            return twos_comp - 65536
        else:
            return twos_comp

# set I2C bus
busNum = 1
bus = SMBus(busNum)

LSM = 0x1d

LSM_WHOAMI = 0b1001001 #Device self-id

#Define Initial Complementary Angle Variables
CF_X_deg = 0
CF_Y_deg = 0
CF_Z_deg = 0

# Define Rotation Angles
Gyro_X_deg = 0
Gyro_Y_deg = 0
Gyro_Z_deg = 0

Gyro_Sens = 0.00875 # Define Gyro Sensitivity Value
Acc_Sens = 0.000061 # Define Accelerometer Sensitiviy Value
Loop_time = 0.01 # Estimated Loop Time

 #Control register addresses -- from LSM303D datasheet

CTRL_0 = 0x1F #General settings
CTRL_1 = 0x20 #Turns on accelerometer and configures data rate
CTRL_2 = 0x21 #Self test accelerometer, anti-aliasing accel filter
CTRL_3 = 0x22 #Interrupts
CTRL_4 = 0x23 #Interrupts
CTRL_5 = 0x24 #Turns on temperature sensor
CTRL_6 = 0x25 #Magnetic resolution selection, data rate config
CTRL_7 = 0x26 #Turns on magnetometer and adjusts mode

#Registers holding twos-complemented MSB and LSB of magnetometer readings -- from LSM303D datasheet
MAG_X_LSB = 0x08 # x
MAG_X_MSB = 0x09
MAG_Y_LSB = 0x0A # y
MAG_Y_MSB = 0x0B
MAG_Z_LSB = 0x0C # z
MAG_Z_MSB = 0x0D

#Registers holding twos-complemented MSB and LSB of magnetometer readings -- from LSM303D datasheet
ACC_X_LSB = 0x28 # x
ACC_X_MSB = 0x29
ACC_Y_LSB = 0x2A # y
ACC_Y_MSB = 0x2B
ACC_Z_LSB = 0x2C # z
ACC_Z_MSB = 0x2D

#Registers holding 12-bit right justified, twos-complemented temperature data -- from LSM303D datasheet
TEMP_MSB = 0x05
TEMP_LSB = 0x06


if bus.read_byte_data(LSM, 0x0f) == LSM_WHOAMI:
        print 'LSM303D detected successfully.'
else:
        print 'No LSM303D detected on bus '+str(busNum)+'.'

bus.write_byte_data(LSM, CTRL_1, 0b1010111) # enable accelerometer, 50 hz sampling
bus.write_byte_data(LSM, CTRL_2, 0x00) #set +/- 2g full scale
bus.write_byte_data(LSM, CTRL_5, 0b01100100) #high resolution mode, thermometer off, 6.25hz ODR
bus.write_byte_data(LSM, CTRL_6, 0b00100000) # set +/- 4 gauss full scale
bus.write_byte_data(LSM, CTRL_7, 0x00) #get magnetometer out of low power mode

# I2C Connection
L3G = 0x6b

L3G_WHOAMI = 0b11010111


#defining the control registers from L3GD20H Datasheet

CTRL_GYRO_1 = 0x20 #Page 36 of Datasheet
CTRL_GYRO_2 = 0x21 #Page 38
CTRL_GYRO_3 = 0x22 #Page 39
CTRL_GYRO_4 = 0x23 #Page 39
CTRL_GYRO_5 = 0x24 #Page 40
CTRL_GYRO_6 = 0x39 #Page 48


#Registers holding twos complement gyro values

GYRO_X_LSB = 0x28
GYRO_X_MSB = 0x29

GYRO_Y_LSB = 0x2A
GYRO_Y_MSB = 0x2B

GYRO_Z_LSB = 0x2C
GYRO_Z_MSB = 0x2D

#Temperature Data
TEMP_Out = 0x26

# Writing required settings to Gyro
if bus.read_byte_data(L3G, 0x0f) == L3G_WHOAMI:
    print 'L3GD20H successfully detected'
else:
    print 'L3GD20H not detected'

bus.write_byte_data(L3G, CTRL_GYRO_1, 0b00001111) #enable x,y,z; choose frequency and bandwidth
bus.write_byte_data(L3G, CTRL_GYRO_2, 0x00) # sets high pass filter
bus.write_byte_data(L3G, CTRL_GYRO_6, 0b000000) # sets LOW_ODR


while True:

        start_time = time.time() # used to define loop time

        # reading accelerometer values
        accx = twos_comp_combine(bus.read_byte_data(LSM, ACC_X_MSB), bus.read_byte_data(LSM, ACC_X_LSB))
        accy = twos_comp_combine(bus.read_byte_data(LSM, ACC_Y_MSB), bus.read_byte_data(LSM, ACC_Y_LSB))
        accz = twos_comp_combine(bus.read_byte_data(LSM, ACC_Z_MSB), bus.read_byte_data(LSM, ACC_Z_LSB))

        #reading results from gyroscope
        gyrox = twos_comp_combine(bus.read_byte_data(L3G, GYRO_X_MSB), bus.read_byte_data(L3G, GYRO_X_LSB))
        gyroy = twos_comp_combine(bus.read_byte_data(L3G, GYRO_Y_MSB), bus.read_byte_data(L3G, GYRO_Y_LSB))
        gyroz = twos_comp_combine(bus.read_byte_data(L3G, GYRO_Z_MSB), bus.read_byte_data(L3G, GYRO_Z_LSB))

        #Define Accelerometer readings in g
        Acc_X_G = accx*Acc_Sens
        Acc_Y_G = accy*Acc_Sens
        Acc_Z_G = accz*Acc_Sens

        #Define Gyro Readings in dps
        Gyro_X_dps = gyrox*Gyro_Sens
        Gyro_Y_dps = gyroy*Gyro_Sens
        Gyro_Z_dps = gyroz*Gyro_Sens

        #Define Gyro Readings in degrees after each time iteration
        Gyro_X_increment = -Gyro_X_dps*Loop_time
        Gyro_Y_increment = -Gyro_Y_dps*Loop_time
        Gyro_Z_increment = -Gyro_Z_dps*Loop_time

        #Gyro Angle Values
        Gyro_X_deg += Gyro_X_increment
        Gyro_Y_deg += Gyro_Y_increment
        Gyro_Z_deg += Gyro_Z_increment

        #Angle from Accelerometer Readings
        Acc_X_deg = math.degrees(math.atan2(Acc_Y_G, Acc_Z_G))
        Acc_Y_deg = math.degrees(math.atan2(Acc_Z_G, Acc_X_G))
        Acc_Z_deg = math.degrees(math.atan2(Acc_X_G, Acc_Y_G))

        #Change Rotation Values of Accelerometer to +/- 180
        if(Acc_X_deg > 180):
            Acc_X_deg -= 360
        if(Acc_Y_deg > 180):
            Acc_Y_deg -= 360
        if(Acc_Z_deg > 180):
            Acc_Z_deg -= 360


        # Complementary Filter for Angle Values
        CF_X_deg = 0.98*(CF_X_deg + Gyro_X_increment) + (1-0.98)*Acc_X_deg
        CF_Y_deg = 0.98*(CF_Y_deg + Gyro_Y_increment) + (1-0.98)*Acc_Y_deg

        # note that it will take a few seconds before accurate results are obtained

        # Gyro offset should also be measured and accounted for
        # however this will vary from case to case so has not been done here
        print "Rotation about the x-axis is", CF_X_deg
        print "Rotation about the y-axis is", CF_Y_deg
        while ((time.time()-start_time) < 0.01):
            # sleeping until a time of 0.01 to keep loop time constant
            time.sleep(0.0005)

        end_time = time.time()

        Loop_time = end_time - start_time
        print Loop_time