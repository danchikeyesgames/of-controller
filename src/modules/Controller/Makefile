SOURCES=Controller.cpp Server/OfServer.cpp Server/Message.cpp Dispatcher.cpp
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
	make -C Server/ MainProc.elf -j4
	make -C Server/ Worker.elf -j4

$(LIBNAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) $@ $^ $(LD_DLIBS)

Controller.o: Controller.cpp
	$(CXX) $(DLIBFLAGS) $^

Server/OfServer.o: Server/OfServer.cpp
	$(CXX) $(DLIBFLAGS) $^ -o $@

Server/Message.o: Server/Message.cpp
	$(CXX) $(DLIBFLAGS) $^ -o $@

Dispatcher.o: Dispatcher.cpp
	$(CXX) $(DLIBFLAGS) $^

clean:
	rm $(OBJECTS) $(LIBNAME) Server/MainProc.elf Server/Worker.elf