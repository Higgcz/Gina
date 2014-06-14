//
//  Helpers.h
//  Gina
//
//  Created by Vojtech Micka on 19.11.13.
//  Copyright (c) 2013 Vojtech Micka. All rights reserved.
//

#ifndef __Gina__Helpers__h__
#define __Gina__Helpers__h__

#include <iostream>
#include <vector>
#include "Graph.h"

namespace api {
    namespace Graphs {
        class UnionFind;
        struct Node;
        
        typedef unsigned int aval;
        
        class Helpers;
    }
}

class api::Graphs::UnionFind {
    size_t dim;
    
    aval* parentForNode;
    aval* rankForNode;
    
public:
    UnionFind  ( size_t dim );
    ~UnionFind ();
    
    aval nFind ( aval node );
    bool nUnion ( aval node1, aval node2 );
    
    inline size_t size () const { return dim; };
};

//namespace api {
//    namespace Graphs {
//
//        typedef std::vector<uint>            map_t;
//        typedef std::vector<std::string>     smap_t;
//        typedef std::map<std::string, map_t> part_t;
//    }
//}
//
class api::Graphs::Helpers {
//
//    static const int    NO_SOL = -1;
//
//    struct Partitions {
//        int n;         // Number of partitions
//        part_t partG1;  // Partition of G1
//        part_t partG2;  // Partition of G2
//
//        Partitions (int n, part_t pG1, part_t pG2):n(n), partG1(pG1), partG2(pG2) {};
//    };
//
    
    
public:
    
    typedef std::string Certificate;
    
    static Certificate
    calculateCertificate (
                          Graph &tree    // Tree for what we want to compute certificate
    );
    
    
    
//
//    template <typename _N>
//    static bool
//    findIsomorphism (
//                     Graph<_N> &g1,     // Graph 1
//                     Graph<_N> &g2      // Graph 2
//    )
//    {
//        Partitions p = getPartitions(g1, g2);
//
//        if (p.n == NO_SOL) return false;
//
//        smap_t partMap;
//
//        //        if (g1._partMap.size() != 0) {
//        //            partMap = g1._partMap;
//        //        }
//
//        // ...
//
//        //        return collectIsomorphism(g1, g2, 0, p.partG2, partMap, map_t (g1.degree()));
//        return collectIsomorphism(g1, g2, 0, p.partG2, partMap, map_t (0));
//    }
//
//    template <typename _N>
//    static Partitions
//    getPartitions (
//                   Graph<_N> &g1,       // Graph 1
//                   Graph<_N> &g2        // Graph 2
//    )
//    {
//        part_t partG1, partG2;
//
//        //        if (g1._partitions.size() != 0) {
//        //            partG1 = g1._partitions;
//        //        } else {
//        //
//        //            for (int i = 0; i < g1.degree(); i++) {
//        //                std::string hash = g1.getVertex(i).calcHashND(g1._seq [ 0 ] );
//        //
//        //
//        //
//        //            }
//        //
//        //        }
//        //
//        //        if (g2._partitions.size() != 0) {
//        //            partG2 = g2._partitions;
//        //        } else {
//        //
//        //
//        //
//        //        }
//
//        return Partitions((int) partG1.size(), partG1, partG2);
//    }
//
//    template <typename _N>
//    static bool
//    collectIsomorphism (
//                        Graph<_N>   &g1,   // Graph 1
//                        Graph<_N>   &g2,   // Graph 2
//                        int         v,     // Starting vertex in G1
//                        part_t  partG2,    // Partitions of G2
//                        smap_t  partMapG1, // Partition mapping as array [ vertices of G1 ] of indices of partitions of G2
//                        map_t   isoMap     // current isomorphism f as array [ vertices of G1 ] of vertices of G2
//    )
//    {
//        //        if (v == g1.degree()) {
//        //            return true;
//        //        }
//
//        map_t R;
//        std::string p = partMapG1 [ v ];
//        bool ok;
//
//        for (map_t::iterator y = partG2 [ p ].begin(); y != partG2 [ p ].end(); ++y) {
//            ok = true;
//
//            for (int u = 0; u < v - 1; u++) {
//
//                if ( (g1.isEdgeExists(u, v) && !g2.isEdgeExists((int) isoMap [ u ], (int) *y)) ||
//                    (!g1.isEdgeExists(u, v) &&  g2.isEdgeExists((int) isoMap [ u ], (int) *y)) ) {
//
//                    ok = false;
//                }
//
//                if ( ok ) {
//                    isoMap [ v ] = *y;
//                    if ( collectIsomorphism (g1, g2, v+1, partG2, partMapG1, isoMap) ) {
//                        return true;
//                    }
//                }
//            }
//        }
//        return false;
//    }
};

#endif /* defined(__Gina__Helpers__h__) */
