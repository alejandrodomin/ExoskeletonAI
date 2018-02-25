all:
	@echo "Building software/src software/include and ExoSAI"
	+$(MAKE) -C software
	@echo "Building hardware/src hardware/include and ExoHAI"
	+$(MAKE) -C hardware
	@echo "Building unit testing, ExoTest"
	+$(MAKE) -C software/test

clean:
	@echo "Cleaning software/build and ExoSAI"
	+$(MAKE) clean -C software
	@echo "Cleaning hardware/build and ExoHAI"
	+$(MAKE) clean -C hardware
	@echo "Cleaning unit test, and ExoTest"
	+$(MAKE) -C software/test
