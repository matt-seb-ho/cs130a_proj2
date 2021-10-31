#include <algorithm>
#include <stdexcept>

template <typename T>
Heap<T>::Heap(HeapType ht, bool (*comp)(const T& l, const T& r))
		: data(1), htype(ht), compare(comp) {}

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
bool Heap<T>::search(T item) {
	return find(item) != -1;
}

template <typename T>
T Heap<T>::extract_root() {
	if (filled == 0) {
		throw std::runtime_error("cannot extract root from empty heap");
	}
	// swap root with rightmost leaf
	std::swap(data[0], data[filled - 1]);

	// decrement size and fix order property
	filled--;
	percDown(0);
	return data[filled];
}

template <typename T>
T Heap<T>::get_root() {
	if (filled == 0) {
		throw std::runtime_error("cannot get root from empty heap");
	}
	return data[0];
}

template <typename T>
T Heap<T>::get_min() {
	if (filled == 0) {
		throw std::runtime_error("cannot get min from empty heap");
	}
	if (htype == MIN) {
		return data[0];
	}
	return otherExtreme;
}

template <typename T>
T Heap<T>::get_max() {
	if (filled == 0) {
		throw std::runtime_error("cannot get max from empty heap");
	}
	if (htype == MAX) {
		return data[0];
	}
	return otherExtreme;
}

template <typename T>
int Heap<T>::get_size() {
	return filled;
}

template <typename T>
void Heap<T>::percDown(int index) {
	// get index of extremum among index, left(index), and right(index)
	int ex = index;
	// examine left child
	int child = 2 * index + 1;
	if (child < filled && compare(data[child], data[ex])) {
		ex = child;
	}
	// examine right child
	child++;
	if (child < filled && compare(data[child], data[ex])) {
		ex = child;
	}

	// work is done once data[index] is the extreme
	while (ex != index) {
		// swap items at ex and index 
		std::swap(data[index], data[ex]);

		// update ex for next iteration
		index = ex;
		// examine left child
		int child = 2 * index + 1;
		if (child < filled && compare(data[child], data[ex])) {
			ex = child;
		}
		// examine right child
		child++;
		if (child < filled && compare(data[child], data[ex])) {
			ex = child;
		}
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
