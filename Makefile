all:
	+$(MAKE) -C software
	+$(MAKE) -C hardware

clean:
	+$(MAKE) clean -C software
	+$(MAKE) clean -C hardware