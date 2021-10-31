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

	private:
		// underlying data
		Heap lower;
		Heap upper;
};

#endif
