install:
	@echo Installation in progress. Please wait
	@gcc grpdecompiler.c -g0 -O0 -o /bin/grpdecompiler
	@chmod ugo+rx /bin/grpdecompiler
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/grpdecompiler
	@echo Uninstallation was successfuly complete