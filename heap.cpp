#include <stdexcept>
#include <iostream>
#include <algorithm> // std::swap

// ctor
template <typename T>
Heap<T>::Heap(bool (*comp)(const T& l, const T& r))
		: data(1), compare(comp) {}

// mutators
template <typename T>
void Heap<T>::insert(T item) {
	if (filled == data.size()) {
		data.resize(data.size() * 2);
	}
	data[filled] = item;
	percUp(filled++);

	if (filled == 1 || compare(otherExtreme, item)) {
		otherExtreme = item;
	}
}

template <typename T>
void Heap<T>::remove(T item) {
	int index = find(item);
	if (index == -1) {
		return;
	}
	if (item == 0) {
		extract_root();
		return;
	}
	
	// supply optional arg to percUp to ignore comparison and go to root 
	percUp(index, true);
	extract_root();
	
	// if otherExtreme was deleted, re-compute it
	if (item == otherExtreme && filled > 0) {
		otherExtreme = data[0];
		for (int i = 0; i < filled; i++) {
			if (compare(otherExtreme, data[i])) {
				otherExtreme = data[i];
			}
		}
	}
}

template <typename T>
T Heap<T>::extract_root() {
	checkEmpty("extract_root");
	// swap root with rightmost leaf
	std::swap(data[0], data[filled - 1]);

	// decrement size and fix order property
	filled--;
	percDown(0);
	return data[filled];
}

// accessors
template <typename T>
bool Heap<T>::search(T item) {
	return find(item) != -1;
}

template <typename T>
T Heap<T>::get_root() {
	checkEmpty("get_root");
	return data[0];
}

template <typename T>
T Heap<T>::get_min() {
	return getExtreme(true);
}

template <typename T>
T Heap<T>::get_max() {
	return getExtreme(false);
}

template <typename T>
int Heap<T>::get_size() {
	return filled;
}

template <typename T>
void Heap<T>::report() {
	std::cout << "Size = " << get_size() << '\n';
	std::cout << "Min = " << get_min() << '\n';
	std::cout << "Max = " << get_max() << '\n';
}

// helper routines
template <typename T>
void Heap<T>::percDown(int index) {
	// find correct parent among index and its children
	int parent = getCorrectParent(index);

	// work is done once index is already the correct parent
	while (parent != index) {
		// swap correct parent into place 
		std::swap(data[index], data[parent]);

		// update for next iteration
		index = parent;
		parent = getCorrectParent(index);
	}
}

template <typename T>
void Heap<T>::percUp(int index, bool toRoot) {
	int parent = (index - 1) / 2;
	while (parent != index && (toRoot || compare(data[index], data[parent]))) {
		// swap up
		std::swap(data[index], data[parent]);

		// update index and parent for next iteration
		index = parent;
		parent = (index - 1) / 2;
	}
}

template <typename T>
int Heap<T>::find(T item) {
	for (int i = 0; i < filled; i++) {
		if (data[i] == item) {
			return i;
		}
	}
	return -1;
}

template <typename T>
void Heap<T>::checkEmpty(std::string op) {
	if (filled == 0) {
		throw std::runtime_error("empty heap: invalid " + op + " operation");
	}
}

template <typename T>
T Heap<T>::getExtreme(bool min) {
	checkEmpty(min ? "get_min" : "get_max");
	// flip comparison result if min is true
	if ((data[0] > otherExtreme) != min) {
		return data[0];
	}
	return otherExtreme;
}

template <typename T>
int Heap<T>::getCorrectParent(int parent) {
	// examine left child
	int child = 2 * parent + 1;
	if (child < filled && compare(data[child], data[parent])) {
		parent = child;
	}
	// examine right child
	child++;
	if (child < filled && compare(data[child], data[parent])) {
		parent = child;
	}
	return parent;
}
