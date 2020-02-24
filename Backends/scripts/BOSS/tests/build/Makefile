########################################
#                                      #
#   BOSS - Backend-On-a-Stick Script   #
#                                      #
########################################

# Makefile for test classes

CXX = g++

OBJS = U.o S.o test.o

FLAGS = -I../include -fPIC

SHARED = ../lib/libtest.so

%.o : ../src/%.cpp
	${CXX} -c $(FLAGS) -o $@ $<

all: ${OBJS}
	$(CXX) -o $(SHARED) $^ $(FLAGS) -shared

clean:
	$(RM) $(SHARED) *.o
