Gina
====

Gina is small library containing basic data structures written in C++. Gina was born for my needs during the studies, but it still can be very helpfull.


Contents
--

### Gina::Map

Basic implementation of HashMap. Start using with creating new HashMap:

```cpp
HashMap < int, string > map ( 10 );
```

This will create HashMap with **10** buckets, **integer** key type and **string** as data type. Now you can get or put a new object to the map:

```cpp
// Putting object
map.put ( 1, "first_data" );
// or
map [ 1 ] = "first_data";

// Getting object
string d1 = map.get ( 1 );
// or
string d2 = map [ 1 ]; 
```

And of course, at the end you can print it using `map.print()`.

### Gina::Graphs

Implementation of basic types of graphs. Classic **Graph** represent an undirected graph, or you can use **MatrixDefinedGraph** or **DirectedGraph**.

Usage is quite simple, just create with:

```cpp
Graph graph ( 12 );
```

It create new Graph instance with 12 nodes. Add nodes with `graph.addNode ( new Node ( _idOfNode_ ))`, for example:

```cpp
for ( int i = 0; i < 12; i++ ) {
  graph.addNode ( new Node ( i ));
}
```

Now, you can add edges calling `graph.addEdge ( from, to )`.

### Gina::Helpers

Now it's the perfect time to intruduce Helpers. I implement just a two Graph algorithms for now, **Union Find** and **Three Cetrificate**.




