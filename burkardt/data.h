#define MAX_POINTS 10

typedef struct Point {
  double xy[2]; // x,y coordinate of this point.  The array of points was the initial input.
} Point;

typedef struct Node {
  Point p;
  int onHull;
  double angle_to_infinity;
  int num_edges;
  int *e; // flexible array of indexes [0:num_edges-1] to edges connected to this point
} Node;

Node *node = NULL;

const Point Pt[MAX_POINTS] = {
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
  int n[2]; // index of nodes representing the endpoints of this edge.  Always stored canonically, lowest index first
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

