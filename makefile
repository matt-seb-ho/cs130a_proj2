CXX = g++
CXXFLAGS = -std=c++11 -Wall
EXE = project2

project2: heap.cpp main.cpp m3sketch.cpp
	${CXX} $^ ${CXXFLAGS} -o ${EXE}

scratch: scratch.cpp
	${CXX} scratch.cpp ${CXXFLAGS} -o scratch


clean:
	rm -f ${EXE} *.o
