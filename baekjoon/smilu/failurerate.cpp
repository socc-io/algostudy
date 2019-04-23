/*
 * author: smilu97
 * description:
 *   algorithm solving: https://www.welcomekakao.com/learn/courses/30/lessons/42889
 */

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<double> f_rates;
    sort(stages.begin(), stages.end());
    int cur = 0;
    for (int i = 1; i <= N; i++) {
    	int begin = cur;
    	while (stages[cur] == i) cur++;
    	double stop_cnt = cur - begin;
    	int reach_cnt = stages.size() - begin;
    	double f_rate = reach_cnt ? (stop_cnt / reach_cnt) : 0;
    	f_rates.push_back(f_rate);
    }
    for (int i = 0; i < N; i++) answer.push_back(i);
    sort(answer.begin(), answer.end(), [f_rates](int a, int b) {
        double fa = f_rates[a], fb = f_rates[b];
        if (fa == fb) return a < b;
    	return fa > fb;
    });
	for (int i = 0; i < N; i++) answer[i]++;
    return answer;
}

int main(void)
{
    vector<int> stages = {2, 1, 2, 6, 2, 4, 3, 3};
    vector<int> answer = solution(5, stages);
    for (int val: answer) printf("%d ", val); puts("");
}
