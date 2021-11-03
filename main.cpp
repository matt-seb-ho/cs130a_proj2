#include "heap.h"
#include "m3sketch.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

template <typename Functor>
void processIntFile(char* fname, Functor functor) {
	std::ifstream in(fname);
	if (in.fail()) {
		throw std::runtime_error("file open failed.\n");
	}
	int x;
	while (in >> x) {
		functor(x);
	}
	in.close();
}

int main(int argc, char* argv[]) {
	// Heap minH(&goodLess), maxH(&goodGreater);
	if (argc != 4) {
		std::cerr << "wrong number of args\n";
	} else {
		if (strcmp(argv[1], "heap") == 0) {
			Heap minH(&M3Sketch::lessThan);
			Heap maxH(&M3Sketch::greaterThan);
			processIntFile(argv[2], [&](int x) {
				minH.insert(x);
				maxH.insert(x);
			});
			processIntFile(argv[3], [&](int x) {
				minH.remove(x);
				maxH.remove(x);
			});
			std::cout << "Min Heap:\n";
			minH.report();
			std::cout << "Max Heap:\n";
			maxH.report();
		} else if (strcmp(argv[1], "minmedianmax") == 0) {
			M3Sketch m3;
			processIntFile(argv[2], [&](int x) {
				m3.insert(x);
			});
			processIntFile(argv[3], [&](int x) {
				m3.remove(x);
			});
			std::cout << "MinMedianMaxSketch:\n";
			m3.report();
		}
	}
	return 0;
}
