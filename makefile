install:
	@echo Installation in progress. Please wait
	@$(CC) grpdecompiler.c -g0 -O0 -o /bin/grpdecompiler
	@chmod ugo+rx /bin/grpdecompiler
	@echo Installation successfully complete
uninstall:
	@rm -f /bin/grpdecompiler
	@echo Uninstallation successfully complete