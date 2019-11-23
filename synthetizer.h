#ifndef SYNTHETIZER_DEF
#define SYNTHETIZER_DEF

#include "utils.hpp"

int load_image(const char* filename, double to_tor,				
				uchar *&E, int &m, double &is_tore, double &new_E, uchar *&Ed, int &md);
void init_variables(uchar *Ed, int md, bool tor, const char* file,
					int &m2, uchar*&E2, bool &have_folder, char* folder, int &L);
void init_live(int W0, int H0, uchar* E2, int m2, int L,
				Pix *S[], int W[], int H[], uchar* El[]);
void init_live_WH(int L, int W0, int H0,
					Pix *S[], int W[], int H[]);

Pix* synthesize (
	uchar* E,					// Image input must be square
	int m,						// The size of the image
	VD &r,						// The vector of amplitudes for the jitter 
	int c,						// The number of correction passes
	double kappa,				// The penalty for the coherence usage
	int W,						// The width of the result (this is the number of duplications of E so the real width is W*m)
	int H,						// The height of the result (this is the number of duplications of E so the real height is H*m)
	bool tor=false,				// If the sample E has been torified
	const char* file="",		// The folder in which are or will be stored coherence images
	bool compute_co=false		// If true and coherence images don't exist then compute them
);

// Apply the step l of the algorithm
void synthesize_step (
	int l,									// The step you want to apply
	Pix *S[], int W[], int H[],				// The array of maps and arrays of width and height of generated image at each step
	uchar *El[],							// The gaussian stack
	int md, int m2,							// The size of the (optionnaly downsized) sample and the size of the possibly torrified sample
	VD &r,									// The vector of amplitudes for the jitter step
	int L,									// Number of steps needed (log2 m)
	bool have_folder, char* folder,			// Some parameters usefull to find coherence files
	bool compute_co, int c, double kappa,	// Same parameters as in the synthetize function
	bool saveE = true						// If true then we write the image E in the file "out.png" else we write the map S
);

uchar* downsample(uchar* im, int m, int p);
uchar* magnify(
	int ml,		// The size of the downsampled image used to create the map S
	uchar* Eh,	// The original sample image before the downsizing
	int mh,		// The original width of the sample image
	Pix* S,		// The map to the downsized sample image
	int W,		// The width of the map S
	int H,		// The height of the map S
	int &Wh,	// The new width will be stored in this integer
	int &Hh		// The new height will be stored in this integer
);

#endif