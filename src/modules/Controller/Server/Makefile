SOURCES=MainProc.cpp Worker.cpp
OBJECTS=$(SOURCES:.cpp=.o)

CXX ?= g++
CXXFLAGS ?= -c
INCLUDE ?= -I../../../core/

CXXFLAGS:=$(INCLUDE) $(CXXFLAGS)

DLIBS_INCLUDE=-L../../core/common/log
DLIBS=-llogger

LD_DLIBS=$(DLIBS_INCLUDE) $(DLIBS)
LDFLAGS=-c

EXECMAINPROC=MainProc.elf
EXECWORKER=Worker.elf

$(EXECMAINPROC): MainProc.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LD_DLIBS)

$(EXECWORKER): Worker.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LD_DLIBS)