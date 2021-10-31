#ifndef HEAP_H
#define HEAP_H
#include <vector>

enum HeapType {
	MIN,
	MAX,
};

template <typename T>
class Heap {
	public:
		// ctor
		Heap(HeapType ht, bool (*comp)(const T& l, const T& r));

		// mutators
		void insert(T item);
		void remove(T item);
		bool search(T item);
		T extract_root();

		// accessors
		T get_root();
		T get_min();
		T get_max();
		int get_size();

	private:
		// helper routines
		void percDown(int index);
		void percUp(int index, bool toRoot = false);
		int find(T item);

		// underlying data
		std::vector<T> data;
		HeapType htype;
		int filled = 0;
		T otherExtreme;

		// compare(a, b) returns
		// - a < b for minHeap
		// - a > b for maxheap
		bool (*compare)(const T& l, const T& r);
};

#include "heap.cpp"
#endif
