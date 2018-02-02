all:
	+$(MAKE) -C lib
	+$(MAKE) -C software
	+$(MAKE) -C hardware

clean:
	+$(MAKE) clean -C lib
	+$(MAKE) clean -C software
	+$(MAKE) clean -C hardware
