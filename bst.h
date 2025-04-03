#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void recursiveRemove(Node<Key, Value>* node_to_remove);
    Node<Key, Value>* recursiveFind(Node<Key, Value>* current, const Key& key) const;
    static Node<Key, Value>* recursiveSmallest(Node<Key, Value>* current);
    static Node<Key, Value>* recursiveLargest(Node<Key, Value>* current);
    static Node<Key, Value>* ancestorRightChild(Node<Key, Value>* current);
    static Node<Key, Value>* ancestorLeftChild(Node<Key, Value>* current);
    Node<Key, Value>* findEmpty(Node<Key, Value>* current, const Key& key) const; // used in insert function
    Node<Key, Value>* findRoot(Node<Key, Value>* current) const;
    bool isBalanced_recursive(Node<Key, Value>* current) const;
    int treeHeight(Node<Key, Value>* root, int count) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr) : current_(ptr)
{
    // TODO
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(NULL)
{
    // TODO

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (current_ != rhs.current_);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    current_ = BinarySearchTree<Key, Value>::successor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()  : root_(nullptr)
{
    // TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    this->clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    // std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    if (this->root_ == nullptr) {
        Node<Key, Value>* new_root = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        this->root_ = new_root;
    }

    Node<Key, Value>* node_to_replace = internalFind(keyValuePair.first);
    if (node_to_replace != nullptr) {
        node_to_replace->setValue(keyValuePair.second);
    }
    else {
        Node<Key, Value>* new_node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        Node<Key, Value>* parent = findEmpty(root_, keyValuePair.first);
        if (keyValuePair.first < parent->getKey()) {
            parent->setLeft(new_node);
            new_node->setParent(parent);
        }
        else {
            parent->setRight(new_node);
            new_node->setParent(parent);
        }
    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::findEmpty(Node<Key, Value>* current, const Key& key) const 
{
    if (current->getKey() > key) {
        if (current->getLeft() == nullptr) {
            return current;
        }
        else {
            return findEmpty(current->getLeft(), key);
        }
    }
    else {
        if (current->getRight() == nullptr) {
            return current;
        }
        else {
            return findEmpty(current->getRight(), key);
        }
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::recursiveRemove(Node<Key, Value>* node_to_remove) {
    // check if node to remove exists
    if (node_to_remove == nullptr) {
        return;
    }

    // case 1: 0 children
    if (node_to_remove->getLeft() == nullptr && node_to_remove->getRight() == nullptr) {
        Node<Key, Value>* parent = node_to_remove->getParent();

        if (parent == nullptr) {
            root_ = nullptr;
        }
        // figure out whether it is a left or right child
        else if (parent->getLeft() == node_to_remove) {
            parent->setLeft(nullptr);
        }
        else {
            parent->setRight(nullptr);
        }

        delete node_to_remove;
        return;
    }

    // case 2: 1 child only
    // case 1a) if left child
    if (node_to_remove->getLeft()!=nullptr && node_to_remove->getRight()==nullptr) {
        Node<Key, Value>* temp = node_to_remove;
        Node<Key, Value>* removed_parent = node_to_remove->getParent();
        node_to_remove = node_to_remove->getLeft();
        if (removed_parent!=nullptr) {
            // can be right child
            if (removed_parent->getLeft() == temp) {
                removed_parent->setLeft(node_to_remove);
            }
            else {
                removed_parent->setRight(node_to_remove);
            }
        }
        else {
            root_ = node_to_remove;
        }
        node_to_remove->setParent(removed_parent);
        delete temp;
        return;
    }
    // case 1b) if right child
    if (node_to_remove->getRight()!=nullptr && node_to_remove->getLeft()==nullptr) {
        Node<Key, Value>* temp = node_to_remove;
        Node<Key, Value>* removed_parent = node_to_remove->getParent();
        node_to_remove = node_to_remove->getRight();
        if (removed_parent!=nullptr) {
            // can be left child
            if (removed_parent->getLeft() == temp) {
                removed_parent->setLeft(node_to_remove);
            }
            else {
                removed_parent->setRight(node_to_remove);
            }
        }
        else {
            root_ = node_to_remove;
        }
        node_to_remove->setParent(removed_parent);
        delete temp;
        return;
    }

    // case 3: both children
    Node<Key, Value>* predecessor = BinarySearchTree<Key, Value>::predecessor(node_to_remove);
    this->nodeSwap(node_to_remove, predecessor);
    recursiveRemove(node_to_remove);
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* node_to_remove = internalFind(key);
    recursiveRemove(node_to_remove);
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::findRoot(Node<Key, Value>* current) const {
    while (current->getParent() != nullptr) {
        current = current->getParent();
    }
    return current;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if (current->getLeft() != nullptr) {
        return BinarySearchTree<Key, Value>::recursiveLargest(current->getLeft());
    }
    else {
        return BinarySearchTree<Key, Value>::ancestorRightChild(current);
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current) {
    if (current->getRight() != nullptr) {
        return BinarySearchTree<Key, Value>::recursiveSmallest(current->getRight());
    }
    else {
        return BinarySearchTree<Key, Value>::ancestorLeftChild(current);
    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::ancestorRightChild(Node<Key, Value>* current) {
    if (current->getParent() == nullptr) {
        return nullptr;
    }

    if (current->getParent()->getRight() == current) {
        return current->getParent();
    }
    else {
        return BinarySearchTree<Key, Value>::ancestorRightChild(current->getParent());
    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::ancestorLeftChild(Node<Key, Value>* current) {
    if(current->getParent() == nullptr) {
        return nullptr;
    }

    if (current->getParent()->getLeft() == current) {
        return current->getParent();
    }
    else {
        return BinarySearchTree<Key, Value>::ancestorLeftChild(current->getParent());
    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::recursiveLargest(Node<Key, Value>* current) {
    if (current->getRight() == nullptr) {
        return current;
    }
    else {
        return BinarySearchTree<Key, Value>::recursiveLargest(current->getRight());
    }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    while(this->root_ != nullptr) {
        this->remove(root_->getKey());
        // this->printRoot(root_);
    }
}


/**
* A helper function to find the smallest node in the tree.
*/
// keep hitting left until there's no more
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    if (root_ == nullptr) {
        return nullptr;
    }
    return BinarySearchTree<Key, Value>::recursiveSmallest(root_);
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::recursiveSmallest(Node<Key, Value>* current) {
    if (current->getLeft() == nullptr) {
        return current;
    }
    else {
        return BinarySearchTree<Key, Value>::recursiveSmallest(current->getLeft());
    }
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    return recursiveFind(root_, key);
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::recursiveFind(Node<Key, Value>* current, const Key& key) const {
    if (current == nullptr) {
        return nullptr;
    }

    if (current->getKey() == key) {
        return current;
    }

    if (key < current->getKey()) {
        return recursiveFind(current->getLeft(), key);
    }

    if (key > current->getKey()) {
        return recursiveFind(current->getRight(), key);
    }

    return nullptr; // just to silence warning
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    return isBalanced_recursive(this->root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced_recursive(Node<Key, Value>* current) const {
    if (current == nullptr) {
        return true;
    }
    int left_height = treeHeight(current->getLeft(), 1);
    int right_height = treeHeight(current->getRight(), 1);
    if (std::abs(left_height-right_height)>1) {
        return false;
    }
    else {
        return (isBalanced_recursive(current->getLeft()) && isBalanced_recursive(current->getRight()) );
    }
}


template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::treeHeight(Node<Key, Value>* root, int count) const {
    if (root == nullptr) {
        return count;
    }
    else {
        return std::max(treeHeight(root->getLeft(), count+1), treeHeight(root->getRight(), count+1));
    }
}




template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
