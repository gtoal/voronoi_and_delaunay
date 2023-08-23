# voronoi_and_delaunay
Simple tools for generating Voronoi and Delaunay data structures from a list of points.

The files in this project are primarily based on the work of other
people.

I wanted to create a data structure that was a bipartite graph consisting
of the data to describe both a voronoi diagram and a delaunay triangulation,
and to create a utility that would generate this data structure from a list
of points.  I did not want to create each one separately but rather to create
ether the Voronoi or the Delaunay from the set of input points and then
construct the dual from whichever form was easiest to compute.

At this point (many years later) I've forgotten how far I got and which
of the utilities in the included subfolders did what, but since I do remember
putting some effort into getting them all to work I thought I might as well
share it here on github for anyone else looking to produce either of these
data structures.  The code here is relatively simple and clean and indeed
I did clean up a lot of old K&R code and make it into more presentable
ANSI C when I worked on this last.  I'll add a more elucidating comment
once I've had a chance to get back into it and remember what everything did :-)


Graham
