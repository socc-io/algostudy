#include <iostream>
#include <vector>
#include <set>

using namespace std;

int gcd(int a, int b) {
	int tmp;
	if(a<b) {
		tmp = a;
		a = b;
		b = tmp;
	}
	while(b != 0) {
		tmp = a;
		a = b;
		b = tmp%b;
	}
	return a;
}

int main(int argc, char** argv)
{
	int n;
	cin >> n;
	vector< pair<int, int> > spots(n);
	vector<bool> dead(n);
	set<float> checker;
	for(int i=0;i<n;++i){
		int a, b;
		cin >> a >> b;
		spots[i].first = a;
		spots[i].second = b;
	}
	int sf = spots[0].first;
	int ss = spots[0].second;
	for(int i=1;i<n;++i) {
		spots[i].first -= sf;
		spots[i].second -= ss;
	}
	int i;
	for(i=1;i<n;++i) {
		int x = spots[i].first;
		int y = spots[i].second;
		int gc = gcd(x, y);
		x /= gc;
		y /= gc;
		float fval = (float)y/x;
		if(checker.find(fval) == checker.end()) {
			checker.insert(fval);
		}	
		else {
			break;
		}
	}
	int dx = spots[i].first;
	int dy = spots[i].second;
	int j, k;
	for(int i=0;i<n;++i) {
		dead[i] = (spots[i].first*dy == spots[i].second*dx);
	}
	for(j=1;j==i || dead[j];++j) {}
	for(k=1;k==i || k==j || dead[k];++k) {}
	int dx2 = spots[k].first - spots[j].first;
	int dy2 = spots[k].second - spots[j].second;
	int ox = spots[j].first;
	int oy = spots[j].second;
	dead[j] = true;
	dead[k] = true;
	bool success = true;
	for(int idx=1;idx<n;++idx) {
		if(dead[idx]) continue;
		if((spots[idx].first-ox)*dy2 != (spots[idx].second-oy)*dx2) {
			success = false;
			break;
		}
	} 
	if(success) {
		cout << "success" << endl;
	}
	else {
		cout << "failure" << endl;
	}
	return 0;
}