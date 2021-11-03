#ifndef M3SKETCH_H
#define M3SKETCH_H

#include "heap.h"

class M3Sketch {
	public:
		// ctor
		M3Sketch();

		// mutators
		void insert(int item);
		void remove(int item);

		// accessors
		int get_median();
		int get_minimum();
		int get_maximum();
		int get_size();
		bool search(int item);
		void report();

		// compare functions for heaps
		static bool lessThan(const int& l, const int& r);
		static bool greaterThan(const int& l, const int& r);

	private:
		// helper routine
		void rebalance();

		// underlying data
		Heap lower;
		Heap upper;
};

#endif
