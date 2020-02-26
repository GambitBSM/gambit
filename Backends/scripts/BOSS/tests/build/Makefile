########################################
#                                      #
#   BOSS - Backend-On-a-Stick Script   #
#                                      #
########################################

# Makefile for test classes

CXX = g++

OBJS = Unspecified.o Specified.o test.o

FLAGS = -I../include -fPIC

SHARED = ../lib/libtest.so

%.o : ../src/%.cpp
	${CXX} -c $(FLAGS) -o $@ $<

all: ${OBJS}
	$(RM) -r ../lib
	mkdir ../lib
	$(CXX) -o $(SHARED) $^ $(FLAGS) -shared

clean:
	$(RM) $(SHARED) *.o
