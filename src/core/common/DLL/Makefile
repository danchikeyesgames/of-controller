SOURCES=DynamicLibrary.cpp LibConnection.cpp linux/unix_dynamic_lib.cpp
OBJECTS=$(SOURCES:.cpp=.o)

CXX ?= g++
CXXFLAGS ?= -c
INCLUDE ?= -I.

DLIBS_INCLUDE=-L../log
DLIBS=-ldl -llogger

DLIBFLAGS=-fPIC $(INCLUDE) $(CXXFLAGS)
LDFLAGS=-shared -o
LD_DLIBS= $(DLIBS_INCLUDE) $(DLIBS)

LIBNAME=libdll.so

.PHONY: .build clean

.build: $(LIBNAME)

$(LIBNAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) $@ $^ $(LD_DLIBS)

DynamicLibrary.o: DynamicLibrary.cpp
	$(CXX) $(DLIBFLAGS) $^

LibConnection.o: LibConnection.cpp
	$(CXX) $(DLIBFLAGS) $^

linux/unix_dynamic_lib.o: linux/unix_dynamic_lib.cpp
	$(CXX) $(DLIBFLAGS) $^ -o $@

clean:
	rm $(OBJECTS) $(LIBNAME)
