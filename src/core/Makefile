SOURCES=main.cpp LoadManager.cpp ModuleBase.cpp common/DLL/DynamicLibrary.cpp common/DLL/LibConnection.cpp common/DLL/linux/unix_dynamic_lib.cpp
OBJECTS=$(SOURCES:.cpp=.o)
CXX=g++
CXXFLAGS=-c -I.
LDFLAGS=-rdynamic -o
DLIBS_INCLUDE=-L./common/log -L../modules/Controller
DLIBS=-llogger -ldl

EXEC=core.elf

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

common/DLL/DynamicLibrary.o: common/DLL/DynamicLibrary.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

common/DLL/LibConnection.o: common/DLL/LibConnection.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

common/DLL/linux/unix_dynamic_lib.o: common/DLL/linux/unix_dynamic_lib.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm $(OBJECTS) $(EXEC)