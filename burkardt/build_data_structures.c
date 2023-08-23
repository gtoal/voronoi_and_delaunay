#ifndef NULL
#define NULL 0
#endif

typedef struct Point {
  double xy[2]; // x,y coordinate of this point.  The array of points was the initial input.
} Point;

typedef struct Node {
  Point p;
  int num_edges;
  int e[]; // flexible array of indexes [0:num_edges-1] to edges connected to this point
} Node;

Node *node = NULL;

const Point Pt[] = {
  /* 0 */ {0, 98, },
  /* 1 */ {4163, 17664, },
  /* 2 */ {36460, 9133, },
  /* 3 */ {9229, 48721, },
  /* 4 */ {52675, 45443, },
  /* 5 */ {23317, 83129, },
  /* 6 */ {93173, 56805, },
  /* 7 */ {55609, 5083, },
  /* 8 */ {76705, 1891, },
  /* 9 */ {25235, 29819, },
};

typedef struct Edge {
  Node n[2]; // Endpoints of line.  Always stored canonically, lowest index first
  int onHull; // This edge is on the convex hull and is not part of a second triangle
  int tri[2]; // indexes of 1 (onHull==true) or 2 (onHull==false) triangles which share this edge
} Edge;

Edge *edge = NULL;

typedef struct Triangle {
  int v[3]; // v for vertex - data from triangle_vertices below
  int e[3]; // e[0] is the index of the edge *opposite* vertex[0]
  int t[3]; // Indexes of adjacent triangles sharing each edge of this triangle in same order as edges in e[0:2] (or -1 for an edge on the hull)
  Point CircumCenter;
  double CC_radius;
} Triangle;

Triangle *triangle = NULL;

const int triangle_vertices[][3] = { // numbers are indexes of points above.
  /* 0 */ {  0,   1,   3, },
  /* 1 */ {  1,   0,   2, },
  /* 2 */ {  3,   1,   9, },
  /* 3 */ {  4,   3,   9, },
  /* 4 */ {  9,   1,   2, },
  /* 5 */ {  4,   9,   2, },
  /* 6 */ {  5,   3,   4, },
  /* 7 */ {  2,   0,   7, },
  /* 8 */ {  4,   2,   7, },
  /* 9 */ {  7,   0,   8, },
  /* 10 */ {  4,   7,   8, },
  /* 11 */ {  4,   8,   6, },
  /* 12 */ {  5,   4,   6, },
};

// We will also want an array of edges but they can be computed from the data above

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  // Create an array node[MAX_POINTS] and populate it from Pt[MAX_POINTS].
  
  // for a triangle such as {  2,   0,   7, }, add edges[0][2] = n, edges[0][7] = n+1, and edges[2][7] = n+2
  // with the lower vertex number always coming first.  Assign a unique index to each unique edge pair
  // to create and populate: Edge edge[MAX_EDGES]

  // Now populate an array Triangle triangle[MAX_TRIANGLES] using the data from triangle_vertices and Edge[]

  // Finally populate node[MAX_POINTS].e from the edge data.

  // Output the deLaunay graph in a convenient form.

  // Add circumcenter data to the data structure and compute anything needed to create a Voronoi diagram
  // from the stored information.  You may need to add new data structures.  Remember that the goal is
  // a data structure which holds both parts of the deLaunay/Voronoi dual without redundancy - it is not
  // simply the aggregation of two separate programs.

  // Output the Voronoi diagram in a convenient form.
  
  exit(EXIT_SUCCESS);
  return EXIT_FAILURE;
}
#ifdef NEVER
  edge(4163,17664, 9229,48721);
  edge(0,98, 9229,48721);
  edge(0,98, 4163,17664);
  edge(4163,17664, 36460,9133);
  edge(0,98, 36460,9133);
  edge(0,98, 4163,17664);
  edge(55609,5083, 36460,9133);
  edge(0,98, 36460,9133);
  edge(0,98, 55609,5083);
  edge(76705,1891, 55609,5083);
  edge(0,98, 55609,5083);
  edge(0,98, 76705,1891);
  edge(0,98, 76705,1891);
  edge(0,98, 9229,48721);
  edge(9229,48721, 23317,83129);
  edge(23317,83129, 52675,45443);
  edge(9229,48721, 52675,45443);
  edge(9229,48721, 23317,83129);
  edge(52675,45443, 25235,29819);
  edge(9229,48721, 25235,29819);
  edge(9229,48721, 52675,45443);
  edge(9229,48721, 25235,29819);
  edge(4163,17664, 25235,29819);
  edge(4163,17664, 9229,48721);
  edge(25235,29819, 36460,9133);
  edge(4163,17664, 36460,9133);
  edge(4163,17664, 25235,29819);
  edge(52675,45443, 36460,9133);
  edge(25235,29819, 36460,9133);
  edge(25235,29819, 52675,45443);
  edge(55609,5083, 36460,9133);
  edge(52675,45443, 36460,9133);
  edge(52675,45443, 55609,5083);
  edge(76705,1891, 55609,5083);
  edge(52675,45443, 55609,5083);
  edge(52675,45443, 76705,1891);
  edge(93173,56805, 76705,1891);
  edge(52675,45443, 76705,1891);
  edge(52675,45443, 93173,56805);
  edge(93173,56805, 52675,45443);
  edge(23317,83129, 52675,45443);
  edge(23317,83129, 93173,56805);
  edge(23317,83129, 93173,56805);
  edge(93173,56805, 76705,1891);
#endif
