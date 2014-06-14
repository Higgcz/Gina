//
//  HashMap.cpp
//  Gina
//
//  Created by Vojtech Micka on 07.01.14.
//  Copyright (c) 2014 Vojtech Micka. All rights reserved.
//

#ifndef __Gina__HashMap__hpp__
#define __Gina__HashMap__hpp__

using namespace api::Map;

template < typename K, typename V, typename F >
HashMap<K, V, F>::HashMap ( const size_t size ) : _size ( size )
{
    _map = new HashNode<K, V> * [ size ]();
}

template < typename K, typename V, typename F >
HashMap<K, V, F>::~HashMap ()
{
    for ( int i = 0; i < _size; i++ ) {
        
        HashNode<K, V> * entry = _map [ i ];
        while ( entry != NULL ) {
            
            HashNode<K, V> * prev = entry;
            entry = entry->next;
            delete prev;
            
        }
        _map [ i ] = NULL;
    }
    
    delete [] _map;
}

template < typename K, typename V, typename F >
V& HashMap<K, V, F>::operator[] ( const K &key )
{
    unsigned long hash = _hashFunction ( key ) % _size;
    
    HashNode<K, V> * node = _map [ hash ];
    HashNode<K, V> * prev = NULL;
    
    while ( node != NULL ) {
        
        if ( node->key == key ) {
            return node->value;
        }
        
        prev = node;
        node = node->next;
    }
    
    // No element for this key was found
    
    if ( node == NULL ) {
        node = new HashNode <K, V> ( key );
        
        if ( prev == NULL ) {
            // First element in bucket
            _map [ hash ] = node;
        } else {
            // Put element to the end of bucket
            prev->next = node;
        }
    }
    
    return node->value;
}

template < typename K, typename V, typename F >
bool HashMap<K, V, F>::get ( const K &key, V &value )
{
    unsigned long hash = _hashFunction ( key ) % _size;
    
    HashNode<K, V> * node = _map [ hash ];
    
    while ( node != NULL ) {
        
        if ( node->key == key ) {
            value = node->value;
            return true;
        }
        
        node = node->next;
    }
    
    return false;
}

template < typename K, typename V, typename F >
void HashMap<K, V, F>::put ( const K &key, const V &value )
{
    unsigned long hash = _hashFunction ( key ) % _size;
    
    HashNode<K, V> * node = _map [ hash ];
    HashNode<K, V> * prev = lastInBucket ( node, key );
    
    if ( node == NULL ) {
        
        node = new HashNode <K, V> ( key, value );
        
        if ( prev == NULL ) {
            // First element in bucket
            _map [ hash ] = node;
        } else {
            // Put element to the end of bucket
            prev->next = node;
        }
        
    } else {
        // Update existing
        node->value = value;
    }
}

template < typename K, typename V, typename F >
void HashMap<K, V, F>::remove ( const K &key )
{
    unsigned long hash = hashFunction ( key ) % _size;
    
    HashNode<K, V> * node = _map [ hash ];
    HashNode<K, V> * prev = lastInBucket ( node, key );
    
    if ( node == NULL ) {
        // Key wasn't found
        return;
    } else {
        if ( prev == NULL ) {
            _map [ hash ] = node->next;
        } else {
            prev->next = node->next;
        }
        
        delete node;
    }
}

#endif /* defineds(__Gina__HashMap__hpp__) */