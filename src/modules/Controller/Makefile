SOURCES=Controller.cpp
OBJECTS=$(SOURCES:.cpp=.o)
CXX=g++
CXXFLAGS=-fPIC -c
LDFLAGS=-rdynamic -shared -o
INCLUDE=-I../../core
DLIBS_INCLUDE=-L../../core/common/log
DLIBS=-llogger

LIBNAME=controller.so

.PHONY: .build clean

.build: $(LIBNAME)

$(LIBNAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) $@ $^ $(DLIBS_INCLUDE) $(DLIBS)

Controller.o: Controller.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^

clean:
	rm $(OBJECTS) $(LIBNAME)