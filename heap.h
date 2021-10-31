#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <string>

class Heap {
	public:
		// ctor
		Heap(bool (*comp)(const int& l, const int& r));

		// mutators
		void insert(int item);
		void remove(int item);
		int extract_root();

		// accessors
		bool search(int item);
		int get_root();
		int get_min();
		int get_max();
		int get_size();

	private:
		// helper routines
		void percDown(int index);
		void percUp(int index, bool toRoot = false);
		int find(int item);
		void checkEmpty(std::string op);

		// returns min if min is true, otherwise returns max 
		int getExtreme(bool min);
	
		// compares items at parent index and its left and right child, and
		// returns the index of the item that should be the parent among the 3
		int getCorrectParent(int parent);


		// underlying data
		std::vector<int> data;
		int filled = 0;
		int otherExtreme;

		// compare(a, b) returns
		// - a < b for minHeap
		// - a > b for maxheap
		bool (*compare)(const int& l, const int& r);
};

#endif
