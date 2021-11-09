#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <string>

template <typename T>
class Heap {
	public:
		// ctor
		Heap(bool (*comp)(const T& l, const T& r), bool isMinHeap);

		// mutators
		void insert(T item);
		void remove(T item);
		T extract_root();

		// accessors
		bool search(T item);
		T get_root();
		T get_min();
		T get_max();
		int get_size();
		void report();

	private:
		// helper routines
		void percDown(int index);
		void percUp(int index, bool toRoot = false);
		int find(T item);
		void checkEmpty(std::string op);

		// compares items at parent index and its left and right child, and
		// returns the index of the item that should be the parent among the 3
		int getCorrectParent(int parent);


		// underlying data
		std::vector<T> data;
		int filled = 0;
		bool isMinHeap;
		T otherExtreme;

		// compare(a, b) returns
		// - a < b for minHeap
		// - a > b for maxheap
		bool (*compare)(const T& l, const T& r);
};

#include "heap.cpp"
#endif
