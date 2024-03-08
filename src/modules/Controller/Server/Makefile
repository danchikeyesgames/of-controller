SOURCES=MainProc.cpp Worker.cpp
OBJECTS=$(SOURCES:.cpp=.o)

CXX ?= g++
CXXFLAGS ?= -c
INCLUDE ?= -I../../../core/

CXXFLAGS:=$(INCLUDE)

DLIBS_INCLUDE=-L../../../core/common/log
DLIBS=-llogger

LD_DLIBS=$(DLIBS_INCLUDE) $(DLIBS)
LDFLAGS=-c

EXECMAINPROC=MainProc.elf
EXECWORKER=Worker.elf

$(EXECMAINPROC): MainProc.cpp Message.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LD_DLIBS)

$(EXECWORKER): Worker.cpp Message.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LD_DLIBS)