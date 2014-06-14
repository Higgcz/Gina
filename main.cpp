#include <iostream>

using namespace std;


#include "Graph.h"
#include "Helpers.h"

using namespace Gina::Graphs;
using namespace std;


int main(int argc, char** argv) {

    Graph graph ( 12 );
    
    for ( int i = 0; i < 12; i++ ) {
        graph.addNode ( new Node ( i ) );
    }
    
    graph.addEdge (0, 1);
    graph.addEdge (1, 3);
    graph.addEdge (0, 2);
    graph.addEdge (2, 11);
    graph.addEdge (2, 10);
    graph.addEdge (0, 8);
    graph.addEdge (8, 9);
    graph.addEdge (0, 5);
    graph.addEdge (5, 4);
    graph.addEdge (5, 7);
    graph.addEdge (7, 6);
    
    Helpers::Certificate cer = Helpers::calculateCertificate ( graph );
    
    cout << "Certificate: " << cer << endl;
    
//    HashMap < int, string > map ( 10 );
//    map.put(1, "ahoj");
//    map.put(5, "jak");
//    map.put(8, "se");
//    map.put(2, "Vojto!");
//    map.put(11, "mas");
//    map.put(21, "pri mesicku");
//    
//    map.print();
//    SplayTree tree;
//    
//    tree.insertNode ( 20 , 20 );
//    tree.insertNode ( 25 , 25 );
//    tree.insertNode ( 30 , 30 );
//    tree.insertNode ( 35 , 35 );
//    tree.insertNode (  1 ,  1 );
//    tree.insertNode (  5 ,  5 );
//    tree.insertNode ( 10 , 10 );
//    tree.insertNode ( 15 , 15 );
//    
//    tree.print ();
//    cout << "\n";
//
//    
////    tree.leftRotation ( tree.searchKey ( 25 ));
//    tree.deleteKey ( 20 );
//    tree.deleteKey ( 1 );
////
////    tree.insertNode ( 15, 15 );
//    
//    tree.print ();
//    cout << "\n";
}