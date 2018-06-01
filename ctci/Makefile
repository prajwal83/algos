CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11
LDFLAGS=-g -std=c++11
LDLIBS=-lpthread

SRCS=main.cpp
OBJS=$(patsubst %.cpp,%.o,$(wildcard ch1/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard ch2/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard ch3/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard ch4/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard ch5/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard ch6/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard ch8/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard ch10/*.cpp)) \
	$(patsubst %.cpp,%.o,$(wildcard ch15/*.cpp)) \
	$(patsubst %.cpp,%.o,$(SRCS))

all: build ctci

build:
	cd ch1 && make
	cd ch2 && make
	cd ch3 && make
	cd ch4 && make
	cd ch5 && make
	cd ch6 && make
	cd ch8 && make
	cd ch10 && make
	cd ch15 && make

ctci: ${OBJS}
	${CXX} $(LDFLAGS) -o ctci $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean:
	$(RM) $(OBJS) ctci
