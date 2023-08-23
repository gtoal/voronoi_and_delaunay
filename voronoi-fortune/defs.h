#ifndef NULL
#define NULL 0
#endif
#define DELETED -2

extern int triangulate, sorted, plot, debug;

struct Freenode {
  struct Freenode *nextfree;
};
struct Freelist {
  struct Freenode *head;
  int nodesize;
};

extern float xmin, xmax, ymin, ymax, deltax, deltay;

struct Point {
  float x, y;
};

/* structure used both for sites and for vertices */
struct Site {
  struct Point coord;
  int sitenbr;
  int refcnt;
};

extern struct Site *sites;
extern int nsites;
extern int siteidx;
extern int sqrt_nsites;
extern int nvertices;
extern struct Freelist sfl;
extern struct Site *bottomsite;

struct Edge {
  double a, b, c;
  struct Site *ep[2];
  struct Site *reg[2];
  int edgenbr;
};
#define le 0
#define re 1
extern int nedges;
extern struct Freelist efl;

struct Halfedge {
  struct Halfedge *ELleft, *ELright;
  struct Edge *ELedge;
  int ELrefcnt;
  char ELpm;
  struct Site *vertex;
  double ystar;
  struct Halfedge *PQnext;
};

extern struct Freelist hfl;
extern struct Halfedge *ELleftend, *ELrightend;
extern int ELhashsize;
extern struct Halfedge **ELhash;

extern int PQhashsize;
extern struct Halfedge *PQhash;
extern int PQcount;
extern int PQmin;

/* Headers for edgelist.c */
extern void ELinitialize(void);
extern struct Halfedge *HEcreate(struct Edge *e, int pm);
extern void ELinsert(struct Halfedge *lb, struct Halfedge *new);
extern struct Halfedge *ELgethash(int b);
extern struct Halfedge *ELleftbnd(struct Point *p);
extern void ELdelete(struct Halfedge *he);
extern struct Halfedge *ELright(struct Halfedge *he);
extern struct Halfedge *ELleft(struct Halfedge *he);
extern struct Site *leftreg(struct Halfedge *he);
extern struct Site *rightreg(struct Halfedge *he);
/* End of headers for edgelist.c */
/* Headers for geometry.c */
extern void geominit(void);
extern struct Edge *bisect(struct Site *s1, struct Site *s2);
extern struct Site *intersect(struct Halfedge *el1, struct Halfedge *el2);
extern int right_of(struct Halfedge *el, struct Point *p);
extern void endpoint(struct Edge *e, int lr, struct Site *s);
extern float dist(struct Site *s, struct Site *t);
extern void makevertex(struct Site *v);
extern void deref(struct Site *v);
extern void ref(struct Site *v);
/* End of headers for geometry.c */
/* Headers for heap.c */
extern void PQinsert(struct Halfedge *he, struct Site *v, float offset);
extern void PQdelete(struct Halfedge *he);
extern int PQbucket(struct Halfedge *he);
extern int PQempty(void);
extern struct Point PQ_min(void);
extern struct Halfedge *PQextractmin(void);
extern void PQinitialize(void);
/* End of headers for heap.c */
/* Headers for main.c */
extern int main(int argc, char **argv);
extern int scomp(const void *p1, const void *p2);
extern struct Site *nextone(void);
extern void readsites(void);
extern struct Site *readone(void);
/* End of headers for main.c */
/* Headers for memory.c */
extern void freeinit(struct Freelist *fl, int size);
extern char *getfree(struct Freelist *fl);
extern void makefree(struct Freenode *curr, struct Freelist *fl);
extern char *myalloc(unsigned n);
/* End of headers for memory.c */
/* Headers for output.c */
extern void out_bisector(struct Edge *e);
extern void out_ep(struct Edge *e);
extern void out_vertex(struct Site *v);
extern void out_site(struct Site *s);
extern void out_triple(struct Site *s1, struct Site *s2, struct Site *s3);
extern void plotinit(void);
extern void finish_pl(void);
extern int clip_line(struct Edge *e);
/* End of headers for output.c */
/* Headers for voronoi.c */
extern void voronoi(int triangulate, struct Site *(*nextsite )());
/* End of headers for voronoi.c */
