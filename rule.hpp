#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class ruleset {
public:
	int rings_n;
	
	int* min_r;
	int* max_r;
	
	int* min_birth;
	int* max_birth;
	
	ruleset(int rn, int* mr, int* Mr, int* mb, int* Mb);
};

class grid {
public:
	int width;
	int height;
	
	ruleset rule;
	
	short* buf1;
	short* buf2;
	
	short* state_buf;
	short* working_buf;
	
	grid(int width, int height, ruleset rule);
	
	void randomize();
	
	void next();
	
	short count_cell(int x, int y, int X, int Y, int r);
	
	void save(char* fn);
	
	~grid();
};

#include "rule.cpp"
