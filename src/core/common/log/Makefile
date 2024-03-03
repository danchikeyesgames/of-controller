SOURCES=logger.cpp colorscheme.cpp linux/unix_escaped_seq.cpp
OBJECTS=$(SOURCES:.cpp=.o)

CXX ?= g++
CXXFLAGS ?= -c
INCLUDE ?= -I.

DLIBFLAGS=-fPIC $(INCLUDE) $(CXXFLAGS)
LDFLAGS=-shared -o

LIBNAME=liblogger.so

.PHONY: .build clean

.build: $(LIBNAME)

$(LIBNAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) $@ $^

logger.o: logger.cpp
	$(CXX) $(DLIBFLAGS) $^

colorscheme.o: colorscheme.cpp
	$(CXX) $(DLIBFLAGS) $^

linux/unix_escaped_seq.o: linux/unix_escaped_seq.cpp
	$(CXX) $(DLIBFLAGS) $^ -o $@

clean:
	rm $(OBJECTS) $(LIBNAME)
