#include <iostream>

// ctor
template <typename T>
M3Sketch<T>::M3Sketch(
		bool (*lt)(const T& l, const T& r), 
		bool (*gt)(const T& l, const T& r))
		: lessThan(lt), greaterThan(gt), lower(gt), upper(lt) {}

// mutators
template <typename T>
void M3Sketch<T>::insert(T item) {
	if (get_size() == 0 || lessThan(item, get_median())) {
		lower.insert(item);
	} else {
		upper.insert(item);
	}
	rebalance();
}

template <typename T>
void M3Sketch<T>::remove(T item) {
	Heap<int>* targetHeap;
	if (lessThan(item, get_median())) {
		targetHeap = &lower;
	} else if (greaterThan(item, get_median())) {
		targetHeap = &upper;
	} else {
		targetHeap = lower.get_size() >= upper.get_size() ? &lower : &upper;
	}
	targetHeap->remove(item);
	rebalance();
}

// accessors
template <typename T>
T M3Sketch<T>::get_median() {
	if (lower.get_size() >= upper.get_size()) {
		return lower.get_root();
	}
	return upper.get_root();
}

template <typename T>
T M3Sketch<T>::get_minimum() {
	return lower.get_min();
}

template <typename T>
T M3Sketch<T>::get_maximum() {
	return upper.get_max();
}

template <typename T>
int M3Sketch<T>::get_size() {
	return lower.get_size() + upper.get_size();
}

template <typename T>
bool M3Sketch<T>::search(T item) {
	if (lessThan(item, get_minimum()) || greaterThan(item, get_maximum())) {
		return false;
	}
	Heap<T>& heapToSearch = greaterThan(item, get_median())? upper : lower;
	return heapToSearch.search(item);
}

template <typename T>
void M3Sketch<T>::report() {
	std::cout << "Size = " << get_size() << '\n';
	std::cout << "Min = " << get_minimum() << '\n';
	std::cout << "Max = " << get_maximum() << '\n';
	std::cout << "Median = " << get_median() << '\n';
}
	
// helper routine
template <typename T>
void M3Sketch<T>::rebalance() {
	Heap<T>& big = lower.get_size() > upper.get_size() ? lower : upper;
	Heap<T>& smol = lower.get_size() > upper.get_size() ? upper : lower;
	if (big.get_size() - smol.get_size() > 1) {
		smol.insert(big.extract_root());
	}
}
