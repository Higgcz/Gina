//
//  Matrix.hpp
//  Gina
//
//  Created by Vojtech Micka on 16.11.13.
//  Copyright (c) 2013 Vojtech Micka. All rights reserved.
//

#ifndef __Gina__Matrix__hpp__
#define __Gina__Matrix__hpp__

using namespace api::Matrix;

template <bool _symetric, typename _T>
////////////////////////////////////////////////////////////////
SquareMatrix<_symetric, _T>::SquareMatrix ():
////////////////////////////////////////////////////////////////
    _vals        (NULL),
    _size        (0)
{};

template <bool _symetric, typename _T>
////////////////////////////////////////////////////////////////
SquareMatrix<_symetric, _T>::SquareMatrix (size_t size):
////////////////////////////////////////////////////////////////
    _size        (size)
{
    _vals = new _T [size * size];
    memset(_vals, 0, size * size * sizeof(_T));
}

template <bool _symetric, typename _T>
////////////////////////////////////////////////////////////////
SquareMatrix<_symetric, _T>::SquareMatrix (const SquareMatrix &m):
////////////////////////////////////////////////////////////////
    _size         (m._size),
    _symetricFlag (m._symetricFlag)
{
    _vals = new _T [_size * _size];
    memcpy(_vals, m._vals, _size * _size * sizeof(_T));
}

template <bool _symetric, typename _T>
////////////////////////////////////////////////////////////////
void SquareMatrix<_symetric, _T>::set (uint x, uint y, _T val)
////////////////////////////////////////////////////////////////
{
    rangeCheck (x, y);
    
    _vals [ x + _size * y ] = val;
    if (_symetricFlag)
        _vals [ y + _size * x ] = val;
}

template <bool _symetric, typename _T>
////////////////////////////////////////////////////////////////
_T& SquareMatrix<_symetric, _T>::get (uint x, uint y)
////////////////////////////////////////////////////////////////
{
    rangeCheck (x, y);
    
    if (_symetricFlag && x < y) std::swap (x, y);
    return _vals [ x + _size * y ];
}

template <bool _symetric, typename _T>
////////////////////////////////////////////////////////////////
_T& SquareMatrix<_symetric, _T>::operator() (uint x, uint y)
////////////////////////////////////////////////////////////////
{
    return get (x , y);
}

template <bool _symetric, typename _T>
////////////////////////////////////////////////////////////////
void SquareMatrix<_symetric, _T>::rangeCheck(uint x, uint y)
////////////////////////////////////////////////////////////////
{
    assert ( x < _size && y < _size );
}

template <bool _symetric, typename _T>
////////////////////////////////////////////////////////////////
void SquareMatrix<_symetric, _T>::print()
////////////////////////////////////////////////////////////////
{
    for (int i = 0; i < _size * _size; i++) {
        std::cout << _vals [ i ];
        if ((i+1) % _size) std::cout << " ";
        else              std::cout << "\n";
    }
}

#endif /* defineds(__Gina__Matrix__hpp__) */
