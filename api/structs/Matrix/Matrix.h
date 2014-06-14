//
//  Matrix.h
//  Gina
//
//  Created by Vojtech Micka on 16.11.13.
//  Copyright (c) 2013 Vojtech Micka. All rights reserved.
//

#ifndef __Gina__Matrix__h__
#define __Gina__Matrix__h__

#include <iostream>
#include <assert.h>

#include "Types.h"

namespace api {
    namespace Matrix {
        template <bool _symetric, typename _T> class SquareMatrix;
    }
}

////////////////////////////////////////////////////////////////////////////////
// SQUARE_MATRIX Definition
////////////////////////////////////////////////////////////////////////////////

template <bool _symetric = false, typename _T = int>
class api::Matrix::SquareMatrix {
    _T*          _vals;
    const size_t _size;
    const bool   _symetricFlag   = _symetric;

public:
    
    SquareMatrix  ();
    SquareMatrix  (size_t size);
    SquareMatrix  (const SquareMatrix &m);
    
    ~SquareMatrix () {
        delete [] _vals;
    }
    
    void    set         (uint x, uint y, _T val);
    _T      &get        (uint x, uint y);
    _T      &operator() (uint x, uint y);
    
    void    print();
    
private:
    void rangeCheck (uint x, uint y);    
};

#include "Matrix.hpp"

#endif /* defined(__Gina__Matrix__h__) */
