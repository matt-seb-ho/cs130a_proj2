CXX = g++
CXXFLAGS = -std=c++11 -Wall
EXE = project2

project2: heap.cpp main.cpp m3sketch.cpp heap.h m3sketch.h
	${CXX} main.cpp  ${CXXFLAGS} -o ${EXE}

scratch: scratch.cpp
	${CXX} scratch.cpp ${CXXFLAGS} -o scratch

tester: tester.cpp
	${CXX} tester.cpp ${CXXFLAGS} -o tester

clean:
	rm -f tester ${EXE} *.o
