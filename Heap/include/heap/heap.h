// Written by scienist73 in 2024
//
// "heap.h" is a library with heap data structure implementation 
//

#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>





// Heap data structure (max_heap by default)
//
// type T requirements:
//		* copy constructor
// 		* overloaded < (less operator) for max_heap or specify comparation rule as Compare type
//		* overloaded > (greater operator) for min_heap or specify comparation rule as Compare type
//

template <class T, class Compare = std::less<>>
class heap
{
public:
    heap(Compare comp = Compare{});
    ~heap();

    void push(const T& value);
    void pop();
    T top() const;

    template <class OutputIt>
    void copy_heap(OutputIt d_first) const;

    bool empty() const;
    size_t size() const;

private:
    size_t get_parent_index(size_t child) const;
    T* get_parent(size_t child) const;

    size_t get_left_child_index(size_t parent) const;
    T* get_left_child(size_t parent) const;

    size_t get_right_child_index(size_t parent) const;
    T* get_right_child(size_t parent) const;

	std::vector<T*> heap_array;

    Compare comp; // comparation function, set std::greater<T> to get min_heap
};


// public
template<class T, class Compare>
heap<T, Compare>::heap(Compare comp)
{
	this->comp = comp;
}

template<class T, class Compare>
heap<T, Compare>::~heap()
{
    for (size_t i = 0; i < heap_array.size(); ++i)
	{
		delete heap_array[i];
	}
	heap_array.clear();
}

// Inserts item with value in the heap
// O(log(n)) complexity
template<class T, class Compare>
void heap<T, Compare>::push(const T& value)
{
	heap_array.push_back(nullptr);

	for (size_t i = heap_array.size() - 1; ; i = get_parent_index(i))
	{
		auto x = get_parent(i);

		if (x == nullptr || !comp(*x, value))
		{
			heap_array[i] = new T(value);

			break;
		}

		heap_array[i] = x;
	}
}

// Removes top item (item in the root) from the heap
// O(1) complexity
template<class T, class Compare>
void heap<T, Compare>::pop()
{
	if (!empty())
	{
		auto y = heap_array.back();
		heap_array.pop_back();

		delete heap_array[0];

		if (heap_array.empty())
			return;

		for (size_t i = 0;;)
		{
			auto l_child = get_left_child(i);
			auto r_child = get_right_child(i);

			if (r_child != nullptr)
			{
				if (!comp(*l_child, *r_child))
				{
					if (!comp(*l_child, *y))
					{
						heap_array[i] = l_child;

						i = get_left_child_index(i);
					}
					else
					{
						heap_array[i] = y;

						break;
					}
				}
				else
				{
					if (!comp(*r_child, *y))
					{
						heap_array[i] = r_child;

						i = get_right_child_index(i);
					}
					else
					{
						heap_array[i] = y;

						break;
					}
				}
			}
			else if (l_child != nullptr)
			{
				if (!comp(*l_child, *y))
				{
					heap_array[i] = l_child;

					i = get_left_child_index(i);
				}
				else
				{
					heap_array[i] = y;

					break;
				}
			}
			else
			{
				heap_array[i] = y;

				break;
			}
		}
	}
	else
		throw std::underflow_error("Can't pop element from an empty heap.");
}

// Returns heap's top item (item in the root)
// O(1) complexity
template<class T, class Compare>
T heap<T, Compare>::top() const
{
    if (!empty())
        return *heap_array[0];
    else
        throw std::underflow_error("Can't get top element from an empty heap.");
}

// Copies heap_array to another container that supports pointer iterations starting with d_first
// Size of new container must be not less that heap size
// Container's iterator must have overloaded * (deref) and ++ (prefix inc) operators
template<class T, class Compare>
template<class OutputIt>
void heap<T, Compare>::copy_heap(OutputIt d_first) const
{
	for (size_t i = 0; i < heap_array.size(); ++i)
	{
		*d_first = *heap_array[i];
		++d_first;
	}
}

// Returns weather heap is empty (true) or not (false)
// O(1) complexity
template<class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return heap_array.empty();
}

// Returns size of the heap
// O(1) complexity
template<class T, class Compare>
size_t heap<T, Compare>::size() const
{
	return heap_array.size();
}


// private

// Returns parent's index in heap_array if any
// Otherwise throws std::out_of_range exception
template<class T, class Compare>
size_t heap<T, Compare>::get_parent_index(size_t child) const
{
    if (child)
        return ((child + 1) / 2) - 1;
    else
        throw std::out_of_range("Node doesn't have a parent node.");
}

// Returns pointer to the parent in heap_array if any
// Otherwise returns nullptr
template<class T, class Compare>
T* heap<T, Compare>::get_parent(size_t child) const
{
    if (child)
        return heap_array[((child + 1) / 2) - 1];
    else
        return nullptr;
}


// Returns left child's index in heap_array if any
// Otherwise throws std::out_of_range exception
template<class T, class Compare>
size_t heap<T, Compare>::get_left_child_index(size_t parent) const
{
    size_t i = (2 * (parent + 1)) - 1;

    if (i < heap_array.size())
        return i;
    else
        throw std::out_of_range("Node doesn't have a left child node.");
}

// Returns pointer to the left child in heap_array if any
// Otherwise returns nullptr
template<class T, class Compare>
T* heap<T, Compare>::get_left_child(size_t parent) const
{
    size_t i = (2 * (parent + 1)) - 1;

    if (i < heap_array.size())
        return heap_array[i];
    else
        return nullptr;
}


// Returns right child's index in heap_array if any
// Otherwise throws std::out_of_range exception
template<class T, class Compare>
size_t heap<T, Compare>::get_right_child_index(size_t parent) const
{
    size_t i = (2 * (parent + 1));

    if (i < heap_array.size())
        return i;
    else
        throw std::out_of_range("Node doesn't have a right child node.");
}

// Returns pointer to the right child in heap_array if any
// Otherwise returns nullptr
template<class T, class Compare>
T* heap<T, Compare>::get_right_child(size_t parent) const
{
    size_t i = (2 * (parent + 1));

    if (i < heap_array.size())
        return heap_array[i];
    else
        return nullptr;
}
