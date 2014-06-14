//
//  HashMap.h
//  Gina
//
//  Created by Vojtech Micka on 07.01.14.
//  Copyright (c) 2014 Vojtech Micka. All rights reserved.
//

#ifndef __Gina__HashMap__
#define __Gina__HashMap__

#include <iostream>

namespace Gina {
    namespace Map {
        template < typename K >
            struct DefaultHashFunction;
        template < typename K, typename V, class F = DefaultHashFunction<K> >
            class  HashMap;
        template < typename K, typename V >
            struct  HashNode;
    }
}

template < >
struct Gina::Map::DefaultHashFunction<int> {
    unsigned long operator() ( const int &key ) const
    {
        return key;
    }
};

template < >
struct Gina::Map::DefaultHashFunction<std::string> {
    unsigned long operator() ( const std::string &key ) const
    {
        unsigned long n = 5381UL;
        int i;
        
        for (i = 0; i < key.length(); i++) {
            n = n * 33UL + key [ i ];
        }
        return n;
    }
};

template < typename K >
struct Gina::Map::DefaultHashFunction {
    unsigned long operator() ( const K &key ) const
    {
        return reinterpret_cast<unsigned long> ( key );
    }
};

template < typename K, typename V >
struct Gina::Map::HashNode {
    K           key;
    V           value;
    HashNode*   next;
    
    HashNode () : next ( NULL ) {};
    HashNode ( const K &key ) : key ( key ), next ( NULL ) {};
    HashNode ( const K &key, const V &value ) : key ( key ), value ( value ), next ( NULL ) {};
    
    void print ()
    {
        std::cout << "(" << key << ", " << value << ")";
        if ( next != NULL ) {
            std::cout << " -> ";
            next->print();
        }
    }
};

template < typename K, typename V, typename F >
class Gina::Map::HashMap {
    
    HashNode <K, V> ** _map;
    F                  _hashFunction;
    size_t             _size;
    
public:
    V EMPTY_VALUE;
    
    HashMap  ( const size_t size );
    ~HashMap ();
    
    bool get    ( const K &key, V &value );
    void put    ( const K &key, const V &value );
    void remove ( const K &key );
    
    V& operator[] ( const K &key );
    
    void print ()
    {
        for ( int i = 0; i < _size; i++ ) {
            HashNode<K,V> *node = _map [ i ];
            if ( node != NULL ) {
                _map [ i ]->print ();
            } else {
                std::cout << "EMPTY BUCKET";
            }
            std::cout << std::endl;
        }
    }
    
private:
    
    inline HashNode<K, V>* lastInBucket ( HashNode<K, V>* &node, const K &key )
    {
        HashNode<K, V>* prev = NULL;
        while ( node != NULL && node->key != key ) {
            prev = node;
            node = node->next;
        }
        return prev;
    }
    
};

#include "HashMap.hpp"

#endif /* defined(__Gina__HashMap__) */
