# allocator

# pair

```C++
template <class T1, class T2>
struct pair {
	typedef T1 first_type;
	typedef T2 second_type;
	T1 first;
	T2 second;
	pair() : first(T1()), second(T2()) {}
	pair(const T1 &a, const T2 *&b) : first(a), second(b) {}
	template <class U, class V>
	pair(const pair<U,V>& p) : first(p.first), second(p.second) {}
};
```

### make_pair

```C++
std::pair<int,char>(32,'a');
make_pair(32,'a');
```

# auto_ptr

```C++
#include <memory>
std::auto_ptr<classA> ptr(new classA);
```

```C++
std::auto_ptr<ClassA> a(new ClassA);
std::auto_ptr<ClassA> b(a);
```

```C++
class ClassB { // vulnerable
	ClassA* ptr1;
  	ClassA* ptr2;
  	ClassB(ClassA val1, ClassA val2) : ptr1(new ClassA(val1)), ptr2(new ClassA(val2)){}
};
class ClassC { // safety
	std::auto_ptr<ClassA> ptr1;
 	std::auto_ptr<ClassA> ptr2;
  	ClassC(ClassA val1, ClassA val2) : ptr1(new ClassA(val1)), ptr2(new ClassA(val2)) {}
};
```

# Sequence Container

데이터가 직선형으로 나열됨.

* push_back, pop_back, push_front, pop_front, at, assign, insert, erase, swap, reverse

## vector

* 동적인 배열, 랜덤액세스 지원
* 뒤쪽으로만 삽입, 제거 가능

## deque

* 동적인 배열, 랜덤액세스 지원
* 앞뒤로 모두 삽입, 제거 가능

## list

* Doubly linked list처럼 구현되어 있음
* 각각의 원소가 자신만의 메모리를 가짐
* 랜덤액세스에 걸리는 복잡도가 선형 시간이다.
* 어느 위치에서도 삽입, 제거가 빠름

## string

* ```vector<char>```와 거의 동일하다.

# Associative Container

데이터가 바이너리 트리처럼 구현됨

* find, count, insert, erase, swap

## set

* 원소들이 자신의 comparator(<, >와 같은 비교연산자)를 이용하여 정렬됨
* 중복된 값 불가능

## multiset

* set과 달리 중복된 값이 가능한 것을 제외하고 모두 set과 같다

## map

* item들이 pair이다. pair::first를 기준으로 정렬되며, set과 같은 성질을 가지기 때문에 key가 되는 pair::first는 중복된 값을 가질 수 없다.

## multimap

* map의 item의 key값이 중복될 수 있다. 즉, pair::first의 중복이 허용.

# Container Adapter

기본 컨테이너들을 바탕으로 좀더 제한되거나 특별한 행동을 취하는 컨테이너들

## stack

* LIFO
* 랜덤액세스가 제한된 vector
* top, push, pop

## queue

* FIFO
* 랜덤액세스가 제한된 deque
* 앞에서는 추출만 되고, 뒤에서는 삽입만 된다.
* front, back, push, pop

## priority queue

* 어떤 순서로 집어넣는 지에 상관하지 않고, 현재 컨테이너에 들어있는 값들 중 가장 작은 값이 pop된다.
* top, push, pop

# Algorithm

```#include <algorithm>```

* iterator, const_iterator

* min_element

* max_element

* sort, less, greater

  ```C++
  sort(a.begin(),a.end());
  sort(a.begin(),a.end(),[](char a, char b){ return abs('k'-a) < abs('k'-b) });
  set<int,greater<int>> a; // 큰 게 앞으로 옴
  ```

* reverse

* find

  ```C++
  find(a.begin(),a.end(),3);
  ```

* equal

  ```C++
  equal(a.begin(),a.end(),b.begin());
  ```

* copy, unique_copy, back_inserter, front_inserter

  ```C++
  copy(a.begin(), a.end(), b.begin());
  copy(a.begin(), a.end(), back_inserter(b));
  copy(a.begin(), a.end(), front_inserter(b));
  ```

* remove

* transform, negate

  ```C++
  transform(a.begin(),a.end(),b.begin(),[](int v){return v+3})
  transform(a.begin(),a.end(),b.begin(),negate<int>());
  transform(a.begin(),a.end(),b.begin(),c.begin(),[](int a, int b){return a+b});
  ```

* find_if

* istream_iterator, ostream_iterator

  ```C++
  copy(a.begin(), a.end(), ostream_iterator<int>(cout," "));
  ```

## 함수 객체

```C++
class PrintAdd {
private:
	int val;
public:
	PrintAdd(int val_):val(val_){}
	void operator() (int elem) const {
		cout << elem+val << endl;
	}
};
int main(void)
{
	vector<int> v;
	for(int i=1;i<=10;++i) v.push_back(i);
	for_each(v.begin(), v.end(), PrintAdd(100));
	return 0;
}
```

# 예제

```C++
#include <cstdio>
#include <stack>
#include <queue>
#include <cstdlib>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;

typedef vector< vector<int> > vv_i;

template <class T>
class Stack
{
public:
	stack<T> s;
	unsigned int size() { return s.size(); }
	void push(T val){ s.push(val); }
	T pop() {
		T val = s.top();
		s.pop();
		return val;
	}
};
template <class T>
class Queue
{
public:
	queue<T> q;
	unsigned int size() { return q.size(); }
	void push(T val){ q.push(val); }
	T pop() {
		T val = q.front();
		q.pop();
		return val;
	}
};

void makeRandomConn(vv_i& conn, int portion) {
	int size = conn.size();
	for(int i=0;i<size;++i) {
		for(int j=0;j<size;++j) {
			int r = rand() % 1000;
			if(r < portion) conn[i].push_back(j);
		}
	}
}

template <class Container, class Index=int>
bool pathfind(vv_i &conn, vector<Index> &track, int start=0, int end=-1) {
	int size = conn.size();
	track.resize(size,-1);
	if(end == -1) end = size-1;
	vector<bool> visited(size, false);
	Container S;
	S.push(start);
	if(start == end) return true;
	while(S.size() != 0) {
		int u = S.pop();
		// find_if(conn[u].begin(), conn[u].end(), [&](int v){ // 2.5배 느리다
		// 	if(visited[v]) return false;
		// 	track[v] = u;
		// 	if(v == end) return true;
		// 	visited[v] = true;
		// 	S.push(v);
		// 	return false;
		// });
		for(auto it = conn[u].begin(); it != conn[u].end(); ++it) {
			int v = *it;
			if(visited[v]) continue;
			track[v] = u;
			if(v == end) return true;
			visited[v] = true;
			S.push(v);
		}
	}
	return false;
}

template <class Container>
void test(vv_i &conn, int testNum, string name)
{
	printf("%s testing started\n", name.c_str());
	clock_t begin = clock();
	vector<int> track;
	int foundNum = 0;
	int size = conn.size();
	for(int i=0;i<testNum;++i) {
		if(i%(testNum/10)==0) printf("%d%% ", i/(testNum/10)*10);
		int u = rand() % size;
		int v = rand() % size;
		if(pathfind<Container>(conn, track, u, v)) {
			++foundNum;
		}
	}
	clock_t end = clock();
	printf("\nfound: %d\nnot found: %d\nprobablity: %f%%\ntimedelta: %d\n----------------------------\n",
		foundNum, testNum - foundNum, (float)foundNum / testNum * 100, end-begin);
}

int tester(int nodeNum=1000, int testNum=100000, int portion=2)
{
	srand(time(0));
	vv_i conn(nodeNum, vector<int>());
	makeRandomConn(conn, portion);
	test< Stack<int> >(conn, testNum, "stack");
	test< Queue<int> >(conn, testNum, "queue");
	return 0;
}

int main(void)
{
	tester();
}
```

