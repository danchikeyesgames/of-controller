SOURCES=logger.cpp colorscheme.cpp linux/unix_escaped_seq.cpp
OBJECTS=$(SOURCES:.cpp=.o)
CXX=g++
CXXFLAGS=-fPIC -c
LDFLAGS=-shared -o

LIBNAME=liblogger.so

.PHONY: .build clean

.build: $(LIBNAME)

$(LIBNAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) $@ $^

logger.o: logger.cpp
	$(CXX) $(CXXFLAGS) $^

colorscheme.o: colorscheme.cpp
	$(CXX) $(CXXFLAGS) $^

linux/unix_escaped_seq.o: linux/unix_escaped_seq.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm $(OBJECTS) $(LIBNAME)
