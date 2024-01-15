# SplayTree
Splay tree is a data structure that contains key-value pairs with unique keys. Keys are sorted by using the comparison function Compare. Search, removal, and insertion operations have logarithmic complexity. 

A user-provided Compare can be supplied to change the ordering, e.g. using std::greater<T> would cause the right node to be smaller than parent.

Functional similar to std::map (with the note that std::map implemented as red-black tree).

### Template parameters:
- **Key** - unique key type
- **T** - data type
- **Compare** - key compare func type

### Member types:
- **value_type** - std::pair<const Key, T>

### Member classes:
- **iterator** - iterator for splay_tree

### Member functions:
- **insert** - inserts element
- **erase** - erases element
- **extract** - extracts node from the container
- **find** - finds element with specific key
- **empty** - checks whether the container is empty
- **end** - returns an iterator to the end
