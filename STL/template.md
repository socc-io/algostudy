# C++ Template

```C++
template <class T>
inline const T& max (const T& a, const T& b) {
  return a < b ? b:a;
}
```

위처럼 T라는 유동적 타입을 선언하면, 빌드 타임에 각각의 유즈케이스에 관해 필요한 만큼의 함수를 만들어낸다. 그러므로, inline으로 정의했을 경우에는 다수의 함수가 빌드되지 않는다.

```C++
bitset<32> flags32;
bitset<50> flags50;
```

위 처럼, 템플릿에는 비타입 파라미터도 들어갈 수 있다.

```C++
template <int size>
class Container
{
public :
	int buf[size];
};

int main(void)
{
	const int test_size = 10;
	Container<test_size> c;
	for(int i=0;i<10;++i) {
		c.buf[i] = i+1;
	}
	for(int i=0;i<10;++i) {
		printf("%d,",c.buf[i]);
	}
	return 0;
}
```

위 처럼 비타입 파라미터로 넘겨지는 값은 constant해야 한다.

```C++
template <class A, class B=int>
class MyPairContainer
{
private:
	A left;
	B right;
public:
	MyPairContainer(A _left, B _right) : left(_left), right(_right) {}
	void print() { printf("%d %d", left, right); }
};
int main(void)
{
	MyPairContainer<char> pair('a',10);
	pair.print();
	return 0;
}
```

위처럼 템플릿 파라미터에도 기본값이 들어갈 수 있다.

```C++
template <class T>
class MyClass {
  typename T::SubType * ptr;
  ...
};
```

```typename```은 뒤에 오는 것이 Type임을 명시하기 위해 사용된다.

```C++
class GeneralPrinterObject
{
public:
	template <class T>
	void integerPrint(T val) {
		printf("%d", val);
	}
};
int main(void)
{
	GeneralPrinterObject gpo;
	gpo.integerPrint('c');
	gpo.integerPrint(10);
	return 0;
}
```

멤버 함수도 템플릿을 가질 수 있다. 단, 템플릿 멤버함수는 ```virtual```일 수 없고, 기본 인자를 가질 수 없다.

```C++
template <class First>
class DeepContainer {
public:
	int id;
	template <class Second>
	class ChildContainer {
	public:
		template <class Third>
		class GrandsonContainer {
		public:
			First first;
			Second second;
			Third third;
		};
	};
};
int main(void)
{
	DeepContainer<int>::ChildContainer<char>::GrandsonContainer<float> c;
	c.first = 3;
	c.second = 'a';
	c.third = 3.33;
	printf("%d %c %f", c.first, c.second, c.third);
	return 0;
}
```

중첩 클래스도 템플릿을 가질 수 있다.

