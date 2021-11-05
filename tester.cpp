#include <iostream>
#include "heap.h"
#include "m3sketch.h"

using namespace std;


template <typename T>
bool tempLess(const T& l, const T& r) {
	return l < r;
}

template <typename T>
bool tempGreater(const T& l, const T& r) {
	return l > r;
}

int main() {
	Heap<int> minH(&tempLess);
	minH.insert(8);
	minH.insert(3);
	minH.insert(1);
	minH.insert(9);
	minH.insert(5);
	
	for (int i = 0; i < 5; i++) {
		cout << minH.extract_root() << endl;
	}

	/*
	M3Sketch<int> m3(&tempLess, &tempGreater);
	m3.insert(8);
	m3.insert(7);
	m3.insert(9);
	m3.report();
	m3.remove(8);
	m3.report();
	*/

	return 0;
}
