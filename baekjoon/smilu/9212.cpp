#include <iostream>

using namespace std;

const double eps = 1e-9;

struct Vertex
{
	double p[3];

	Vertex() {}
	Vertex(double a, double b, double c) {
		p[0] = a; p[1] = b; p[2] = c;
	}

	Vertex operator+(const Vertex &b) {
		Vertex res(
			p[0] + b.p[0],
			p[1] + b.p[1],
			p[2] + b.p[2]
		);
		return res;
	}

	Vertex operator-(const Vertex &b) {
		Vertex res(
			p[0] - b.p[0],
			p[1] - b.p[1],
			p[2] - b.p[2]
		);
		return res;
	}

	Vertex operator*(const double b) {
		Vertex res(
			p[0] * b,
			p[1] * b,
			p[2] * b
		);
		return res;
	}

	Vertex operator/(const double b) {
		Vertex res(
			p[0] / b,
			p[1] / b,
			p[2] / b
		);
		return res;
	}

	double dot(const Vertex &b) {
		return p[0] * b.p[0] + 
			p[1] * b.p[1] +
			p[2] * b.p[2];
	}

	Vertex cross(const Vertex &b) {
		Vertex res(
			p[1] * b.p[2] - p[2] * b.p[1],
			p[2] * b.p[0] - p[0] * b.p[2],
			p[0] * b.p[1] - p[1] * b.p[0]
		);
		return res;
	}

	Vertex norm() {
		double k = p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
		Vertex res(
			p[0] / k,
			p[1] / k,
			p[2] / k
		);
		return res;
	}

	bool like(const Vertex &b) {
		return 
			p[0] - eps <= b.p[0] && b.p[0] <= p[0] + eps &&
			p[1] - eps <= b.p[1] && b.p[1] <= p[1] + eps &&
			p[2] - eps <= b.p[2] && b.p[2] <= p[2] + eps;					
	}

	Vertex orth(int idx) {
		Vertex res;
		if(idx == 0) {
			res.p[0] = p[1];
			res.p[1] = p[2];
		}
		else if(idx == 1) {
			res.p[0] = p[0];
			res.p[1] = p[2];
		} else {
			res.p[0] = p[0];
			res.p[1] = p[1];
		}
		return res;
	}

	void print()
	{
		printf("(%lf, %lf, %lf)", p[0], p[1], p[2]);
	}
};

struct Triangle
{
	Vertex v[3];
};

int is_point_inside_triangle(Triangle &A, Vertex r)
{
	int res = -1, i;

	double D, k1, k2, ks;

	Vertex p = A.v[1] - A.v[0];
	Vertex q = A.v[2] - A.v[0];
	r = r - A.v[0];

	Vertex a, b, c;

	for(i=0; i<3; ++i) {
		a = p.orth(i);
		b = q.orth(i);
		c = r.orth(i);

		D = a.p[0] * b.p[1] - b.p[0] * a.p[1];

		if(-eps < D && D < eps) continue;

		k1 = (b.p[1] * c.p[0] - b.p[0] * c.p[1]) / D;
		k2 = (a.p[0] * c.p[1] - a.p[1] * c.p[0]) / D;
		ks = k1 + k2;

		if(-eps < k1 && k1 < 1. + eps &&
			-eps < k2 && k2 < 1. +eps &&
			-eps < ks && ks < 1. +eps) {
			res = 1;
		} else {
			res = -1;
		}
		break;
	}

	// printf("ipit\n");
	// printf("    (%lf, %lf, %lf)\n", p.p[0], p.p[1], p.p[2]);
	// printf("    (%lf, %lf, %lf)\n", q.p[0], q.p[1], q.p[2]);
	// printf("    (%lf, %lf, %lf)\n", r.p[0], r.p[1], r.p[2]);
	// printf("    k1, k2, i, D: %lf, %lf, %d, %lf\n\n", k1, k2, i, D);

	return res;
}

bool is_tangled(Triangle A, Triangle B)
{
	// d: Surface Direction: the direction vector of surface that includes triangle A
	Vertex d = (A.v[0] - A.v[2]).cross(A.v[1] - A.v[2]).norm();

	const int line_segment_idx[3][2] = { {0, 1}, {1, 2}, {2, 0} };

	Vertex intersects[3];
	int intersects_num = 0;

	for(int i=0; i<3; ++i) { // find all intersecting points;
		int left = line_segment_idx[i][0];
		int right = line_segment_idx[i][1];

		double up = d.dot(A.v[0] - B.v[left]);
		double down = d.dot(B.v[right] - B.v[left]);

		if(-eps < down && down < eps) continue;

		double k = up / down;

		Vertex in = B.v[left] + ((B.v[right] - B.v[left]) * k); // intersecting point

		if(-eps < k && k < 1. + eps) {
			bool check = true;
			for(int i=0; i<intersects_num; ++i) {
				if(intersects[i].like(in)) { // check duplication
					check = false;
					break;
				}
			}
			if(check) {
				intersects[intersects_num++] = in;
			}
		}
	}

	if(intersects_num != 2) return false;

	int is_inside_prod = 1;

	for(int i=0; i<2; ++i) {
		is_inside_prod *= is_point_inside_triangle(A, intersects[i]);
	}

	return is_inside_prod == -1;
}

void do_task()
{
	Triangle T[2];
	for(int i=0; i<2; ++i) {
		for(int j=0; j<3; ++j) {
			for(int k=0; k<3; ++k) {
				scanf("%lf", T[i].v[j].p + k);
			}
		}
	}

	printf(is_tangled(T[0], T[1]) ? "YES\n" : "NO\n");
}

int main(void)
{
	freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i) {
		do_task();
	}
}