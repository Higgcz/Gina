//
//  BalancedTrees.cpp
//  Gina
//
//  Created by Vojtech Micka on 06.01.14.
//  Copyright (c) 2014 Vojtech Micka. All rights reserved.
//

#include <algorithm>

#include "AVLTree.h"

using namespace Gina::Structures;

Node* AVLTree::leftRotation  ( Node* root )
{
    if ( root == NULL ) return NULL;
    
    // Get right child
    Node* child = root->right;
    if ( child == NULL ) return root;
    
    Node* tempParent = root->parent;
    
    // Rotate
    root->setRight ( child->left );
    child->setLeft ( root );
    
    if ( tempParent != NULL ) {
        tempParent->setChild ( child );
    } else {
        child->parent = NULL;
    }
    
    return child;
}

Node* AVLTree::rightRotation ( Node* root )
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
    }
    
    return child;
}

Node* AVLTree::leftRightRotation ( Node* root )
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

Node* AVLTree::rightLeftRotation ( Node* root )
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

int AVLTree::getHeight ( Node* n )
{
    if ( n == NULL ) return -1; // Leaf
    
    return 1 + std::max ( getHeight ( n->left ), getHeight ( n->right ));
}

int AVLTree::getBal ( Node* n )
{
    return getHeight ( n->left ) - getHeight( n->right );
}

Node* AVLTree::insertNode  ( int key, int value )
{
    Node* n = new Node ( key, value );
    insertNode ( n );
    return n;
}

void AVLTree::insertNode ( Node *n )
{
    Node* cur, *fcur;   // Current sub-tree and its father
    Node* a, *b;        // Smallest unbalanced tree and its son
    bool found = false; // Node with the same key as n found
    
    cur = root;
    fcur = NULL;
    a = cur;
    b = NULL;
    int bal_a = 0; // Remember bal
    
    while (( cur != NULL ) && !found ) {
        
        if ( n->key == cur->key ) {
            found = true;
        } else {
            fcur = cur;
            cur = n->key < cur->key ? cur->left : cur->right;
            
            if (( cur != NULL ) && (( getBal ( cur )) != 0 )) {
                a = cur;
            }
        }
    }
    
    if ( found ) {
        n->copyData ( cur );
    } else {
        if ( fcur == NULL ) {
            root = n->clearRelations ();
            return;
        } else {
            if ( n->key < fcur->key ) {
                fcur->setLeft ( n->clearRelations ());
            } else {
                fcur->setRight ( n->clearRelations ());
            }
        }
        
        bal_a = getBal ( a );
        if ( bal_a == 2 ) {                     // Inserted left from 1
            
            b = a->left;
            if ( b->key < n->key ) {            // and right from its left son
                a->left = leftRotation ( b );   // L rotation (LR)
            }
            a = rightRotation ( a );            // R rotation
            
        } else if ( bal_a == -2 ) {             // Inserted right from -1
            
            b = a->right;
            if ( n->key < b->key ) {            // and left from its right son
                a->right = rightRotation ( b );
            }
            a = leftRotation ( a );
            
        } // else tree remained balanced
        
        if ( a->parent == NULL ) {
            root = a;
        }
    }
    
    n_count++;
}

Node* AVLTree::deleteKey ( int key )
{
    Node* delNode = searchKey ( key );
    if ( delNode == NULL ) return NULL;
    
    return deleteNode ( delNode );
}

Node* AVLTree::deleteNode ( Node *nodeToDelete )
{
    Node *nodeToReplace = Tree::deleteNode ( nodeToDelete );
    
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

Node* AVLTree::searchKey ( int key ) const
{
    return Tree::searchKey ( key );
}

Node* AVLTree::minEl () const
{
    return Tree::minEl ();
}

Node* AVLTree::maxEl () const
{
    return Tree::maxEl ();
}

void AVLTree::printLinear ( Node* focusNode ) const
{
    Tree::printLinear ( focusNode );
}

void AVLTree::printLinear () const
{
    Tree::printLinear ();
}

void AVLTree::print ( Node* focusNode, int indent ) const
{
    Tree::print ( focusNode, indent );
}

void AVLTree::print () const
{
    Tree::print ();
}