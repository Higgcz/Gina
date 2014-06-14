//
//  SplayTree.cpp
//  Gina
//
//  Created by Vojtech Micka on 06.01.14.
//  Copyright (c) 2014 Vojtech Micka. All rights reserved.
//

#include "SplayTree.h"

#include <algorithm>

using namespace api::Structures;

Node* SplayTree::leftRotation  ( Node* root )
{
    if ( root == NULL ) return NULL;
    
    // Get right child
    Node* child = root->right;
    if ( child == NULL ) return root;
    
    Node* tempParent = root->parent;
    
    // Rotate
    
    root ->setRight ( child->left );
    child->setLeft  ( root );
    
    if ( tempParent != NULL ) {
        tempParent->setChild ( child );
    } else {
        child->parent = NULL;
        this->root = child;
    }
    
    return child;
}

Node* SplayTree::rightRotation ( Node* root )
{
    if ( root == NULL ) return NULL;
    
    // Get left child
    Node* child = root->left;
    if ( child == NULL ) return root;
    
    Node* tempParent = root->parent;
    
    // Rotate
    root ->setLeft  ( child->right );
    child->setRight ( root );
    
    if ( tempParent != NULL ) {
        tempParent->setChild ( child );
    } else {
        child->parent = NULL;
        this->root = child;
    }
    
    return child;
}

Node* SplayTree::leftRightRotation ( Node* root )
{
    if ( root == NULL ) return NULL;
    
    Node* leftChild = root->left;
    if ( leftChild == NULL ) return root;
    
    Node* leftRightChild = leftChild->right;
    if ( leftRightChild == NULL ) return root;
    
    leftChild     ->setRight ( leftRightChild->left );
    leftRightChild->setRight ( root );
    leftRightChild->setLeft  ( leftChild );
    
    return leftRightChild;
}

Node* SplayTree::rightLeftRotation ( Node* root )
{
    if ( root == NULL ) return NULL;
    
    Node* rightChild = root->right;
    if ( rightChild == NULL ) return root;
    
    Node* rightLeftChild = rightChild->left;
    if ( rightLeftChild == NULL ) return root;
    
    rightChild    ->setLeft  ( rightLeftChild->right );
    rightLeftChild->setLeft  ( root );
    rightLeftChild->setRight ( rightChild );
    
    return rightLeftChild;
    
}

void SplayTree::splay ( Node* node )
{
    if ( node == NULL ) return;

    Node* parent;
    while ( node->parent ) {
        parent = node->parent;
        
        if ( !parent->parent ) {
            // Node is before root (Just Zig or Zag)
            if ( parent->left == node ) rightRotation ( parent ); // Zig (Node is left child)
            else                        leftRotation  ( parent ); // Zag (Node is right child)
        } else if ( parent->left == node && parent->parent->left == node->parent ) {
            // Zig-Zig
            rightRotation ( parent->parent );
            rightRotation ( parent );
        } else if ( parent->right == node && parent->parent->right == node->parent ) {
            // Zag-zag
            leftRotation ( parent->parent );
            leftRotation ( parent );
        } else if ( parent->left  == node && parent->parent->right == node->parent ) {
            // Zag-Zig
            rightRotation ( parent );
            leftRotation  ( parent );
        } else {
            // Zig-Zag
            leftRotation  ( parent );
            rightRotation ( parent );
        }
    }
}

int SplayTree::getHeight ( Node* n )
{
    if ( n == NULL ) return -1; // Leaf
    
    return 1 + std::max ( getHeight ( n->left ), getHeight ( n->right ));
}

int SplayTree::getBal ( Node* n )
{
    return getHeight ( n->left ) - getHeight( n->right );
}

Node* SplayTree::insertNode  ( int key, int value )
{
    Node* n = new Node ( key, value );
    insertNode ( n );
    return n;
}

void SplayTree::insertNode ( Node *node )
{
    Tree::insertNode ( node );
    splay ( node );
}

Node* SplayTree::deleteKey ( int key )
{
    Node* delNode = searchKey ( key );
    if ( delNode == NULL ) return NULL;
    
    return deleteNode ( delNode );
}

Node* SplayTree::deleteNode ( Node *nodeToDelete )
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
    
    Node* a = NULL, * b = NULL;
    
    if ( nodeToDelete->hasLeft () || nodeToDelete->hasRight ()) {
        a = nodeToDelete;
    } else {
        a = nodeToDelete->parent;
    }
    
    if ( a == NULL ) return nodeToReplace;
    
    // Check for rotations
    int bal_a = getBal ( a );
    if ( bal_a == 2 ) {                     // Inserted left from 1
        
        b = a->left;
        if ( b->key < nodeToDelete->key ) {            // and right from its left son
            a->left = leftRotation ( b );   // L rotation (LR)
        }
        a = rightRotation ( a );            // R rotation
        
    } else if ( bal_a == -2 ) {             // Inserted right from -1
        
        b = a->right;
        if ( nodeToDelete->key < b->key ) {            // and left from its right son
            a->right = rightRotation ( b );
        }
        a = leftRotation ( a );
        
    } // else tree remained balanced
    
    if ( a->parent == NULL ) {
        root = a;
    }
    
    return nodeToReplace;
}

Node* SplayTree::searchKey ( int key )
{
    Node* n = Tree::searchKey ( key );
    splay ( n );
    return n;
}

Node* SplayTree::minEl () const
{
    return Tree::minEl ();
}

Node* SplayTree::maxEl () const
{
    return Tree::maxEl ();
}

void SplayTree::printLinear ( Node* focusNode ) const
{
    Tree::printLinear ( focusNode );
}

void SplayTree::printLinear () const
{
    Tree::printLinear ();
}

void SplayTree::print ( Node* focusNode, int indent ) const
{
    Tree::print ( focusNode, indent );
}

void SplayTree::print () const
{
    Tree::print ();
}