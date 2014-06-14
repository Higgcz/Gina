//
//  Tree.h
//  Gina
//
//  Created by Vojtech Micka on 06.01.14.
//  Copyright (c) 2014 Vojtech Micka. All rights reserved.
//

#ifndef __Gina__Tree__
#define __Gina__Tree__

#include <iostream>
#include <deque>

namespace Gina {
    namespace Structures {
        struct Node;
        class Tree;
    }
}

struct Gina::Structures::Node {
    int key;
    int value;
    Node *parent;
    Node *left;
    Node *right;
    
    Node ( int k ) :        key(k), value(0), left(NULL), right(NULL), parent(NULL) {};
    Node ( int k, int v ) : key(k), value(v), left(NULL), right(NULL), parent(NULL) {};
    
    virtual void setLeft  ( Node *left );
    virtual void setRight (Node *right );
    virtual void setChild ( Node *n );
    
    virtual bool hasLeft  () const;
    virtual bool hasRight () const;
    
    virtual Node* nextForKey ( int key ) const;
    virtual Node* copyData ( Node *node );
    virtual Node* clearRelations ();
    
    virtual void print () const;
    
    void operator=  ( const Node &n ) { key = n.key; value = n.value; }
    bool operator<  ( const Node &n ) { return key < n.key; }
    bool operator>  ( const Node &n ) { return key > n.key; }
    bool operator== ( const Node &n ) { return key == n.key; }
    bool operator!= ( const Node &n ) { return key != n.key; }
};

class Gina::Structures::Tree {

protected:
    Node *root;
    size_t n_count;

public:
    
    Tree():root(NULL) {};

    virtual void  insertNode  ( Node *n );
    virtual Node* insertNode  ( int key, int value );
    virtual Node* deleteKey   ( int key );
    virtual Node* deleteNode  ( Node *n );
    virtual Node* searchKey   ( int key ) const;
    virtual Node* minEl() const;
    virtual Node* maxEl() const;
    
    virtual size_t count () const {return n_count;}
    
    virtual void  printLinear ( Node* focusNode ) const;
    virtual void  printLinear () const;
    virtual void  print () const;
    virtual void  print ( Node* focusNode, int indent = 0 ) const;
    
protected:
    Node* minForNode ( Node *n ) const;
    Node* maxForNode ( Node *n ) const;
    void printBranches ( int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out ) const;
    void printNodes ( int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out ) const;
    void printLeaves ( int indentSpace, int level, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out ) const;
    void printPretty ( Node* root, int level, int indentSpace, std::ostream& out ) const;
    int maxHeight ( Node* p ) const;

    
};


#endif /* defined(__Gina__Tree__) */
