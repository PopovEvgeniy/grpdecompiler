install:
	@echo Installation in progress. Please wait
	@gcc grpdecompiler.c -g0 -O0 -o grpdecompiler
	@chmod ugo+rx grpdecompiler
	@cp -f -p grpdecompiler /bin/
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/grpdecompiler
	@echo Uninstallation was successfuly complete