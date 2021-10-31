CXX = g++
CXXFLAGS = -std=c++11 -Wall
EXE = project2

project2: heap.h heap.cpp main.cpp
	${CXX} main.cpp ${CXXFLAGS} -o ${EXE}

scratch: scratch.cpp
	${CXX} scratch.cpp ${CXXFLAGS} -o scratch


clean:
	rm -f ${EXE} *.o
