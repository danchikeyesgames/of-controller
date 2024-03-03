SOURCES=Controller.cpp
OBJECTS=$(SOURCES:.cpp=.o)

CXX ?= g++
CXXFLAGS ?= -c
INCLUDE ?= -I../../core/

DLIBFLAGS=-fPIC $(INCLUDE) $(CXXFLAGS)

DLIBS_INCLUDE=-L../../core/common/log
DLIBS=-llogger

LD_DLIBS=$(DLIBS_INCLUDE) $(DLIBS)
LDFLAGS=-shared -o

LIBNAME=controller.so

.PHONY: .build clean

.build: $(LIBNAME)

$(LIBNAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) $@ $^ $(LD_DLIBS)

Controller.o: Controller.cpp
	$(CXX) $(DLIBFLAGS) $^

clean:
	rm $(OBJECTS) $(LIBNAME)