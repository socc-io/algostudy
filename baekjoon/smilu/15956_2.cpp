#include <iostream>

#include <string>

#include <vector>

#include <map>

#include <set>

#include <algorithm>

#include <cstring>

using namespace std;

 

const int MAX = 1000000;



string input;

int parent[MAX];

vector<string> group[MAX];

bool hasNumber[MAX];

 

//Union Find

int find(int num)

{

        if (parent[num] < 0)

                 return num;

        return parent[num] = find(parent[num]);

}

 

void merge(int a, int b)

{

        a = find(a);

        b = find(b);

 

        if (a == b)

                 return;

 

        if (parent[a] < parent[b])

                 swap(a, b);

        parent[b] += parent[a];

        parent[a] = b;

}

 

int main(void)

{

        ios_base::sync_with_stdio(0);

        cin.tie(0);

 

        memset(parent, -1, sizeof(parent));

        cin >> input;

        input += "&&";

 

        map<string, int> str2int; //변수에 임의의 번호

        vector<string> int2str; //번호를 변수로

 

        vector<pair<int, int>> same; //==으로 연결된 변수

        vector<pair<int, int>> diff; //!=으로 연결된 변수

 

        string tempS[2]; //파싱중인 절에 들어가는 두 변수를 임의의로 저장

        bool usingSpos = 0; //현재 파싱중인 절의 앞/뒤를 표시

        bool isDifferent; //현재 파싱중인 절이 ==인지 !=인지 표시

 

        for (int i = 0; i < input.size(); i++)

        {

                 //변수 구성 문자

                 if (input[i] != '=' &&input[i] != '&' && input[i] != '!')

                         tempS[usingSpos].push_back(input[i]);

                 //절의 첫 번째 변수가 완성됬을 경우

                 else if (usingSpos == 0)

                 {

                         isDifferent = (input[i] == '!');

                         usingSpos = 1;

                         i++;

                 }

                 //절의 두 번째 변수가 완성됬을 경우

                 else

                 {

                         int a, b;

                         //변수에 해당하는 번호를 찾아내거나 새로 매긴다

                         if (str2int.count(tempS[0]))

                                 a = str2int[tempS[0]];

                         else

                         {

                                 str2int[tempS[0]] = int2str.size();

                                 a = int2str.size();

                                 int2str.push_back(tempS[0]);

                         }

                        

                         if (str2int.count(tempS[1]))

                                 b = str2int[tempS[1]];

                         else

                         {

                                 str2int[tempS[1]] = int2str.size();

                                 b = int2str.size();

                                 int2str.push_back(tempS[1]);

                         }

 

                         //==면 same, !=면 diff

                         if (!isDifferent)

                                 same.push_back({ a, b });

                         else

                                 diff.push_back({ a, b });

 

                         tempS[0] = tempS[1] = "";

                         usingSpos = 0;

                         i++;

                 }

        }

 

        string answer;

 

        //==끼리 연결된 컴포턴트끼리 전부 합친다

        for (int i = 0; i < same.size(); i++)

                 merge(same[i].first, same[i].second);

 

        //group에 i를 부모로 하는 집합의 모든 변수들을 저장

        //int2str을 이용하므로 같은 그룹에 중복된 변수 X

        for (int i = 0; i < int2str.size(); i++)

                 group[find(i)].push_back(int2str[i]);

 

        //각 그룹을 순회하면서 답을 구성

        for (int i = 0; i < int2str.size(); i++)

        {

                 //이 그룹에 상수가 2개 이상 있다면 항상 거짓

                 int cntNumber = 0;

                 for (int j = 0; j < group[i].size(); j++)

                         cntNumber += (isdigit(group[i][j][0]) || (group[i][j][0] == '-'));

                 if (cntNumber >= 2)

                 {

                         cout << "0==1";

                         return 0;

                 }

                 //상수가 있는 절은 나중에 필요하므로 표시

                 if (cntNumber == 1)

                         hasNumber[i] = true;

 

                 //그룹의 원소가 3 이상이면, 답에 포함되어야 한다

                 if (group[i].size() < 2)

                         continue;

 

                 //이 그룹에서 가장 길이가 짧은 변수를 찾아낸다

                 int minLength = group[i][0].size(), minIdx = 0;

                 for (int j = 1; j < group[i].size(); j++)

                 {

                         if (group[i][j].size() < minLength)

                         {

                                 minLength = group[i][j].size();

                                 minIdx = j;

                         }

                 }

                 string temp = group[i][minIdx];

                 for (int j = 0; j < group[i].size(); j++)

                 {

                         if (j == minIdx)

                                 continue;

                         answer += group[i][j] + "==" + temp + "&&";

                 }

 

                 //길이가 가장 짧은 원소는 맨 앞에 놔둔다

                 swap(group[i][0], group[i][minIdx]);

        }

 

        //!=로 연결되는 그룹의 쌍을 저장

        //set을 사용하고 항상 {작은 값, 큰 값}으로 저장하여 중복을 없앤다

        set<pair<int, int>> diffZip;

        for (int i = 0; i < diff.size(); i++)

        {

                 int a = find(diff[i].first);

                 int b = find(diff[i].second);

                 //같은 그룹끼리 다르다 = 무조건 거짓

                 if (a == b)

                 {

                         cout << "a!=a";

                         return 0;

                 }

 

                 //둘 다 숫자를 가지고 있으면 다르다고 표시할 필요가 없다

                 if (hasNumber[a] && hasNumber[b])

                         continue;

                 diffZip.insert({ min(a, b), max(a, b) });

        }

 

        //두 그룹의 가장 짧은 변수를 골라 !=로 연결한다

        for (set<pair<int, int>>::iterator it=diffZip.begin(); it!=diffZip.end(); it++)

        {

                 int a = (*it).first;

                 int b = (*it).second;

 

                 answer += group[(*it).first][0] + "!=" + group[(*it).second][0] + "&&";

        }

       

        //항상 참인 절만 있었다면 답이 비어있을 수 있다

        if (answer.empty())

        {

                 cout << "1==1";

                 return 0;

        }

 

        //불필요하게 들어간 &&를 없애고 출력

        for (int i = 0; i < 2; i++)

                 answer.pop_back();

        cout << answer << "\n";

 

        return 0;

}