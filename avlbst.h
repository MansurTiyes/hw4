#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rightRotate(AVLNode<Key,Value>* root);
    void leftRotate(AVLNode<Key,Value>* root);
    bool isZigZig(AVLNode<Key,Value>* grandparent, AVLNode<Key,Value>* parent, AVLNode<Key,Value>* current, bool isLeft);
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* current);
    void removeFix(AVLNode<Key, Value>* current, int diff);
};

template<class Key, class Value>
void AVLTree<Key, Value>::rightRotate(AVLNode<Key,Value>* root) {
    AVLNode<Key, Value>* left = root->getLeft();
    root->setLeft(left->getRight());
    // PREDECESSOR MIGHT CHANGE
    if (left->getRight()!=nullptr) {
        left->getRight()->setParent(root);
    }
    AVLNode<Key, Value>* parent = root->getParent();
    left->setParent(parent);
    // UPDATING ROOT, if root used to be root_
    if (parent == nullptr) {
        this->root_ = left;
    }
    // if root was parent left child
    else if (root == parent->getLeft()) {
        parent->setLeft(left);
    }
    else {
        parent->setRight(left);
    }
    left->setRight(root);
    root->setParent(left);
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftRotate(AVLNode<Key,Value>* root) {
    AVLNode<Key, Value>* right = root->getRight();
    root->setRight(right->getLeft());
    if (right->getLeft() != nullptr) {
        right->getLeft()->setParent(root);
    }
    AVLNode<Key, Value>* parent = root->getParent();
    right->setParent(parent);
    // used to be root
    if (parent == nullptr) {
        this->root_ = right;
    }
    else if (root == parent->getLeft()) {
        parent->setLeft(right);
    }
    else {
        parent->setRight(right);
    }
    right->setLeft(root);
    root->setParent(right);

}

template<class Key, class Value>
bool AVLTree<Key, Value>::isZigZig(AVLNode<Key,Value>* grandparent, AVLNode<Key,Value>* parent, AVLNode<Key,Value>* current, bool isLeft) {
    if (isLeft) {
        return ( (grandparent->getLeft()==parent) && (parent->getLeft()==current) );
    }
    else {
        return ( (grandparent->getRight()==parent) && (parent->getRight()==current) );
    }
}

// make one insertFix
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* current) {
    // Base Cases first
    if (parent==nullptr) {
        return;
    }
    AVLNode<Key, Value>* grandparent = parent->getParent();
    if (grandparent == nullptr) {
        return;
    }

    if (grandparent->getLeft() == parent) {
        grandparent->updateBalance(-1);
        // case 1
        if (grandparent->getBalance() == 0) {
            return;
        }

        // case 2
        if (grandparent->getBalance() == -1) {
            this->insertFix(grandparent, parent);
            return;
        }

        // case 3
        if (isZigZig(grandparent, parent, current, true)) {
            this->rightRotate(grandparent);
            parent->setBalance(0);
            grandparent->setBalance(0);
        }
        else {
            this->leftRotate(parent);
            this->rightRotate(grandparent);
            if (current->getBalance() == -1) {
                parent->setBalance(0);
                grandparent->setBalance(1);
                current->setBalance(0);
            }
            else if (current->getBalance() == 0) {
                parent->setBalance(0);
                grandparent->setBalance(0);
                current->setBalance(0);
            }
            else {
                parent->setBalance(-1);
                grandparent->setBalance(0);
                current->setBalance(0);
            }
        }
    }
    else {
        grandparent->updateBalance(1);
        // case 1
        if (grandparent->getBalance() == 0) {
            return;
        }

        // case 2
        if (grandparent->getBalance() == 1) {
            this->insertFix(grandparent, parent);
            return;
        }

        // case 3
        if (isZigZig(grandparent, parent, current, false)) {
            this->leftRotate(grandparent);
            parent->setBalance(0);
            grandparent->setBalance(0);
        }
        else {
            this->rightRotate(parent);
            this->leftRotate(grandparent);
            if (current->getBalance() == 1) {
                parent->setBalance(0);
                grandparent->setBalance(-1);
                current->setBalance(0);
            }
            else if (current->getBalance() == 0) {
                parent->setBalance(0);
                grandparent->setBalance(0);
                current->setBalance(0);
            }
            else {
                parent->setBalance(1);
                grandparent->setBalance(0);
                current->setBalance(0);
            }
        }
    }
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // checking if tree is empty
    if (this->root_ == nullptr) {
        AVLNode<Key, Value>* new_root = new AVLNode<Key,Value>(new_item.first, new_item.second, nullptr);
        this->root_ = new_root;
        return;
    }

    // checking if node already exists in a tree
    AVLNode<Key, Value>* node_to_replace = static_cast<AVLNode<Key, Value>*>(this->internalFind(new_item.first));
    if (node_to_replace!=nullptr) {
        node_to_replace->setValue(new_item.second);
        return;
    }

    AVLNode<Key, Value>* new_node = new AVLNode<Key,Value>(new_item.first, new_item.second, nullptr);
    AVLNode<Key,Value>* parent = static_cast<AVLNode<Key, Value>*>(this->findEmpty(this->root_, new_item.first));
    new_node->setBalance(0);
    bool isLeftChild = false;

    if (new_item.first < parent->getKey()) {
        parent->setLeft(new_node);
        new_node->setParent(parent);
        isLeftChild = true;
    }
    else {
        parent->setRight(new_node);
        new_node->setParent(parent);
    }

    // case 1
    if (parent->getBalance() == -1) {
        parent->setBalance(0);
    }
    // case 2
    else if (parent->getBalance()==1) {
        parent->setBalance(0);
    }
    // case 3
    else if (parent->getBalance() == 0) {
        if (isLeftChild) {
            parent->setBalance(-1);
            this->insertFix(parent, new_node);
        }
        else {
            parent->setBalance(1);
            this->insertFix(parent, new_node);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* current, int diff) {
    if (current == nullptr) {
        return;
    }

    // computing next recusrive call's argument
    AVLNode<Key, Value>* parent = current->getParent();
    // if current is a left child
    int nextdiff = 0;
    if (parent!=nullptr) {
        if (parent->getLeft() == current) {
            nextdiff = 1;
        }
        else {
            nextdiff = -1;
        }
    }

    if (diff == -1) {
        // case 1
        if (current->getBalance() + diff == -2) {
            AVLNode<Key, Value>* tallest_child = current->getLeft();

            // case 1a -> zig-zig case
            if (tallest_child->getBalance() == -1) {
                rightRotate(current);
                current->setBalance(0);
                tallest_child->setBalance(0);
                removeFix(parent, nextdiff);
            }
            // case 1b) zig zig case
            else if (tallest_child->getBalance() == 0) {
                rightRotate(current);
                current->setBalance(-1);
                tallest_child->setBalance(1);
                return;
            }
            else {
                // case 1c  -> zig zag case
                AVLNode<Key, Value>* right = tallest_child->getRight();
                leftRotate(tallest_child);
                rightRotate(current);
                if (right->getBalance() == 1) {
                    current->setBalance(0);
                    tallest_child->setBalance(-1);
                    right->setBalance(0);
                }
                else if (right->getBalance() == 0) {
                    current->setBalance(0);
                    tallest_child->setBalance(0);
                    right->setBalance(0);
                }
                else {
                    current->setBalance(1);
                    tallest_child->setBalance(0);
                    right->setBalance(0);
                }
                if (parent!=nullptr) {
                    removeFix(parent, nextdiff);
                }
            }
        }

        // case 2
        else if (current->getBalance() + diff == -1) {
            current->setBalance(-1);
            return;
        }

        // case 3
        else {
            current->setBalance(0);
            removeFix(parent, nextdiff);
        }
    }

    else {
        // case 1
        if (current->getBalance() + diff == 2) {
            AVLNode<Key, Value>* tallest_child = current->getRight();

            // case 1a -> zig zig
            if (tallest_child->getBalance() == 1) {
                leftRotate(current);
                current->setBalance(0);
                tallest_child->setBalance(0);
                removeFix(parent, nextdiff);
            }
            // case 1b -> also zig zig
            else if (tallest_child->getBalance() == 0) {
                leftRotate(current);
                current->setBalance(1);
                tallest_child->setBalance(-1);
                return;
            }
            // case 1c -> zig zag
            else {
                AVLNode<Key, Value>* left = tallest_child->getLeft();
                rightRotate(tallest_child);
                leftRotate(current);
                if (left->getBalance() == -1) {
                    current->setBalance(0);
                    tallest_child->setBalance(1);
                    left->setBalance(0);
                }
                else if (left->getBalance() == 0) {
                    current->setBalance(0);
                    tallest_child->setBalance(0);
                    left->setBalance(0);
                }
                else {
                    current->setBalance(-1);
                    tallest_child->setBalance(0);
                    left->setBalance(0);
                }
                if (parent!=nullptr) {
                    removeFix(parent, nextdiff);
                }
            }
        }
        // case 2
        else if (current->getBalance() + diff == 1) {
            current->setBalance(1);
            return;
        }
        // case 3
        else {
            current->setBalance(0);
            removeFix(parent, nextdiff);
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    AVLNode<Key, Value>* node_to_remove = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));

    // node doesn't exist
    if (node_to_remove == nullptr) {
        return;
    }

    // if has only left child
    if (node_to_remove->getLeft()!=nullptr && node_to_remove->getRight()==nullptr) {
        this->nodeSwap(node_to_remove, node_to_remove->getLeft());
    }
    // if has only right child
    else if (node_to_remove->getRight()!=nullptr && node_to_remove->getLeft()==nullptr) {
        this->nodeSwap(node_to_remove, node_to_remove->getRight());
    }
    // if 2 children
    else if (node_to_remove->getLeft()!=nullptr && node_to_remove->getRight()!=nullptr) {
        AVLNode<Key, Value>* predecessor = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(node_to_remove));
        this->nodeSwap(node_to_remove, predecessor);
    }

    int diff = 0;
    AVLNode<Key, Value>* parent = node_to_remove->getParent();
    if (parent!=nullptr) {
        if (parent->getLeft() == node_to_remove) {
            diff = 1;
            if ((node_to_remove->getLeft() == nullptr) && (node_to_remove->getRight() == nullptr)) {
                parent->setLeft(nullptr);
            } 
            else {
                if (node_to_remove->getLeft() != nullptr) {
                    parent->setLeft(node_to_remove->getLeft());
                    node_to_remove->getLeft()->setParent(parent);
                }
                else {
                    parent->setLeft(node_to_remove->getRight());
                    node_to_remove->getRight()->setParent(parent);
                }
            }
            // parent->setLeft(node_to_remove->getLeft());
        }
        else {
            diff = -1;
            if ((node_to_remove->getLeft() == nullptr) && (node_to_remove->getRight() == nullptr)) {
                parent->setRight(nullptr);
            } 
            else {
                if (node_to_remove->getRight() != nullptr) {
                    parent->setRight(node_to_remove->getRight());
                    node_to_remove->getRight()->setParent(parent);
                }
                else {
                    parent->setRight(node_to_remove->getLeft());
                    node_to_remove->getLeft()->setParent(parent);
                }
            }
        }
    }
    // removed node was the root
    else {
        this->root_ = nullptr;
    }
    delete node_to_remove;
    this->removeFix(parent, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
