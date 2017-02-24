# invoke SourceDir generated makefile for main.pem4f
main.pem4f: .libraries,main.pem4f
.libraries,main.pem4f: package/cfg/main_pem4f.xdl
	$(MAKE) -f C:\Users\jalex_000\workspace_v6_2\DRV8711-RTOS/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\jalex_000\workspace_v6_2\DRV8711-RTOS/src/makefile.libs clean

