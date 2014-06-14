//
//  Helpers.cpp
//  Gina
//
//  Created by Vojtech Micka on 19.11.13.
//  Copyright (c) 2013 Vojtech Micka. All rights reserved.
//

#include "Helpers.h"

#include <vector>
#include <set>

#include "Graph.h"
#include "Types.h"

#include "HashMap.h"

using namespace std;
using namespace Gina::Graphs;

// UnionFind
UnionFind::UnionFind ( size_t dim ) : dim ( dim )
{
    parentForNode = new aval [ dim ];
    rankForNode   = new aval [ dim ];
    
    for (int i = 0; i < dim; i++) {
        parentForNode [ i ] = i;
        rankForNode   [ i ] = 1;
    }
}

UnionFind::~UnionFind ()
{
    delete [] parentForNode;
    delete [] rankForNode;
}

aval UnionFind::nFind ( aval node )
{
    if ( node >= dim ) return -1;
    
    aval parent = parentForNode [ node ];
    
    while ( parentForNode [ parent ] != parent ) {
        parent = parentForNode [ parent ];
    }
    
    if ( parentForNode [ node ] != parent )
        parentForNode [ node ] = parent;
    
    return parent;
}

bool UnionFind::nUnion ( aval node1, aval node2 ) {
    aval root1 = nFind ( node1 );
    aval root2 = nFind ( node2 );
    
    if ( root1 == root2 || root1 == -1 || root2 == -1 ) return false;
    
    if ( rankForNode  [ root1 ]  > rankForNode [ root2 ] ) {
        parentForNode [ root2 ]  = root1;
        rankForNode   [ root2 ] += rankForNode [ root1 ];
    } else {
        parentForNode [ root1 ]  = root2;
        rankForNode   [ root1 ] += rankForNode [ root1 ];
    }
    
    return true;
}

Helpers::Certificate
Helpers::calculateCertificate (
                      Graph &tree    // Tree for what we want to compute certificate
)
{
    Graph cTree = tree;
    
    Map::HashMap<int, Certificate> labels ( cTree.size() );
    
    // Label all vertices of G with the string "01"
    for ( int i = 0; i < cTree.size (); i++ ) {
        labels [ cTree.getNode ( i )->_id ] = "01";
    }
    
    // While there are more than two vertices of G do:
    while ( cTree.size () > 2 ) {
        
        // Find all adj nodes to leaves
        set<Node* > allLeaves;
        set<Node* > adjNodes;
        Node *n;
        for ( int i = 0; i < cTree.size (); i++ ) {
            n = cTree.getNode ( i );
            if ( n->degreeOut () == 1 ) {
                adjNodes.insert ( n->_next [ 0 ] );
            }
        }
        
        // Get first non-leaf node
        for ( set<Node *>::iterator it = adjNodes.begin(); it != adjNodes.end(); ++it ) {
            n = *it;
            
//            cout << "\nTesting Node: " << n->_id << endl;
            
            // Get set of leaves ajdacent to the n
            vector<Node* > leaves;
            vector<Certificate> leavesLabels;
            for ( vector<Node *>::iterator it = n->_next.begin(); it != n->_next.end(); ++it ) {
                if ( (*it)->degreeOut() == 1 ) {
                    leaves.push_back (( *it ));
                    leavesLabels.push_back ( labels [ (*it)->_id ] );
                    allLeaves.insert (( *it ));
                }
            }
            
            // If no leaves was found - continue
            if ( leaves.empty ()) continue;
            
//            cout << "\nFound leaves:\n";
//            for ( int i = 0; i < leavesLabels.size(); i++ ) {
//                cout << leaves [ i ]->_id << " : " << leavesLabels [ i ] << "\n";
//            }
            
//            cout << "\n";
//            labels.print(); cout << "\n";
            Certificate& nCert = labels [ n->_id ];
            
            
//            cout << "Cur cert: " << nCert << "\n";
            // Add n certificate without initial 0 and trailing 1
            if ( nCert.size() > 2 ) {
                leavesLabels.push_back ( nCert.substr ( 1, nCert.size() - 2 ));
            }
            
            // Sort in lexicovgraphic order
            sort ( leavesLabels.begin (), leavesLabels.end ());
            
//            cout << "Leaves sorted:\n";
//            for ( int i = 0; i < leavesLabels.size(); i++ ) {
//                cout << leavesLabels [ i ] << "\n";
//            }
//            cout << "\n";
            
            // Create concetenation of the labels in leavesLabels
            nCert = "0";
            for ( vector<Certificate>::iterator it = leavesLabels.begin(); it != leavesLabels.end(); ++it ) {
                nCert += *it;
            }
            nCert += "1";
            
//            cout << "Create concetenation: " << nCert << endl;
            
            
        }
        
        // Remove leaves
        for ( set<Node* >::iterator it = allLeaves.begin(); it != allLeaves.end(); ++it ) {
            cTree.removeNode (( *it ));
        }
        allLeaves.clear();
    }
    
    if ( cTree.size () == 1 ) {
        return labels [ cTree.getNode ( 0 )->_id ];
    } else if ( cTree.size() == 2 ) {
        
        Certificate first  = labels [ cTree.getNode ( 0 )->_id ];
        Certificate second = labels [ cTree.getNode ( 1 )->_id ];
        
        return ( first < second ) ? first + second : second + first;
    }
    
    return "";
}


















