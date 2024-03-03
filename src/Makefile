export CXX=g++
export CXXFLAGS=-c
export INCLUDE=-I/home/danchik//Desktop/rep/of-controller/src/core
export LD_LIBRARY_PATH:=~/Desktop/rep/of-controller/src/core/common/DLL:~/Desktop/rep/of-controller/src/core/common/log:~/Desktop/rep/of-controller/src/modules/Controller/

LIBDLL_PATH=core/common/DLL/
LIBLOGGER_PATH=core/common/log
CORE_PATH=core/

.PHONY: all run libdll liblogger core libdll-clean liblogger-clean core-clean clean

all: liblogger libdll core

run:
	./$(CORE_PATH)core.elf

libdll:
	make -C $(LIBDLL_PATH) .build -j4

liblogger:
	make -C $(LIBLOGGER_PATH) .build -j4

core:
	make -C $(CORE_PATH) .build -j4


libdll-clean:
	make -C $(LIBDLL_PATH) clean

liblogger-clean:
	make -C $(LIBLOGGER_PATH) clean

core-clean:
	make -C $(CORE_PATH) clean

clean: libdll-clean liblogger-clean core-clean