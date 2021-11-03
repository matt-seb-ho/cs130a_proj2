#include <iostream>
#include <fstream>
#include "heap.h"
#include "m3sketch.h"
#include <algorithm>

template <typename T>
void printv(std::vector<T>& v) {
	for (T& x : v) {
		std::cout << x << ", ";
	}
	std::cout << std::endl;
}

bool goodLess(const int& l, const int& r) {
	return l < r;
}

bool goodGreater(const int& l, const int& r) {
	return l > r;
}

void heapReport(Heap& h) {
	std::cout << "Size = " << h.get_size() << '\n';
	std::cout << "Min = " << h.get_min() << '\n';
	std::cout << "Max = " << h.get_max() << '\n';
}

void m3Report(M3Sketch& m3) {
	std::cout << "Size = " << m3.get_size() << '\n';
	std::cout << "Min = " << m3.get_minimum() << '\n';
	std::cout << "Max = " << m3.get_maximum() << '\n';
	std::cout << "Median = " << m3.get_median() << '\n';
}
	
int main(int argc, char* argv[]) {
	std::vector<int> v = {8, 2, 5, 7, 1, 3, 10};
	printv(v);

	// Heap minH(&goodLess), maxH(&goodGreater);
	std::vector<int> v2;
	M3Sketch m3;
	std::ifstream in(argv[1]);
	int x;
	int counter = 0;
	while (in >> x) {
		counter++;
		m3.insert(x);
		v2.push_back(x);
		// minH.insert(x);
		// maxH.insert(x);
	}
	in.close();

	m3Report(m3);

	std::sort(v2.begin(), v2.end());
	std::cout << "vec ver:\n";
	std::cout << v2[0] << '\n';
	std::cout << v2[v2.size() - 1] << '\n';
	std::cout << v2[v2.size() / 2 - 1] << '\n';

	/* 
	std::cout << "counter: " << counter << '\n';
	std::cout << "Min Heap:\n";
	heapReport(minH);
	std::cout << "Max Heap:\n";
	heapReport(maxH);
	*/

	/*
	// Heap h(&myLess);
	// empty heap test
	// std::cout << h.get_min() << '\n';
	for (int x : v) {
		h.insert(x);
	}
	std::cout << h.get_max() << '\n';
	h.remove(10);
	std::cout << "new max: " << h.get_max() << '\n';
	int s = h.get_size();
	for (int i = 0; i < s; i++) {
		std::cout << h.extract_root() << ", ";
	}
	std::cout << '\n';
	*/

	return 0;
}
