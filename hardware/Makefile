CC = g++
LIB = lib/
SRC = src/
OBJ = build/
INC = include/
CFLAGS = -O2 -g
LIBINSTALLDIR = /usr/local/lib
INCLUDEINSTALLDIR = /usr/local/include

PROJ = ExoHAI

.PHONY: $(PROJ)
$(PROJ): $(LIB)liblsm9ds1.a $(LIB)liblsm9ds1.so $(LIB)liblsm9ds1cwrapper.so


$(OBJ)LSM9DS1.o: $(SRC)LSM9DS1.cpp
	$(CC) -I$(INC) -Wall -O2 -fPIC -c -lwiringPi $(SRC)LSM9DS1.cpp -o $(OBJ)LSM9DS1.o


# static library
$(LIB)liblsm9ds1.a: $(OBJ)LSM9DS1.o
	mkdir -p $(LIB)
	ar rcs $(LIB)liblsm9ds1.a $(OBJ)LSM9DS1.o

# dynamic library
$(LIB)liblsm9ds1.so: $(OBJ)LSM9DS1.o
	mkdir -p $(LIB)
	$(CC) -I$(INC) -Wall -O2 -fexceptions $(SRC)LSM9DS1.cpp -lwiringPi -shared -o $(LIB)liblsm9ds1.so
 
$(OBJ)LSM9DS1_c_wrapper.o: $(SRC)LSM9DS1_c_wrapper.cpp
	$(CC) -I$(INC) -Wall -O2 -fPIC -c -lwiringPi $(SRC)LSM9DS1_c_wrapper.cpp -o $(OBJ)LSM9DS1_c_wrapper.o


$(LIB)liblsm9ds1cwrapper.so: $(OBJ)LSM9DS1_c_wrapper.o $(OBJ)LSM9DS1.o
	mkdir -p $(LIB)
	$(CC) -I$(INC) -Wall -O2 -shared -lwiringPi $(OBJ)LSM9DS1.o $(OBJ)LSM9DS1_c_wrapper.o -o $(LIB)liblsm9ds1cwrapper.so


clean:
	rm -f $(OBJ)*.o $(LIB)*.a $(LIB)*.so


install:
	sudo install -m 644 $(LIB)liblsm9ds1.a $(LIBINSTALLDIR)
	sudo install $(LIB)liblsm9ds1.so $(LIBINSTALLDIR)
	sudo cp include/* $(INCLUDEINSTALLDIR)
	sudo ldconfig
