SOURCES=main.cpp LoadManager.cpp ModuleBase.cpp
OBJECTS=$(SOURCES:.cpp=.o)
CXX=g++
CXXFLAGS=-c
LDFLAGS=-o
DLIBS_INCLUDE=-L./common/log -L./common/DLL
DLIBS=-llogger -ldll

EXEC=core

.PHONY: .build clean

.build: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $^ $(DLIBS_INCLUDE) $(DLIBS) $(LDFLAGS) $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $^

LoadManager.o: LoadManager.cpp
	$(CXX) $(CXXFLAGS) $^

ModuleBase.o: ModuleBase.cpp
	$(CXX) -fPIC $(CXXFLAGS) $^

clean:
	rm $(OBJECTS) $(EXEC)