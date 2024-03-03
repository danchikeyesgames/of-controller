SOURCES=main.cpp LoadManager.cpp ModuleBase.cpp
OBJECTS=$(SOURCES:.cpp=.o)

CXX ?= g++
CXXFLAGS ?= -c
INCLUDE ?= -I.

DLIBS_INCLUDE=-L./common/log -L./common/DLL -L../modules/Controller
DLIBS=-llogger -ldll

CXXFLAGS:=$(CXXFLAGS) $(INCLUDE)
LD_DLIBS=$(DLIBS_INCLUDE) $(DLIBS)
LDFLAGS=-rdynamic -o

EXEC=core.elf

.PHONY: .build run clean

.build: $(EXEC)

run:
	./$(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $^ $(LDFLAGS) $@ $(LD_DLIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $^

LoadManager.o: LoadManager.cpp
	$(CXX) $(CXXFLAGS) $^

ModuleBase.o: ModuleBase.cpp
	$(CXX) -fPIC $(CXXFLAGS) $^

clean:
	rm $(OBJECTS) $(EXEC)