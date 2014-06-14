//
//  Tree.cpp
//  Gina
//
//  Created by Vojtech Micka on 06.01.14.
//  Copyright (c) 2014 Vojtech Micka. All rights reserved.
//

#include <iomanip>
#include <math.h>
#include "Tree.h"

using namespace std;
using namespace api::Structures;

void Node::setLeft ( Node *left )
{
    if ( left != NULL ) left->parent = this;
    this->left = left;
}

void Node::setRight ( Node *right )
{
    if ( right != NULL ) right->parent = this;
    this->right = right;
}

void Node::setChild ( Node *n )
{
    if ( n == NULL ) return;
    if ( this->key > n->key ) {
        setLeft  (n);
    } else {
        setRight (n);
    }
        
}

bool Node::hasLeft () const
{
    return left != NULL;
}

bool Node::hasRight () const
{
    return right != NULL;
}

Node* Node::nextForKey ( int k ) const
{
    return k > this->key ? this->right : this->left;
}

Node* Node::clearRelations ()
{
    this->left   = NULL;
    this->right  = NULL;
    this->parent = NULL;
    
    return this;
}

Node* Node::copyData ( Node *node )
{
    this->key   = node->key;
    this->value = node->value;
    
    return this;
}

void Node::print () const
{
    printf ( "Node [ %3d ]\t=\t%d\n", this->key, this->value );
}

Node* Tree::insertNode  ( int key, int value )
{
    Node* n = new Node ( key, value );
    insertNode ( n );
    return n;
}

void Tree::insertNode ( Node *node )
{
    // Find the node where to put the new key
    Node* n = root, * parent = NULL;
    if ( n == NULL ) {
        root = node;
        return;
    }
    
    while ( n != NULL ) {
        parent = n;
        n = *n > *node ? n->left : n->right;
    }
    
    if ( *parent == *node ) {
        parent->copyData ( node );
        return;
    }
    
    parent->setChild ( node );
    
    n_count++;
}

Node* Tree::deleteKey ( int key )
{
    Node* delNode = searchKey ( key );
    if ( delNode == NULL ) return NULL;
    
    return deleteNode ( delNode );
}

Node* Tree::deleteNode ( Node *nodeToDelete )
{
    Node *nodeToReplace = NULL, *child = NULL;
    
    // Test if Node has only one or none children
    if ( !nodeToDelete->hasLeft () || !nodeToDelete->hasRight ()) {
        nodeToReplace = nodeToDelete;
    } else {
        nodeToReplace = maxForNode ( nodeToDelete->left );
    }
    
    // Find the child of node to replace
    if ( nodeToReplace->hasLeft ()) {
        child = nodeToReplace->left;
    } else {
        child = nodeToReplace->right;
    }
    
    if ( child != NULL ) {
        child->parent = nodeToReplace->parent;
    }
    
    if ( nodeToReplace->parent == NULL ) {
        root = nodeToReplace;
    } else if ( nodeToReplace == nodeToReplace->parent->left ) {
        nodeToReplace->parent->left  = child;
    } else {
        nodeToReplace->parent->right = child;
    }
    
    // Copy data instead of delete
    if ( nodeToReplace != nodeToDelete ) {
        nodeToDelete->copyData ( nodeToReplace );
    }
    
    n_count--;
    return nodeToReplace;
}

Node* Tree::searchKey ( int key ) const
{
    Node* n = root;
    while ( n != NULL && n->key != key ) {
        n = n->key > key ? n->left : n->right;
    }
    return n;
}

Node* Tree::minEl () const
{
    return minForNode ( root );
}

Node* Tree::maxEl () const
{
    return maxForNode ( root );
}

// Private Tree methods

Node* Tree::minForNode ( Node *n ) const
{
    if ( n->left == NULL ) return n;
    return minForNode ( n->left );
}

Node* Tree::maxForNode ( Node *n ) const
{
    if ( n->right == NULL ) return n;
    return maxForNode ( n->right );
}

void Tree::printLinear ( Node* focusNode ) const
{
    if ( focusNode != NULL ) {
        printLinear ( focusNode->left );
        focusNode->print ();
        printLinear ( focusNode->right );
    }
}

void Tree::printLinear () const
{
    if ( root != NULL ) {
        printLinear ( root->left );
        root->print ();
        printLinear ( root->right );
    }
}

void Tree::print () const
{
    printPretty ( root, 1, 1, cout );
}

void Tree::print ( Node* focusNode, int indent ) const
{
    printPretty ( focusNode, 1, indent, cout );
}

///////////////////////////////////////////////////////////////////////////////////////
// Prety print
///////////////////////////////////////////////////////////////////////////////////////
int Tree::maxHeight(Node *p) const
{
    if (!p) return 0;
    int leftHeight = maxHeight(p->left);
    int rightHeight = maxHeight(p->right);
    return (leftHeight > rightHeight) ? leftHeight + 1: rightHeight + 1;
}

// Print the arm branches (eg, /    \ ) on a line
void Tree::printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) const
{
    deque<Node*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel / 2; i++) {
        out << ((i == 0) ? setw(startLen-1) : setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
        out << setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
    }
    out << endl;
}

// Print the branches and node (eg, ___10___ )
void Tree::printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) const
{
    deque<Node*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
        
        if ((*iter) != NULL) {
            out << setw(branchLen+2) << (*iter)->value;
        } else {
            out << setw(branchLen+2) << "";
        }
        
        out << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
    }
    out << endl;
}

// Print the leaves only (just for the bottom row)
void Tree::printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) const
{
    deque<Node*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        if ((*iter) != NULL) {
            out << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << (*iter)->value;
        } else {
            out << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << "";
        }
    }
    out << endl;
}

// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
void Tree::printPretty ( Node *root, int level, int indentSpace, ostream& out ) const
{
    int h = maxHeight(root);
    int nodesInThisLevel = 1;
    
    int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);  // eq of the length of branch for each node of each level
    int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);  // distance between left neighbor node's right arm and right neighbor node's left arm
    int startLen = branchLen + (3-level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)
    
    deque<Node*> nodesQueue;
    nodesQueue.push_back(root);
    for (int r = 1; r < h; r++) {
        printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
        branchLen = branchLen/2 - 1;
        nodeSpaceLen = nodeSpaceLen/2 + 1;
        startLen = branchLen + (3-level) + indentSpace;
        printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
        
        for (int i = 0; i < nodesInThisLevel; i++) {
            Node *currNode = nodesQueue.front();
            nodesQueue.pop_front();
            if (currNode) {
                nodesQueue.push_back(currNode->left);
                nodesQueue.push_back(currNode->right);
            } else {
                nodesQueue.push_back(NULL);
                nodesQueue.push_back(NULL);
            }
        }
        nodesInThisLevel *= 2;
    }
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
    printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}

