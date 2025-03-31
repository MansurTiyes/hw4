#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <algorithm>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int path_to_leaf(Node* root, int count);

bool equalPaths(Node * root)
{
    // Add your code below
    if (root==nullptr) {
        return true;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return true;
    }
    if (root->left == nullptr && root->right != nullptr) {
        return equalPaths(root->right);
    }
    if (root->right == nullptr && root->left != nullptr) {
        return equalPaths(root->left);
    }
    if (path_to_leaf(root->left, 1) == path_to_leaf(root->right, 1)) {
        return true;
    }
    else {
        return false;
    }
}

int path_to_leaf(Node* root, int count) {
    if (root->left==nullptr && root->right==nullptr) {
        return count++;
    }
    if (root->right == nullptr) {
        return path_to_leaf(root->left, count+1);
    }
    if (root->left == nullptr) {
        return path_to_leaf(root->right, count+1);
    }
    return max(path_to_leaf(root->left, count+1), path_to_leaf(root->right, count+1));
}

