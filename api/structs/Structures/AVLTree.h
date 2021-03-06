//
//  BalancedTrees.h
//  Gina
//
//  Created by Vojtech Micka on 06.01.14.
//  Copyright (c) 2014 Vojtech Micka. All rights reserved.
//

#ifndef __Gina__BalancedTrees__
#define __Gina__BalancedTrees__

#include <iostream>

#include "Tree.h"

namespace Gina {
    namespace Structures {
        class AVLTree;
    }
}

class Gina::Structures::AVLTree : public Tree {
    
public:
    virtual void  insertNode  ( Node *n );
    virtual Node* insertNode  ( int key, int value );
    virtual Node* deleteKey   ( int key );
    virtual Node* deleteNode  ( Node *n );
    virtual Node* searchKey   ( int key ) const;
    virtual Node* minEl() const;
    virtual Node* maxEl() const;
    
    virtual void  printLinear ( Node* focusNode ) const;
    virtual void  printLinear () const;

    virtual void  print ( Node* focusNode, int indent = 0 ) const;
    virtual void  print () const;
    
    // Rotate
    Node* leftRotation      ( Node* root );
    Node* rightRotation     ( Node* root );
    Node* leftRightRotation ( Node* root );
    Node* rightLeftRotation ( Node* root );
    
private:
    int getHeight ( Node *n );
    int getBal    ( Node *n );
};

#endif /* defined(__Gina__BalancedTrees__) */
