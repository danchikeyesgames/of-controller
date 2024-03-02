SOURCES=DynamicLibrary.cpp LibConnection.cpp linux/unix_dynamic_lib.cpp
OBJECTS=$(SOURCES:.cpp=.o)
CXX=g++
CXXFLAGS=-fPIC -c
LDFLAGS=-shared -o
INCLUDE=-I../../
DLIBS_INCLUDE=-L../log
DLIBS=-ldl -llogger

LIBNAME=libdll.so

.PHONY: .build clean

.build: $(LIBNAME)

$(LIBNAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) $@ $^ $(DLIBS_INCLUDE) $(DLIBS)

DynamicLibrary.o: DynamicLibrary.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^

LibConnection.o: LibConnection.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^

linux/unix_dynamic_lib.o: linux/unix_dynamic_lib.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^ -o $@

clean:
	rm $(OBJECTS) $(LIBNAME)
