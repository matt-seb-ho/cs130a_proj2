#include <iostream>
#include "heap.h"

template <typename T>
void printv(std::vector<T>& v) {
	for (T& x : v) {
		std::cout << x << ", ";
	}
	std::cout << std::endl;
}

int main() {
	std::vector<int> v = {8, 2, 5, 7, 1, 3, 10};
	printv(v);
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
