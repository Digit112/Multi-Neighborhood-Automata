const float cos45 = 0.7071067811;

ruleset::ruleset(int rn, int* mr, int* Mr, int* mb, int* Mb) : 
	rings_n(rn), min_r(mr), max_r(Mr), min_birth(mb), max_birth(Mb) {}

grid::grid(int width, int height, ruleset rule) : width(width), height(height), rule(rule) {
	buf1 = new short[width*height];
	buf2 = new short[width*height];
	
	state_buf   = buf1;
	working_buf = buf2;
	
	for (int i = 0; i < width*height; i++) {
		buf1[i] = 0;
		buf2[i] = 0;
	}
}

void grid::randomize() {
	for (int i = 0; i < width*height; i++) {
		state_buf[i] = rand() % 2;
	}
}

void grid::next() {
	for (int X = 0; X < width; X++) {
		for (int Y = 0; Y < height; Y++) {
			int total_neighbors = 0;
			int state = 0;
			for (int r = 0; r < rule.rings_n; r++) {
				int rm = rule.min_r[r];
				int rM = rule.max_r[r];
				int E2m = (int) (cos45 * rm);
				int E2M = (int) ceil(rM);
				
				int temp;
				
				int neighbors = 0;
				for (int x = -E2M; x <= E2M; x++) {
					for (int y = E2m; y <= E2M; y++) {
						if (X-x < 0 || X-x >= width || Y-y < 0 || Y-y >= height) continue;
				
						temp = count_cell(X-x, Y-y, X, Y, r);
						neighbors += temp;
						total_neighbors += temp;
					}
				}
		
				for (int x = -E2M; x <= -E2m; x++) {
					for (int y = -E2m; y <= E2m; y++) {
						if (X-x < 0 || X-x >= width || Y-y < 0 || Y-y >= height) continue;
				
						temp = count_cell(X-x, Y-y, X, Y, r);
						neighbors += temp;
						total_neighbors += temp;
					}
				}
		
				for (int x = E2m; x <= E2M; x++) {
					for (int y = -E2m; y <= E2m; y++) {
						if (X-x < 0 || X-x >= width || Y-y < 0 || Y-y >= height) continue;
				
						temp = count_cell(X-x, Y-y, X, Y, r);
						neighbors += temp;
						total_neighbors += temp;
					}
				}
		
				for (int x = -E2M; x <= E2M; x++) {
					for (int y = -E2M; y <= -E2m; y++) {
						if (X-x < 0 || X-x >= width || Y-y < 0 || Y-y >= height) continue;
						
						temp = count_cell(X-x, Y-y, X, Y, r);
						neighbors += temp;
						total_neighbors += temp;
					}
				}
				
				if (neighbors >= rule.min_birth[r] && neighbors <= rule.max_birth[r]) {
					state++;
				}
				else {
					state--;
				}
			}
			
			if (state == 0) {
				working_buf[X + Y*width] = state_buf[X + Y*width];
			}
			else {
				working_buf[X + Y*width] = state;
			}
		}
	}
	
	if (working_buf == buf1) {
		working_buf = buf2;
		state_buf   = buf1;
	}
	else {
		working_buf = buf1;
		state_buf   = buf2;
	}
}

short grid::count_cell(int x, int y, int X, int Y, int r) {
	int dx = X-x;
	int dy = Y-y;
	
	int sqr_dis = dx*dx+dy*dy;
	
	int mr = rule.min_r[r];
	mr *= mr;
	
	int Mr = rule.max_r[r];
	Mr *= Mr;
	
//	printf("(%d, %d) isn (%d, %d): %d, isa: %d, dx: (%d, %d), r: %d <= %d <= %d\n",
//	x, y, X, Y, sqr_dis <= Mr && sqr_dis >= mr, state_buf[x + width*y], dx, dy, mr, sqr_dis, Mr);
	
	if (state_buf[x + width*y] > 0 && sqr_dis <= Mr && sqr_dis >= mr) {
		return 1;
	}
	
	return 0;
}

void grid::save(char* fn) {
	FILE* fout = fopen(fn, "wb");
	if (fout == NULL) {
		printf("Write failed.\n");
		return;
	}
	
	char wbuf[width*height*3+32];
	
	int n = sprintf(wbuf, "P6\n%d %d\n255\n", width, height);
	for (int i = 0; i < width*height; i++) {
		if (state_buf[i] > 0) {
			wbuf[n] = 255; n++;
			wbuf[n] = 255; n++;
			wbuf[n] = 255; n++;
		}
		else {
			wbuf[n] = 0; n++;
			wbuf[n] = 0; n++;
			wbuf[n] = 0; n++;
		}
	}
	
	fwrite(wbuf, n, 1, fout);
	fclose(fout);
}

grid::~grid() {
	delete[] buf1;
	delete[] buf2;
}









