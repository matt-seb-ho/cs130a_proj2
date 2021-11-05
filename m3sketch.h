#ifndef M3SKETCH_H
#define M3SKETCH_H

#include "heap.h"

template <typename T>
class M3Sketch {
	public:
		// ctor
		M3Sketch(
			bool (*lt)(const T& l, const T& r), 
			bool (*gt)(const T& l, const T& r));

		// mutators
		void insert(T item);
		void remove(T item);

		// accessors
		T get_median();
		T get_minimum();
		T get_maximum();
		int get_size();
		bool search(T item);
		void report();

	private:
		// helper routine
		void rebalance();

		// compare functions for heaps
		bool (*lessThan)(const T& l, const T& r);
		bool (*greaterThan)(const T& l, const T& r);

		// underlying data
		Heap<T> lower;
		Heap<T> upper;
};

#include "m3sketch.cpp"
#endif
