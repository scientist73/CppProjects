// Written by scientist73 in 2024
//
// "splay_tree.h" is a library with splay tree data structure implementation
//

#include <utility>
#include <cstddef>
#include <queue>
#include <functional>
#include <stdexcept>


// Splay tree structure
//
// type Key requirements:
//		* copy constructor
// 		* overloaded < or > (less or greater operator) or specify comparation rule as Compare type
//

template<class Key, class T, class Compare = std::less<>>
class splay_tree
{
public:
    typedef std::pair<const Key, T> value_type;
private:
    struct node_type
    {    
        value_type* value;

        node_type* parent;
        node_type* l_child = nullptr, * r_child = nullptr;
    };
public:
    class iterator
    {
        friend class splay_tree;
    public:
        iterator() : iterator(nullptr, nullptr) {}
        iterator(const iterator& it);

        value_type* operator-> () { return node->value; }
        value_type& operator* () { return (*node->value); }


        friend bool operator!= (const iterator& it1, const iterator& it2);
        
    private:
        iterator(node_type* node, const splay_tree* tree);
        iterator(const splay_tree* tree) : iterator(nullptr, tree) {}

        node_type* node;
        const splay_tree* tree;
    };

    splay_tree(Compare comp = Compare{});
    ~splay_tree();

    std::pair<iterator, bool> insert(const value_type& value);
    size_t erase(const Key& key);
    value_type extract(const Key& key);
    iterator find(const Key& key);

    bool empty() const;
    iterator end() const;
private:
    node_type* _find(const Key& key);

    void splay(node_type* n);

    void zig_l(node_type* n);
    void zig_r(node_type* n);


    node_type* root;

    Compare comp;
};



template<class Key, class T, class Compare>
splay_tree<Key, T, Compare>::iterator::iterator(const iterator& it)
{
    this->node = it.node;
    this->tree = it.tree;
}

template<class Key, class T, class Compare>
bool operator!=(const typename splay_tree<Key,T,Compare>::iterator& it1, const typename splay_tree<Key,T,Compare>::iterator& it2)
{
    return it1.tree != it2.tree && it1.node != it2.node;
}

template<class Key, class T, class Compare>
splay_tree<Key, T, Compare>::iterator::iterator(typename splay_tree<Key,T,Compare>::node_type* node, const splay_tree<Key, T, Compare>* tree)
{
    this->node = node;
    this->tree = tree;
}

// public:
template<class Key, class T, class Compare>
splay_tree<Key, T, Compare>::splay_tree(Compare comp)
{
    root = nullptr;
    this->comp = comp;
}

template<class Key, class T, class Compare>
splay_tree<Key, T, Compare>::~splay_tree()
{
    if (root == nullptr) return;

    std::queue<node_type*> q;
    q.push(root);

    do
    {
        auto v = q.front(); q.pop();

        if (v->l_child != nullptr)
            q.push(v->l_child);
        if (v->r_child != nullptr)
            q.push(v->r_child);

        delete v;

    } while (!q.empty());
}

// Inserts value in the splay tree
// Returns (iterator, true) if insertion is successidied and (nullptr, false) otherwise
// O(log(n))
template<class Key, class T, class Compare>
std::pair<typename splay_tree<Key, T, Compare>::iterator, bool> splay_tree<Key, T, Compare>::insert(const typename splay_tree<Key, T, Compare>::value_type& value)
{
    if (root == nullptr)
    {
        root = new node_type{new value_type(value), nullptr};

        return std::make_pair(iterator(root, this), true);
    }


    node_type* search = root;

    while (true)
    {
        if (value.first == search->value->first)
        {
            splay(search);

            return std::make_pair(iterator(this), false);
        }

        if (comp(value.first, search->value->first))
        {
            if (search->l_child == nullptr)
            {
                node_type* new_v = new node_type { new value_type(value), search };
                search->l_child = new_v;
                splay(new_v);

                return std::make_pair(iterator(new_v, this), true);
            }
            else
                search = search->l_child;
        }
        else // if (key >= root->key)
        {
            if (search->r_child == nullptr)
            {
                node_type* new_v = new node_type{ new value_type(value), search };
                search->r_child = new_v;
                splay(new_v);

                return std::make_pair(iterator(new_v, this), true);
            }
            else
                search = search->r_child;
        }
    }
}

// Erases node with the key
// O(log(n))
template<class Key, class T, class Compare>
size_t splay_tree<Key, T, Compare>::erase(const Key& key)
{
    value_type value = extract(key);

    if (value != value_type())
        return (size_t)1;
    else
        return (size_t)0;
}

// Extracts node
// O(log(n))
template<class Key, class T, class Compare>
typename splay_tree<Key, T, Compare>::value_type splay_tree<Key, T, Compare>::extract(const Key & key)
{
    node_type* search = _find(key);

    if (search != nullptr)
    {
        value_type value = *search->value;

        // if this key exists, then after _find it wound be in the root
        if (root->l_child == nullptr)
        {
            if (root->r_child != nullptr)
            {
                root = search->r_child;
                root->parent = nullptr;

                delete search;
            }
            else
            {
                root = nullptr;

                delete search;
            }
        }
        else
        {
            if (root->r_child != nullptr)
            {
                node_type* r_root = root->r_child; // right tree

                root = root->l_child; // left tree - main tree
                root->parent = nullptr;


                delete search; // delete old root



                node_type* max = root;
                while (max->r_child != nullptr)
                {
                    max = max->r_child;
                }
                splay(max);

                root->r_child = r_root;
                r_root->parent = root;
            }
            else
            {
                root = root->l_child;
                root->parent = nullptr;

                delete search;
            }
        }

        return value;
    }
    else
        return value_type();
}

// Returns iterator of node with the key
// O(log(n))
template<class Key, class T, class Compare>
typename splay_tree<Key, T, Compare>::iterator splay_tree<Key, T, Compare>::find(const Key & key)
{
    return iterator(_find(key), this);
}

// Returns weather splay tree is empty (true) or not (false)
// O(1)
template<class Key, class T, class Compare>
bool splay_tree<Key, T, Compare>::empty() const
{
    return (root == nullptr);
}

// Returns iterator to the end of the splay tree
// O(1)
template<class Key, class T, class Compare>
typename splay_tree<Key, T, Compare>::iterator splay_tree<Key, T, Compare>::end() const
{
    return iterator(this);
}

// private:

// Finds node
// O(log(n))
template<class Key, class T, class Compare>
typename splay_tree<Key, T, Compare>::node_type* splay_tree<Key, T, Compare>::_find(const Key & key)
{
    if (root == nullptr)
        return nullptr;


    node_type* search = root;

    while (true)
    {
        if (key == search->value->first)
        {
            splay(search);

            return search;
        }

        if (comp(key, search->value->first))
        {
            if(search->l_child == nullptr)
            {
                splay(search);

                return nullptr; // not found
            }
            else
                search = search->l_child;
        }
        else
        {
            if (search->r_child == nullptr)
            {
                splay(search);

                return nullptr; // not found
            }
            else
                search = search->r_child;
        }
    }
}

// ascend the node to the root
// O(log(n))
template<class Key, class T, class Compare>
void splay_tree<Key, T, Compare>::splay(typename splay_tree<Key, T, Compare>::node_type* n)
{
    while (n != root)
    {
        if (n->parent->parent == nullptr)
        {
            if (n == n->parent->l_child)
                zig_l(n);
            else
                zig_r(n);
        }
        else
        {
            if (n->parent == n->parent->parent->l_child)
            {
                if (n == n->parent->l_child)
                {
                    zig_l(n->parent);
                    zig_l(n);
                }
                else
                {
                    zig_r(n);
                    zig_l(n);
                }
            }
            else
            {
                if (n == n->parent->r_child)
                {
                    zig_r(n->parent);
                    zig_r(n);
                }
                else
                {
                    zig_l(n);
                    zig_r(n);
                }
            }
        }
    }
}

// left turn of the node
// O(1)
template<class Key, class T, class Compare>
void splay_tree<Key, T, Compare>::zig_l(typename splay_tree<Key, T, Compare>::node_type* n)
{
    // x = n
    // y = n->parent


    if (n == nullptr || n->parent == nullptr)
        throw std::invalid_argument("zig_l error");
        

    node_type* y_parent = n->parent->parent;

    if (n->parent->parent != nullptr)
    {
        if (n->parent->parent->l_child == n->parent)
            n->parent->parent->l_child = n;
        else // if (n->parent->parent->r_child == n->parent)
            n->parent->parent->r_child = n;
    }
    else
        root = n;

    n->parent->l_child = n->r_child; // y->l_child = x->r_child
    if (n->r_child != nullptr)
        n->r_child->parent = n->parent;

    n->parent->parent = n; // y->parent = x
    n->r_child = n->parent; //x->r_child = y
    n->parent = y_parent; // x->parent = y->parent
}

// right turn of the node
// O(1)
template<class Key, class T, class Compare>
void splay_tree<Key, T, Compare>::zig_r(typename splay_tree<Key, T, Compare>::node_type* n)
{
    // x = n
    // y = n->parent


    if (n == nullptr || n->parent == nullptr)
        throw std::invalid_argument("zig_r error");

    node_type* y_parent = n->parent->parent;

    if (n->parent->parent != nullptr)
    {
        if (n->parent->parent->l_child == n->parent)
            n->parent->parent->l_child = n;
        else // if (n->parent->parent->r_child == n->parent)
            n->parent->parent->r_child = n;
    }
    else
        root = n;

    n->parent->r_child = n->l_child; // y->r_child = x->l_child
    if (n->l_child != nullptr)
        n->l_child->parent = n->parent;

    n->parent->parent = n; // y->parent = x
    n->l_child = n->parent; //x->l_child = y
    n->parent = y_parent; // x->parent = y->parent
}

