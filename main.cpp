#include <iostream>
#include <cstring>
#include <cmath>
#include "stb_image.h"
#include "stb_image_write.h"
#include "utils.hpp"
#include "synthetizer.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	//Parameters needed to be manipulate
	int W = 2, H = 2;
	int c = 2;
	double kappa = 0.08;
	VD r = {0.65, 0.35, 0.48, 0.35, 0.3, 0.2, 0.2, 0.1, 0.0};
	bool compute_co = false;
	bool to_tor = false;

	// Parsing
	if(argc < 2) {
		cerr << "Please type as:" << endl;
		cerr << "\t" << argv[0] << " [filename] [-c] [-t]" << endl;
		return 1;
	}
	for(int i = 2; i < argc; i++) {
		if(strcmp(argv[i], "-c") == 0) compute_co = true;
		else if(strcmp(argv[i], "-t") == 0) to_tor = true;
	}
	char* filename = argv[1];

	uchar *E=0, *Ed=0;
	int m, md;
	double is_tore, new_E;
	if(load_image(filename, to_tor, E, m, is_tore, new_E, Ed, md))
		return 1;

	if(md < m) {
		Pix* S = synthesize(Ed, md, r, c, kappa, W, H, !is_tore, filename, compute_co);
		int Wh, Hh;
		uchar* Sh = magnify(md, E, m, S, W, H, Wh, Hh);
		stbi_write_png("magnific.png", Wh, Hh, 3, Sh, 0);
		delete[] S;
		delete[] Sh;
		delete[] Ed;
	} else {
		Pix* S = synthesize(E, m, r, c, kappa, W, H, !is_tore, filename, compute_co);
		int L = 1 << (int) ceil(log2(m));
		save_smooth(S, W*L, H*L, E, m, "magnific.png");
		delete[] S;
	}

	if(new_E) delete[] E;
	else free(E);
	return 0;
}