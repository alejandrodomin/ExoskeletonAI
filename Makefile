all:
	@echo "Building software/src software/include and ExoSAI"
	+$(MAKE) -C software
	@echo "Building hardware/src hardware/include and ExoHAI"
	+$(MAKE) -C hardware

clean:
	@echo "Cleaning software/build and ExoSAI"
	+$(MAKE) clean -C software
	@echo "Cleaning hardware/build and ExoHAI"
	+$(MAKE) clean -C hardware
