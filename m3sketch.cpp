#include "m3sketch.h"

// compare functions for heap ctor
bool myLess(const int& l, const int& r) {
	return l < r;
}
bool myGreater(const int& l, const int& r) {
	return l > r;
}

M3Sketch::M3Sketch()
		: lower(&myGreater), upper(&myLess) {}

void M3Sketch::insert(int item) {
	if (lower.get_size() <= upper.get_size()) {
		lower.insert(item);
		return;
	}
	upper.insert(item);
}

void M3Sketch::remove(int item) {
	if (item <= get_median()) {
		lower.remove(item);
	} else {
		upper.remove(item);
	}
	// re-balance
	Heap& big = lower.get_size() > upper.get_size() ? lower : upper;
	Heap& smol = lower.get_size() > upper.get_size() ? upper : lower;
	if (big.get_size() - smol.get_size() > 1) {
		smol.insert(big.extract_root());
	}
}

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
