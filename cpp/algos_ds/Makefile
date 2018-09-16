CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-std=c++14 -O4
LDFLAGS=-std=c++14 -O4 -lpthread
LDLIBS=-lpthread

SRCS=$(shell find . -name "*.cpp")
OBJS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: build alds

build:

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

include .depend

alds: ${OBJS}
	${CXX} $(LDFLAGS) -o alds $(OBJS) $(LDLIBS)

clean:
	$(RM) *.o

distclean:
	$(RM) *.o
	$(RM) alds
