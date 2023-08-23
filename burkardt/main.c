#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "data.h"

int MAX_EDGES = 0, MAX_TRIANGLES;

int **table = NULL;

int add_edge(int **table, int p1, int p2) {
  if (table[p1][p2] == -1) {
    table[p1][p2] = (++MAX_EDGES - 1);
    //fprintf(stderr, "Edge(%d,%d) = #%d\n", p1, p2, table[p1][p2]);
  }
  return table[p1][p2];
}

int find_edge_no(int p1, int p2) {
  if (p2 > p2) {
    fprintf(stderr, "Programmer error: asking for edge between 2 points (%d and %d) given in NON-CANONICAL order\n", p1, p2);
    exit(EXIT_FAILURE);
  }
  int edge_no = table[p1][p2];
  if (edge_no < 0) {
    fprintf(stderr, "Programmer error: asking for edge between 2 points (%d and %d), which does not exist.\n", p1, p2);
    exit(EXIT_FAILURE);
  }
  return edge_no;
}

int find_triangle(Triangle *triangles, int e, /* excluding */ int me) { // returns -1 if none found.
  int i;
  for (i = 0; i < MAX_TRIANGLES; i++) {
    if (i != me) {
      if (triangle[i].e[0] == e || triangle[i].e[1] == e || triangle[i].e[2] == e) return i;
    }
  }
  return -1;
}

int find_num_edges(int point) { // count the number of edges for which this point is at one or other end of the edge
  int edges = 0, i;
  for (i = 0; i < MAX_EDGES; i++) {
    if (edge[i].n[0] == point || edge[i].n[1] == point) {
      edges += 1;
    }
  }
  return edges;
}

double distance(Point a, Point b) {
  double dx = a.xy[0] - b.xy[0];
  double dy = a.xy[1] - b.xy[1];
  return sqrt(dx * dx + dy * dy);
}

double det(double m00, double m01, double m10, double m11)
{
  return m00 * m11 - m01 * m10;
}

void circumcenter(Point a, Point b, Point c, Point *center, double *radius) {
   double cx = c.xy[0];
   double cy = c.xy[1];
   double ax = a.xy[0] - cx;
   double ay = a.xy[1] - cy;
   double bx = b.xy[0] - cx;
   double by = b.xy[1] - cy;

   double denom = 2 * det(ax, ay, bx, by);

   if (denom == 0) {
     // special case code for co-linear points. Not really the circumcenter.
     // I just pick the halfway point between the two farthest points.
     // Not sure how this affects building deLaunay graph.
     Point farthest1 = a, farthest2 = b;
     double d, farthest_dist = distance(a, b);
     if ((d=distance(b, c)) > farthest_dist) { farthest1 = b; farthest2 = c; farthest_dist = d; }
     if ((d=distance(c, a)) > farthest_dist) { farthest1 = c; farthest2 = a; farthest_dist = d; }
     center->xy[0] = (farthest1.xy[0] + farthest2.xy[0]) / 2;
     center->xy[1] = (farthest1.xy[1] + farthest2.xy[1]) / 2;
     *radius = farthest_dist / 2;     
     return;
   }
   
   double numx = det(ay, ax * ax + ay * ay, by, bx * bx + by * by);
   double numy = det(ax, ax * ax + ay * ay, bx, bx * bx + by * by);
   center->xy[0] = cx - numx / denom; center->xy[1] = cy + numy / denom;
   *radius = distance(a,*center);
}

int main(int argc, char **argv) {
  int i,j,k;

  table = calloc(MAX_POINTS, sizeof(int *));
  for (i = 0; i < MAX_POINTS; i++) { // record unique edges and allocate an edge index number to each.
    table[i] = calloc(MAX_POINTS, sizeof(int));  // The index for edge between p1 and p2 being table[p1][p2]
    for (j = 0; j < MAX_POINTS; j++) table[i][j] = -1; // (as long as p1 < p2)
  }
  
  // for a triangle such as {  2,   0,   7, }, add edges[0][2] = n, edges[0][7] = n+1, and edges[2][7] = n+2
  // with the lower vertex number always coming first.  Assign a unique index to each unique edge pair
  // to create and populate: Edge edge[MAX_EDGES]
  
  MAX_TRIANGLES=sizeof(triangle_vertices)/sizeof(triangle_vertices[0]);
  fprintf(stderr, "Determined number of triangles = %d\n", MAX_TRIANGLES);
  triangle = calloc(MAX_TRIANGLES, sizeof(Triangle));
  
  for (i = 0; i < MAX_TRIANGLES; i++) {
    int v0 = triangle_vertices[i][0], v1 = triangle_vertices[i][1], v2 = triangle_vertices[i][2];
    // The point index will be identical to the triangle_vertex index.
    // Vertex indices for points around a triangle are stored in sorted (ascending) order.
    // Edge indices are *not*. (Because triangle edge X is the edge *opposite* triangle vertex X)
    int e0, e1, e2;
    if (v1 > v2) {int v = v2; v2 = v1; v1 = v;};
    if (v0 > v1) {int v = v0; v0 = v1; v1 = v;};
    if (v1 > v2) {int v = v2; v2 = v1; v1 = v;};
    if (v0 > v1) {int v = v0; v0 = v1; v1 = v;};
    if (!((v0 <= v1) && (v1 <= v2))) {
      fprintf(stderr, "Programmer error - you didn't even sort three integers correctly.  Idiot.  %d %d %d\n", v0,v1,v2);
    }
    e2=add_edge(table, v0,v1);
    e1=add_edge(table, v0,v2);
    e0=add_edge(table, v1,v2);
    // Since we now know the canonical order of the vertices we might as well start populating triangle[]
    triangle[i].v[0] = v0; triangle[i].v[1] = v1; triangle[i].v[2] = v2;
    // And add the edges now since we know them and they're not going to change...
    triangle[i].e[0] = e0; triangle[i].e[1] = e1; triangle[i].e[2] = e2;

  }
  // From now on we should never refer to triangle_vertices[i][0:2] again.  Just use triangle[i].v[0:2]

  node = calloc(MAX_POINTS, sizeof(Node));
  for (i = 0; i < MAX_POINTS; i++) {
    node[i].onHull = false;
  }

  edge = calloc(MAX_EDGES, sizeof(Edge));
  for (i = 0; i < MAX_TRIANGLES; i++) {
    int v0 = triangle[i].v[0], v1 = triangle[i].v[1], v2 = triangle[i].v[2];  // already in order
    int e0, e1, e2;
    
    e0 = triangle[i].e[0];    // The edge opposite v0 is the edge from v1 to v2:
    e1 = triangle[i].e[1];    // The edge opposite v1 is the edge from v0 to v2:
    e2 = triangle[i].e[2];    // The edge opposite v2 is the edge from v0 to v1:

    edge[e0].n[0] = v1; edge[e0].n[1] = v2; 
    edge[e1].n[0] = v0; edge[e1].n[1] = v2; 
    edge[e2].n[0] = v0; edge[e2].n[1] = v1; 
  }
  
  for (i = 0; i < MAX_TRIANGLES; i++) {
    int e0 = triangle[i].e[0], e1 = triangle[i].e[1], e2 = triangle[i].e[2]; // index of unique edges
    triangle[i].t[0] = find_triangle(triangle, e0, /* excluding */ i); // returns -1 if none found.
    triangle[i].t[1] = find_triangle(triangle, e1, /* excluding */ i); // returns -1 if none found.
    triangle[i].t[2] = find_triangle(triangle, e2, /* excluding */ i); // returns -1 if none found.

    // (An edge can only be shared between two triangles... hence edge[edge_no].tri[0:1] ...)
    int sides=0;
    edge[e0].tri[0] = i; edge[e1].tri[0] = i; edge[e2].tri[0] = i; // Primary triangle shared with each side.

    if (edge[e0].onHull = (edge[e0].tri[1] = triangle[i].t[0]) == -1 ? true : false) {
      node[edge[e0].n[0]].onHull = true; node[edge[e0].n[1]].onHull = true;  sides += 1;
    }

    if (edge[e1].onHull = ((edge[e1].tri[1] = triangle[i].t[0])) == -1 ? true : false) {
      node[edge[e1].n[0]].onHull = true; node[edge[e1].n[1]].onHull = true; sides += 1;
    }
    
    if (edge[e2].onHull = (edge[e2].tri[1] = triangle[i].t[2]) == -1 ? true : false) {
       node[edge[e2].n[0]].onHull = true; node[edge[e2].n[1]].onHull = true; sides += 1;
    }
  }
  
  for (i = 0; i < MAX_TRIANGLES; i++) {
    int hull=0;
    fprintf(stderr, "Triangle %d is adjacent to triangles", i);
    if (triangle[i].t[0] >= 0) fprintf(stderr, " %d", triangle[i].t[0]); else hull+=1; /* no other tri shares this side */
    if (triangle[i].t[1] >= 0) fprintf(stderr, " %d", triangle[i].t[1]); else hull+=1;
    if (triangle[i].t[2] >= 0) fprintf(stderr, " %d", triangle[i].t[2]); else hull+=1;
    if (hull) {
      fprintf(stderr, " and has %s on the hull", hull==1?"a side":"sides");
    } else {
      int e0 = triangle[i].e[0], e1 = triangle[i].e[1], e2 = triangle[i].e[2]; // index of unique edges
      if (
          (node[edge[e0].n[0]].onHull || node[edge[e0].n[1]].onHull) ||  // but one of the three vertices is!
          (node[edge[e1].n[0]].onHull || node[edge[e1].n[1]].onHull) ||
          (node[edge[e2].n[0]].onHull || node[edge[e2].n[1]].onHull)
          ) {
        fprintf(stderr, " and has a vertex on the hull");
      } else {
        fprintf(stderr, " and is completely internal to the graph");
      }
    }
    fprintf(stderr, "\n");
  }
  
  for (i = 0; i < MAX_POINTS; i++) {
    int num_edges = find_num_edges(i); /* need to calculate the number of edges attached to this point */
    node[i].p = (Point)Pt[i];
    // .onHull already assigned
    node[i].num_edges = num_edges;
    node[i].e = calloc(num_edges, sizeof(int));
    // Finally populate node[MAX_POINTS].e from the edge data:

    // same logic as in find_num_edges but save each one here.
    num_edges = 0;
    for (j = 0; j < MAX_EDGES; j++) {
      if (edge[j].n[0] == i || edge[j].n[1] == i) { // assumes the edge creation set up n[0:1] already
        node[i].e[num_edges++] = j;
      }
    }
    fprintf(stderr, "Point %d is at (%g,%g), and connects to %d edges:  ", i, node[i].p.xy[0], node[i].p.xy[1], node[i].num_edges);
    for (j = 0; j < num_edges; j++) fprintf(stderr, "Edge %d  ", node[i].e[j]);
    if (node[i].onHull) fprintf(stderr, " ON HULL"); // MISSING ONE. 
    fprintf(stderr, "\n");
  }

  // Calculate circumcenters
  for (i = 0; i < MAX_TRIANGLES; i++) {
    int v0 = triangle[i].v[0], v1 = triangle[i].v[1], v2 = triangle[i].v[2];
    circumcenter(node[v0].p,node[v1].p,node[v2].p, &triangle[i].CircumCenter, &triangle[i].CC_radius);
    fprintf(stderr, "Triangle %d: Circumcenter at %g,%g  radius=%g\n", i, triangle[i].CircumCenter.xy[0], triangle[i].CircumCenter.xy[1], triangle[i].CC_radius);
  }

#ifdef NEVER
  // Output this now as the info wasn't available at the point where I output whether an edge was on the hull, earlier.
  for (i = 0; i < MAX_TRIANGLES; i++) {
    int e0 = triangle[i].e[0], e1 = triangle[i].e[1], e2 = triangle[i].e[2]; // index of unique edges
    if (
        (!(edge[e0].onHull || edge[e0].onHull || edge[e0].onHull)) // none of the 3 edges are on the hull
       && (
           (node[edge[e0].n[0]].onHull || node[edge[e0].n[1]].onHull) ||  // but one of the three vertices is!
           (node[edge[e1].n[0]].onHull || node[edge[e1].n[1]].onHull) ||
           (node[edge[e2].n[0]].onHull || node[edge[e2].n[1]].onHull)
           )
        ) fprintf(stderr, "Triangle %d does not have any sides on the hull *but* does have a vertex on the hull\n", i);
  }
#endif

  // Output the deLaunay graph in a convenient form.

  // Add circumcenter data to the data structure and compute anything needed to create a Voronoi diagram
  // from the stored information.  You may need to add new data structures.  Remember that the goal is
  // a data structure which holds both parts of the deLaunay/Voronoi dual without redundancy - it is not
  // simply the aggregation of two separate programs.

  // Output the Voronoi diagram in a convenient form.

  exit(EXIT_SUCCESS);
  return EXIT_FAILURE;
}


