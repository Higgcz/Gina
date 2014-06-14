//
//  Graph.h
//  Gina
//
//  Created by Vojtech Micka on 15.11.13.
//  Copyright (c) 2013 Aisacorp. All rights reserved.
//

#ifndef __Gina__Graph__h__
#define __Gina__Graph__h__

#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>

#include "Matrix.h"

////////////////////////////////////////////////////////////////////////////////
// GRAPHS
////////////////////////////////////////////////////////////////////////////////

namespace api {
    namespace Graphs {
        struct Node;
        
        class Graph;
        class MatrixDefinedGraph;
        class DirectedGraph;
    }
}

struct api::Graphs::Node {
    int                 _id;
    std::vector<Node *> _next;
    std::vector<Node *> _prev;
    
    Node () {
        static int global_id = 0;
        _id = global_id++;
    };
    
    Node ( int i ) : _id ( i ) {};
    
    Node ( const Node &v ): _id ( v._id ), _next ( v._next ), _prev ( v._prev ) {}
    
    ~Node () {};
    
    bool hasNeighbour ( Node *n )
    {
        return std::find(_next.begin(), _next.end(), n) != _next.end();
    }
    
    void addNeighbour ( Node *n )
    {
        _next.push_back (n);
        n->_prev.push_back (this);
    }
    
    void removeNeighbour ( Node* n )
    {
        _next.erase    ( std::find ( _next.begin(), _next.end(), n ));
        n->_prev.erase ( std::find ( _prev.begin(), _prev.end(), n ));
    }
    
    void removeNeighbours ()
    {
        for ( std::vector<Node* >::iterator it = _prev.begin(); it != _prev.end(); ++it ) {
            (*it)->_next.erase ( std::find ( (*it)->_next.begin(), (*it)->_next.end(), this ));
        }
        
        for ( std::vector<Node* >::iterator it = _next.begin(); it != _next.end(); ++it ) {
            (*it)->_prev.erase ( std::find ( (*it)->_prev.begin(), (*it)->_prev.end(), this ));
        }
        
        _next.erase(_next.begin(), _next.end());
        _prev.erase(_prev.begin(), _prev.end());
    }
    
    size_t  degreeIn  () { return _prev.size(); }
    size_t  degreeOut () { return _next.size(); }
    
    virtual Node* withId ( int _id )
    {
        this->_id = _id;
        return this;
    }
    
    virtual void print () {
        std::cout << "(" << _id + 1 << ")";
    };
    
    virtual void printRecursive () {
        print(); std::cout << " --> ";
        for ( std::vector<Node *>::iterator n = _next.begin(); n != _next.end(); ++n ) {
            (*n)->print(); std::cout << ", ";
        }
    }
    
    bool operator== ( const Node &n ) { return n._id == this->_id; }
    bool operator!= ( const Node &n ) { return n._id != this->_id; }
};

class api::Graphs::Graph {
public:
    typedef std::vector<Node*> nodes_t;
    typedef nodes_t::iterator  nodes_it;
    
protected:
    nodes_t _nodes;  // Generalize later
    
public:
    // Methods
    
    Graph ()
    {};
    
    Graph (const Graph &g):
        _nodes (g._nodes)
    {}
    
    Graph (uint size)
    {
        _nodes.reserve (size);
//        for (int i = 0; i < size; i++)
//            _nodes.push_back(new N);
    }
    
    ~Graph ()
    {
//        for (int i = 0; i < _nodes.size(); i++) {
//            delete _nodes [ i ];
//        }
    }
    
    void swap (Graph &g) {
        std::swap(this->_nodes, g._nodes);
    }
    
    Graph& operator= (const Graph &g) {
        if (this != &g)
            Graph (g).swap (*this);
        return *this;
    }
    
    size_t        size ()           { return _nodes.size(); }
    virtual Node* getNode (int _u)  { return _nodes [ _u ]; }
    virtual void  addNode (Node *n) { _nodes.push_back ( n->withId ( (int) size ()) ); }
    
    virtual bool isEdgeExists ( int _u, int _v )
    {
        Node *u = getNode ( _u );
        Node *v = getNode ( _v );
        
        return u->hasNeighbour ( v ) || v->hasNeighbour ( u );
    }
    
    virtual void addEdge ( int _u, int _v )
    {
        Node *u = getNode ( _u );
        Node *v = getNode ( _v );
        
        addEdge ( u, v );
    }
    
    virtual void addEdge ( Node *n1, Node *n2 )
    {
        n1->addNeighbour ( n2 );
        n2->addNeighbour ( n1 );
    }
    
    virtual void removeEdge ( int _u, int _v )
    {
        Node *u = getNode ( _u );
        Node *v = getNode ( _v );
        
        removeEdge ( u, v );
    }
    
    virtual void removeEdge ( Node* n1, Node* n2 )
    {
        n1->removeNeighbour ( n2 );
        n2->removeNeighbour ( n1 );
    }
    
    virtual void removeNode ( Node *n )
    {
        n->removeNeighbours();
        _nodes.erase ( std::find ( _nodes.begin(), _nodes.end(), n ));
    }
    
    virtual void print () {
        for (nodes_it n = _nodes.begin(); n != _nodes.end(); ++n) {
            (*n)->printRecursive(); std::cout << "\n";
        }
    }
    
};

class api::Graphs::MatrixDefinedGraph : public Graph {
    SquareMatrix<true, int>* _vals;
public:
    
    MatrixDefinedGraph ():
        Graph (),
        _vals (NULL)
    {};
    
    MatrixDefinedGraph (const MatrixDefinedGraph &g):
        Graph (g)
    {
        _vals = new SquareMatrix<true, int> ( *g._vals );
    }
    
    MatrixDefinedGraph (uint size):
        Graph (size)
    {
        _vals = new SquareMatrix<true, int>(size);
    }
    
    ~MatrixDefinedGraph ()
    {
        delete _vals;
    }
    
    MatrixDefinedGraph& operator= (const MatrixDefinedGraph &m) {
        Graph::operator= (m);
        return *this;
    }
    
    virtual bool isEdgeExists ( int _u, int _v )
    {
        return (*_vals) (_u , _v) == 1; // Possible > 0 if we allow multigraph
    }
    virtual void addEdge      ( int _u, int _v )
    {
        _vals->set(_u, _v, 1); // (*_vals) (_u , _v) = 1; // Possible += 1 if we allow multigraph
    }

};

class api::Graphs::DirectedGraph : public Graph {
public:
    DirectedGraph ():                         Graph ()       {};
    DirectedGraph ( const DirectedGraph &g ): Graph ( g )    {};
    DirectedGraph ( uint size ):              Graph ( size ) {};
    
    DirectedGraph& operator= ( const DirectedGraph &d ) {
        Graph::operator= ( d );
        return *this;
    }
    
    virtual bool isEdgeExists ( int _u, int _v ) {
        Node *n = this->getNode ( _u );
        return n->hasNeighbour ( this->getNode ( _v ));
    }
    
    virtual void addEdge ( int _u, int _v ) {
        this->getNode ( _u )->addNeighbour ( this->getNode ( _v ));
    }
    
    virtual void addEdge ( Node* n1, Node* n2 ) {
        n1->addNeighbour ( n2 );
    }
    
    virtual void removeEdge ( int _u, int _v ) {
        Graph::removeEdge ( _u, _v );
    }
    
    virtual void removeEdge ( Node* n1, Node* n2 ) {
        n1->removeNeighbour ( n2 );
    }
    
};

#endif /* defined(__Gina__Graph__h__) */
