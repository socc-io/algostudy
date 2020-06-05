#include <bits/stdc++.h>
using namespace std;

class BigInt{
public:
	int sign;
	string s;

	BigInt() : s("") {}

	BigInt(string x){
		*this = x;
	}

	BigInt(int x){
		*this = to_string(x);
	}

	BigInt negative(){
		BigInt x = *this;

		x.sign *= -1;

		return x;
	}

	BigInt normalize(int newSign){
		for(int a = s.size() - 1; a > 0 && s[a] == '0'; a--)
			s.erase(s.begin() + a);

		sign = (s.size() == 1 && s[0] == '0' ? 1 : newSign);

		return *this;
	}

	void operator =(string x){
		int newSign = (x[0] == '-' ? -1 : 1);

		s = (newSign == -1 ? x.substr(1) : x);

		reverse(s.begin(), s.end());

		this->normalize(newSign);
	}

	bool operator ==(const BigInt &x) const{
		return (s == x.s && sign == x.sign);
	}

	bool operator <(const BigInt &x) const{
		if(sign != x.sign) return sign < x.sign;

		if(s.size() != x.s.size())
			return (sign == 1 ? s.size() < x.s.size() : s.size() > x.s.size());

		for(int a = s.size() - 1; a >= 0; a--) if(s[a] != x.s[a])
			return (sign == 1 ? s[a] < x.s[a] : s[a] > x.s[a]);

		return false;
	}

	bool operator <=(const BigInt &x) const{
		return (*this < x || *this == x);
	}

	bool operator >(const BigInt &x) const{
		return (!(*this < x) && !(*this == x));
	}

	bool operator >=(const BigInt &x) const{
		return (*this > x || *this == x);
	}

	BigInt operator +(BigInt x){
		BigInt curr = *this;

		if(curr.sign != x.sign) return curr - x.negative();

		BigInt res;

		for(int a = 0, carry = 0; a < s.size() || a < x.s.size() || carry; a++){
			carry += (a < curr.s.size() ? curr.s[a] - '0' : 0) + (a < x.s.size() ? x.s[a] - '0' : 0);

			res.s += (carry % 10 + '0');

			carry /= 10;
		}

		return res.normalize(sign);
	}

	BigInt operator -(BigInt x){
		BigInt curr = *this;

		if(curr.sign != x.sign) return curr + x.negative();

		int realSign = curr.sign;

		curr.sign = x.sign = 1;

		if(curr < x) return ( (x - curr).negative()).normalize(-realSign);

		BigInt res;

		for(int a = 0, borrow = 0; a < s.size(); a++){
			borrow = (curr.s[a] - borrow - (a < x.s.size() ? x.s[a] : '0'));

			res.s += (borrow >= 0 ? borrow + '0' : borrow + '0' + 10);

			borrow = (borrow >= 0 ? 0 : 1);
		}

		return res.normalize(realSign);
	}

	BigInt operator *(BigInt x){
		BigInt res("0");

		for(int a = 0, b = s[a] - '0'; a < s.size(); a++, b = s[a] -'0'){
			while(b--) res = (res + x);

			x.s.insert(x.s.begin(), '0');
		}

		return res.normalize(sign * x.sign);
	}

	BigInt operator /(BigInt x){
		if(x.s.size() == 1 && x.s[0] == '0') x.s[0] /= (x.s[0] - '0');

		BigInt temp("0"), res;

		for(int a = 0; a < s.size(); a++)
			res.s += "0";
		
		int newSign = sign * x.sign;

		x.sign = 1;

		for(int a = s.size() - 1; a >= 0; a--){
			temp.s.insert(temp.s.begin(), '0');
			temp = temp + s.substr(a, 1);

			while(!(temp < x)){
				temp = temp - x;
				res.s[a]++;
			}
		}

		return res.normalize(newSign);
	}

	BigInt operator %(BigInt x){
		if(x.s.size() == 1 && x.s[0] == '0') x.s[0] /= (x.s[0] - '0');

		BigInt res("0");

		x.sign = 1;

		for(int a = s.size() - 1; a >= 0; a--){
			res.s.insert(res.s.begin(), '0');

			res = res + s.substr(a, 1);

			while(!(res < x))
				res = res - x;
		}

		return res.normalize(sign);
	}

	// operator string(){
	// 	string ret = s;

	// 	reverse(ret.begin(), ret.end());

	// 	return (sign == -1 ? "-" : "") + s;
	// }

	string toString() const{
		string ret = s;

		reverse(ret.begin(), ret.end());

		return (sign == -1 ? "-" : "") + ret;
	}

	BigInt toBase10(int base){
		BigInt exp(1), res("0"), BASE(base);
		
		for(int a = 0; a < s.size(); a++){
			int curr = (s[a] < '0' || s[a] > '9' ? (toupper(s[a]) - 'A' + 10) : (s[a] - '0'));

			res = res + (exp * BigInt(curr));
			exp = exp * BASE;
		}

		return res.normalize(sign);
	}

	BigInt toBase10(int base, BigInt mod){
		BigInt exp(1), res("0"), BASE(base);
		
		for(int a = 0; a < s.size(); a++){
			int curr = (s[a] < '0' || s[a] > '9' ? (toupper(s[a]) - 'A' + 10) : (s[a] - '0'));

			res = (res + ((exp * BigInt(curr) % mod)) % mod);
			exp = ((exp * BASE) % mod);
		}

		return res.normalize(sign);
	}

	string convertToBase(int base){
		BigInt ZERO(0), BASE(base), x = *this;
		string modes = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

		if(x == ZERO)
			return "0";

		string res = "";

		while(x > ZERO){
			BigInt mod = x % BASE;

			x = x - mod;

			if(x > ZERO)
				x = x / BASE;

			res = modes[stoi(mod.toString())] + res;
		}

		return res;
	}

	BigInt toBase(int base){
		return BigInt(this->convertToBase(base));
	}

	friend ostream &operator <<(ostream &os, const BigInt &x){
		os << x.toString();

		return os;
	}
};

int precede_map[256];
void init_precede() {
	precede_map[43] = 1; // '+'
	precede_map[45] = 1; // '-'
	precede_map[42] = 2; // '*'
	precede_map[47] = 2; // '/'
	precede_map[94] = 3; // '^'
}
int precede(char ch) {
  return precede_map[(int)ch];
}

bool is_op(char ch) {
	return ch == '*' || ch == '/' || ch == '+' || ch == '-';
}

typedef BigInt t_val;
enum t_item { ITEM_OP, ITEM_VAL };
typedef pair<t_item, pair<t_val, char>> item;

const t_val inf("4557430888798830399");

vector<item> convert_infix_postfix(const string &infix) {
  stack<char> stk;
  stk.push('#');
  vector<item> postfix;

	bool turn_op = false;
  for (int i = 0; i < (int)infix.size(); i++) {
    char ch = infix[i];
    if (isdigit(ch)) {
			if (turn_op) { postfix.clear(); return postfix; }
			turn_op = true;
			int end = i;
			while (isdigit(infix[end])) ++end;
			BigInt val(infix.substr(i, end-i));
			postfix.push_back({ITEM_VAL, {val, 0}});
			i = end-1;
    } else if (ch == '(') {
			if (turn_op) { postfix.clear(); return postfix; }
			turn_op = false;
      stk.push('(');
    } else if (ch == ')') {
			if (!turn_op) { postfix.clear(); return postfix; }
			turn_op = true;
      while (stk.top() != '#' && stk.top() != '(') {
        postfix.push_back({ITEM_OP, {0, stk.top()}});
				stk.pop();
      }
			if (stk.top() != '(') { postfix.clear(); return postfix; }
      stk.pop();
    } else if (is_op(ch)) {
			if (!turn_op) { postfix.clear(); return postfix; }
			turn_op = false;
      if (precede(ch) > precede(stk.top())) {
        stk.push(ch);
      } else {
        while (stk.top() != '#' && precede(ch) <= precede(stk.top())) {
          postfix.push_back({ITEM_OP, {0, stk.top()}});
          stk.pop();
        }
        stk.push(ch);
      }
    } else { postfix.clear(); return postfix; }
  }

  while (stk.top() != '#') {
    postfix.push_back({ITEM_OP, {0, stk.top()}});
    stk.pop();
  }

  return postfix;
}

t_val process_operator(t_val L, t_val R, char op) {
	if (op == '*') return L * R;
	if (op == '/') return L / R;
	if (op == '+') return L + R;
	if (op == '-') return L - R;
	return 0;
}

t_val process_postfix(const vector<item> &items) {
	stack<t_val> stk;
	for (int i = 0; i < (int)items.size(); i++) {
		auto item = items[i];
		if (item.first == ITEM_VAL) {
			stk.push(item.second.first);
		} else {
			char op = item.second.second;
			if (stk.empty()) return inf;
			t_val R = stk.top(); stk.pop();
			if (stk.empty()) return inf;
			t_val L = stk.top(); stk.pop();
			t_val T = process_operator(L, R, op);
			if (T == inf) return inf;
			stk.push(T);
		}
	}
	if (stk.empty()) return inf;
	t_val ret = stk.top(); stk.pop();
	if (!stk.empty()) return inf;
	return ret;
}

int main() {
	init_precede();
	ios::sync_with_stdio(0); cin.tie(0);
	string infix; cin >> infix;
	auto postfix = convert_infix_postfix(infix);

	// for (const auto &item: postfix) {
	// 	if (item.first == ITEM_OP) cout << (char)item.second.second;
	// 	else cout << item.second.first;
	// } cout << '\n';

	t_val ret = process_postfix(postfix);
	if (ret == inf) cout << "ROCK";
	else cout << ret;
}
