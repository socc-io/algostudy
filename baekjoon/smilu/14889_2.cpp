#include <bits/stdc++.h>
using namespace std;

int n, n2;
int answer = 0x3f3f3f3f;
int chemi[20][20];

bool in_start[20];

int member_start[10];
int member_link[10];

void UpdateMembers() {
    int cnt_start = 0, cnt_link = 0;
    for (int i = 0; i < n; i++) {
        if (in_start[i]) {
            member_start[cnt_start++] = i;
        } else {
            member_link[cnt_link++] = i;
        }
    }
}

int Ability(int * members) {
    int result = 0;
    for (int i = 0; i < n2; i++) {
        int mi = members[i];
        for (int j = 0; j < n2; j++) {
            int mj = members[j];
            result += chemi[mi][mj];
        }
    }
    return result;
}

void UpdateAnswer() {
    UpdateMembers();
    answer = min(answer, abs(Ability(member_start) - Ability(member_link)));
}

void DFS(int index, int prev) {
    if (index >= n2) {
        UpdateAnswer();
        return;
    }

    for (int i = prev+1; i < n; i++) {
        in_start[i] = true;
        DFS(index + 1, i);
        in_start[i] = false;
    }
}

int main() {
    scanf("%d", &n);
    n2 = n >> 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &chemi[i][j]);
        }
    }
    DFS(0, -1);
    printf("%d\n", answer);
}
