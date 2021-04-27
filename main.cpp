#include <stdio.h>
#include <stdlib.h>

#include "rule.hpp"

int main() {
	printf("Hello Multi-Neighborhood Automata!\n");
	
	int width  = 1000;
	int height = 1000;
	
	int frames = 20;
	
	int rings_n = 3;
	int min_r[3] = {2, 5, 10};
	int max_r[3] = {4, 8, 12};
	int min_birth[3] = {8, 30, 300};
	int max_birth[3] = {20, 130, 500};
	ruleset r(rings_n, min_r, max_r, min_birth, max_birth);
	
	grid g(width, height, r);
	
	g.randomize();
	g.save((char*) "frames/000.pgm");
	
	char fn[64];
	
	for (int f = 1; f <= frames; f++) {
		printf("Frame %d\n", f);
		g.next();
		sprintf(fn, "frames/%03d.pgm", f);
		g.save(fn);
	}
	
	return 0;
}
