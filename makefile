install:
	@echo Compiling the program source code. Please wait
	@gcc grpdecompiler.c -g0 -O0 -o grpdecompiler
	@echo Compilation successfuly complete
	@chmod ugo+rx grpdecompiler
	@echo Enter you user password for do last installation step
	@sudo cp -f -p grpdecompiler /bin/
	@echo Installation complete
uninstall:
	@echo Enter you user password for uninstall this software
	@sudo rm -f /bin/grpdecompiler
	@echo Uninstallation complete