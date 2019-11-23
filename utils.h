#ifndef UTILS_DEF
#define UTILS_DEF
#include <vector>

using namespace std;

typedef unsigned char uchar;
typedef vector<double> VD;
typedef vector<int> VI;

struct Pix {
	int x, y;
	Pix(int a=0, int b=0): x(a), y(b) {}
	inline Pix operator+(const Pix &a) { return {x+a.x, y+a.y}; }
	inline Pix operator-(const Pix &a) { return {x-a.x, y-a.y}; }
	inline Pix operator%(int d) { return {x % d, y % d}; }
	inline Pix operator/(int d) { return {x / d, y / d}; }
};
inline Pix operator*(int a, const Pix &p) { return {a*p.x, a*p.y}; }
typedef std::vector<Pix> VP;
typedef std::vector<VP> VVP;




void getNeighb_S(int x, int y, int k, Pix* S, int W, int H, uchar* E, int m, VI &N);
void getNeighb(int x, int y, int k, uchar* E, int m, VI &N, int h);
inline int distNeighb(VI &a, VI &b, int k) {
	int k2 = k*k*3;
	int res = 0, diff;
	for(int i = 0; i < k2; i++) {
		diff = a[i] - b[i];
		res += diff * diff;
	}
	return res;
}

bool is_tor(uchar* im, int m);

uchar* torrify(uchar* im, int m);
uchar* square(uchar* im, int W, int H);

void save(Pix* S, int W, int H, uchar* E, int m, const char* name);
void save_smooth(Pix* S, int W, int H, uchar* E, int m, const char* name);
void saveS(Pix* S, int W, int H, int m, const char* name);

#endif