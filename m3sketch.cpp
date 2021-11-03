#include "m3sketch.h"
#include <iostream>

// ctor
M3Sketch::M3Sketch()
		: lower(&greaterThan), upper(&lessThan) {}

// mutators
void M3Sketch::insert(int item) {
	if (get_size() == 0 || item < get_median()) {
		lower.insert(item);
	} else {
		upper.insert(item);
	}
	rebalance();
}

void M3Sketch::remove(int item) {
	if (item <= get_median()) {
		lower.remove(item);
	} else {
		upper.remove(item);
	}
	rebalance();
}

// accessors
int M3Sketch::get_median() {
	return lower.get_root();
}

int M3Sketch::get_minimum() {
	return lower.get_min();
}

int M3Sketch::get_maximum() {
	return upper.get_max();
}

int M3Sketch::get_size() {
	return lower.get_size() + upper.get_size();
}

bool M3Sketch::search(int item) {
	if (item < get_minimum() || item > get_maximum()) {
		return false;
	}
	Heap& heapToSearch = item <= get_median() ? lower : upper;
	return heapToSearch.search(item);
}

void M3Sketch::report() {
	std::cout << "Size = " << get_size() << '\n';
	std::cout << "Min = " << get_minimum() << '\n';
	std::cout << "Max = " << get_maximum() << '\n';
	std::cout << "Median = " << get_median() << '\n';
}
	
// heap compare functions
bool M3Sketch::lessThan(const int& l, const int& r) {
	return l < r;
}
bool M3Sketch::greaterThan(const int& l, const int& r) {
	return l > r;
}

// helper routine
void M3Sketch::rebalance() {
	Heap& big = lower.get_size() > upper.get_size() ? lower : upper;
	Heap& smol = lower.get_size() > upper.get_size() ? upper : lower;
	if (big.get_size() - smol.get_size() > 1) {
		smol.insert(big.extract_root());
	}
}
