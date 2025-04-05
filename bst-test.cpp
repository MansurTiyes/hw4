#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    // BinarySearchTree<char,int> bt;
    // bt.insert(std::make_pair('F', 20));
    // bt.insert(std::make_pair('D', 20));
    // bt.insert(std::make_pair('H', 20));
    // bt.insert(std::make_pair('C', 20));
    // bt.insert(std::make_pair('E', 20));
    // bt.insert(std::make_pair('G', 20));
    // bt.insert(std::make_pair('I', 20));
    // bt.clear();

    
    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // bt.remove('b');

    // AVL Tree Tests
    AVLTree<int,int> at;
    at.insert(std::make_pair(10,1));
    at.insert(std::make_pair(5,1));
    at.insert(std::make_pair(15,1));
    at.insert(std::make_pair(3,1));
    at.insert(std::make_pair(7,1));
    at.insert(std::make_pair(13,1));
    at.insert(std::make_pair(17,1));
    at.clear();
    at.print();

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // at.remove('b');

    return 0;
}
