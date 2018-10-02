//
//  math.h
//  DailyCodingTeamNote
//
//  Created by IRIS on 9/7/15.
//  Copyright (c) 2015 IRIS. All rights reserved.
//
#pragma once
#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;

bool isPrime(int n);
bool isPrime(int n, vector<int> v);
vector<int> getPrimes(int n);

vector<pair<int, int>> factorize(int n);
vector<pair<int, int>> factorize(int n, vector<int> v);

//Complexity : O(N/ logN + N ^ 0.75) for worst case (which means when n is prime number)
// N= 10^9 -> 5 * 10^7
// N= 10^10 -> 4.6 * 10^8
// N= 10^11 -> 4.1 * 10^9

bool isPrime(int n) {
	return isPrime(n, getPrimes((int)sqrt(n)));
}
//Complexity : O(N) for worst case (which means when n is prime number)
bool isPrime(int n, const vector<int> v) {
	for (auto now : v) {
		if (n % now == 0) return false;
	}
	return true;
}

//Verified in range of (0, 10^6) at least by BOJ
//Complexity : O(N ^1.5)
vector<int> getPrimes(int N) {
	vector<int> ret;

	if (N >= 2) ret.push_back(2);
	if (N >= 3) ret.push_back(3);

	int i, j, k;

	bool ctn = true;
	int mid_point = (int)sqrt(N - 1) / 6 + 1;

	for (i = 1; ctn && i <= mid_point; i++) {
		for (j = -1; j <= 1; j += 2) {
			int now = i * 6 + j;

			if (now > sqrt(N)) {
				ctn = false;
				break;
			}

			bool flag = true;
			for (auto here : ret) {
				if (now % here == 0) {
					flag = false;
					break;
				}

			}
			if (flag) {
				ret.push_back(now);
			}
		}
	}

	ctn = true;

	int ret_sqrt_cnt = (int)ret.size();
	for (i = mid_point - 2; ctn && i <= (N - 1) / 6 + 1; i++) {
		for (j = -1; j <= 1; j += 2) {
			int now = i * 6 + j;
			if (now <= ret[ret_sqrt_cnt - 1]) continue;
			if (now > N) {
				ctn = false;
				break;
			}

			bool flag = true;
			for (k = 0; k<ret_sqrt_cnt; k++) {
				if (now % ret[k] == 0) {
					flag = false;
					break;
				}
			}
			if (flag) {
				ret.push_back(now);
			}
		}
	}
	return ret;
}

//return <prime number, power_cnt>
//ex) N = 12 / return vector<pair<2, 2>, pair<3, 1>>
vector<pair<int, int>> factorize(int N) {
	auto primes = getPrimes(sqrt(N) + 5);
	return factorize(N, primes);

}
vector<pair<int, int>> factorize(int N, vector<int> primes) {
	vector<pair<int, int>> ret;

	for (auto p : primes) {
		int c = 0;
		while (N % p == 0) {
			N /= p;
			c++;
		}
		if (c>0) ret.push_back(make_pair(p, c));
	}

	if (N > 1) ret.push_back(make_pair(N, 1));

	return ret;
}

//extended gcd function
//returns gcd(a, b) by value,
//and x, y by reference that satisfies ax + by = gcd(a, b)
//Complexity : 12log2/(pi^2) log a + O(1) approximated by "0.85loga + O(1) in average case",
//				"O(logb) in worst case"	when a>=b
template <typename T>
T xGCD(T a, T b, T *x, T *y) {

	if (a == 0) {
		*x = 0;
		*y = 1;
		return b;
	}

	T x1, y1;
	T gcd = xGCD(b%a, a, &x1, &y1);

	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}

//m SHOULD BE PRIME NUMER!! It doesn't make any assertion!
//returns multiplicative inverse by modulo
//ex) mul_inverse_modulo(3, 11) = 4 since 3 * 4 is equivalent with 1 by modulo 11
//Complexity : O( (log m)^2 )
template <typename T>
T mul_inverse_modulo(T a, T m) {
	T x, y;
	xGCD(a, m, &x, &y);
	return x;
}

//returns ( n C r ) % MOD without caching in 
template <typename T>
T combination(T n, T r, T MOD) {
	if (r > n / 2) r = n - r;
	T ret = 1;
	for (T i = n; i >= n - r + 1; i--) {
		ret *= i;
		ret %= MOD;
	}
	for (T i = r; i >= 1; i--) {
		ret *= mul_inverse_modulo(i, MOD);
		ret %= MOD;
	}
	return ret;
}


//sign of return value is same as the variable {a} (not always positive)
template<typename T>
T gcd(T a, T b) {
	return (b == 0) ? a : gcd(b, a%b);
}
// U must cover T
template<typename T, typename U>
U lcm(T a, T b) {
	return a / gcd(a, b) * (U)b;
}

void Combination(int** c, int n) {
	int i, j;
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= n; j++) {
			c[i][j] = 0;
		}
	}
	for (i = 0; i <= n; i++) {
		c[i][0] = 1;
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= i; j++) {
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
			//if there's a modulo opeartion remove comment mark and add new parameter MOD
			//c[i][j] %= MOD;
		}
	}
}

//Created by Maybe 10/3/15
//chinese_remainder_Theorem
/* if there is a possibility of k being very big, then prime factorize m[i],
* find modular inverse of 'temp' of each of the factors
* 'k' equals to the multiplication ( modular mods[i] ) of modular inverses
*/
template <typename type>
type chinese_remainder(const vector<type>& r, const vector<type>& mods)
{
	type M = 1;
	for (size_t i = 0; i<size_t(mods.size()); i++) M *= mods[i];
	vector< type > m, s;
	for (size_t i = 0; i<size_t(mods.size()); i++) {
		m.push_back(M / mods[i]);
		type temp = m[i] % mods[i];
		type k = 0;
		while (true) {
			if ((k*temp) % mods[i] == 1) break;
			k++;
		}
		s.push_back(k);
	}
	long long ret = 0;
	for (int i = 0; i<int(s.size()); i++) {
		ret += ((m[i] * s[i]) % M *r[i]) % M;
		if (ret >= M) ret -= M;
	}
	return ret;
}


//Created by Maybe 10/3/15
//catalan_number
/*can refix binomial function to use lucas, pascal triangle for performance.
*/
template<typename type>
long long int binomial(type n, type m) 
{
	if (n > m || n < 0) return 0;
	long long int ans = 1, ans2 = 1;
	for (int i = 0 ; i < m ; i++) {
	ans *= n - i;
	ans2 *= i + 1;
	}
	return ans/ans2;
}

template<typename type>
type catalan_number(type n) {
    return binomial(n * 2, n) / (n + 1);
}

template<typename T>
T abs(T a) {
    return (a>=0)? a: -a;
}

/*PRIME NUMBERS
2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691,
701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997

density of prime numbers : x / log x  (lim x -> INF)
*/

/* PI
3.14159265358979323846264338327950288419716939937510582097494459230781640

*/