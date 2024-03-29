/*
 * Ken Clarkson wrote this.  Copyright (c) 1995 by AT&T..
 * Permission to use, copy, modify, and distribute this software for any
 * purpose without fee is hereby granted, provided that this entire notice
 * is included in all copies of any software which is or includes a copy
 * or modification of this software and in all copies of the supporting
 * documentation for such software.
 * THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY.  IN PARTICULAR, NEITHER THE AUTHORS NOR AT&T MAKE ANY
 * REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
 * OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
 */

#include <math.h>
#include <stdio.h>
#include <time.h>
#include "hull.h"
#include <stdlib.h>

double erand48 (unsigned short X[3]);

unsigned short X[3];

int rand(void);
void srand(unsigned int);

double double_rand(void)
{
#ifdef WIN32
	return (double)rand()/RAND_MAX;
#else
	return erand48(X);
#endif
}

void init_rand(long seed, int quiet) {
#ifdef WIN32
	srand((unsigned int)seed);
#else
	if (!quiet) fprintf(stderr, "init_rand: seed = %d\n", X[1]=(unsigned short) ((seed==0) ? time(0) : seed));
#endif
}

#ifdef WIN32
double logb(double x) {
	if (x<=0) return -1e305;
	return log(x)/log(2);
}
#endif
