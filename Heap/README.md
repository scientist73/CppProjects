# Heap
Heap is a data structure that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.

A user-provided Compare can be supplied to change the ordering, e.g. using std::greater<T> would cause the smallest element to appear as the top().

Functional similar to std::priority_queue.

### Template parameters:
- **T**             type of the stored elements
- **Compare**       compare func type for stored elements

### Member functions:
- **push**          inserts element and sorts the heap
- **pop**           removes the top element
- **top**           accesses the top element
- **copy_heap**     copies heap_array to another container
- **empty**         checks whether the container adaptor is empty
- **size**          returns the number of elements


