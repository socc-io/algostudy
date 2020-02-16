/*
 * Solving https://www.acmicpc.net/problem/10814
 */

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Person {
  int index;
  int age;
  char name[101];

  void get_age_and_name_from_cin() {
    scanf("%d %s", &age, name);
  }

  void print_age_and_name() {
    printf("%d %s\n", age, name);
  }

  bool operator<(const Person &b) const {
    if (age == b.age) {
      return index < b.index;
    }
    return age < b.age;
  }
};

int main(void)
{
  int N; // the number of people
  scanf("%d", &N);
  vector<Person> people(N);
  
  for (int i = 0; i < N; i++) {
    people[i].index = i;
    people[i].get_age_and_name_from_cin();
  }

  sort(people.begin(), people.end());

  for (int i = 0; i < N; i++) {
    people[i].print_age_and_name();
  }
}
