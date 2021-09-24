#include <bits/stdc++.h>

using namespace std;

int n, m;
int selected[10];

int arr[10];

void PrintArray() {
    for (int i = 0; i < m; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * @arg index `index`번째 숫자를 고르는 단계
 * 
 * DFS는 Depth First Search의 약자. main에서는 DFS(0)의 형태로 단 한번만 호출됨.
 * 현재 상태에서 arr[index]에 조건을 배반하지 않으면서 넣을 수 있는 모든 경우의 수들을
 * 시험해보며 진행함.
 * 
 * DFS(0)은 main에서 단 한번만 호출되는 것에 반해,
 * DFS(1)은 최대 약 N번, DFS(2)는 최대 약 N^2번, DFS(3)은 최대 약 N^3번... 의
 * 꼴로 각 DFS(i)가 DFS(i+1)를 N번 호출하게 되면서 연쇄적으로 기하급수적인 횟수의 호출이
 * 재귀적으로 이루어지게 됨.
 */
void DFS(int index) {
    /**
     * m개의 숫자를 고르는 것이기 때문에 index가 m이 되는 순간 더 이상
     * 고르지 않아도 된다.
     * 따라서, 여태까지 골랐던 숫자들을 모두 출력하고 종료.
     * 
     * DFS에서 index >= m 와 같이 재귀적 호출을 중단하게 되는 조건을 `종료조건`이라 자주 표현됨.
     */
    if (index >= m) {
        PrintArray();
    } else {
        /**
         * arr의 index번째 원소는 1~n사이의 자연수. 단, 이미 선택된 수는 제외.
         * 아직 index보다 뒤쪽의 원소들은 결정되지 않았기 때문에 무시할 수 있음.
         * 이 앞의 단계에서 arr[index] = i를 실행하기 전 항상 selected[i]를
         * 1로 설정해주었기 때문에 selected만 보고도 해당 i가 사용가능한 상태인지를
         * 판별할 수 있음.
         */
        for (int i = 1; i <= n; i++) {
            if (selected[i]) continue; // 이미 선택되었다면 스킵

            /**
             * selected[i]가 1이면 i가 이미 arr배열 어딘가에 존재한다는 뜻.
             * DFS로 다음 index의 수를 방문하고 나면, selected[i]는 다시 0으로
             * 되돌려서 arr[index]에 i를 넣었던 것을 무효화 함
             */
            selected[i] = 1;
            arr[index] = i;
            DFS(index + 1);
            selected[i] = 0;
        }
    }
}

int main() {
    // n, m 을 표준입력에서 읽어들임
    cin >> n >> m;

    DFS(0);
}
