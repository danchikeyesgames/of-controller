

.PHONY: all libdll liblogger core clean

all: liblogger core


libdll:
	make -C core/common/DLL/ .build -j4

liblogger:
	make -C core/common/log .build -j4

core:
	make -C core/ .build -j4

clean:
	make -C core/common/log clean
	make -C core/ clean