#include <cstdio>

int rewards_num[2][6] = {
    {1, 2, 3, 4, 5, 6},
    {1, 2, 4, 8, 16, 0},
};

int rewards_size[2][6] = {
    {500, 300, 200, 50, 30, 10},
    {512, 256, 128, 64, 32, 0},
};

int get_reward(int idx, int key)
{
    if (key == 0) return 0;
    
    int* reward_num = rewards_num[idx];
    int* reward_size = rewards_size[idx];

    for (int i = 0; i < 6; i++) {
        key -= reward_num[i];
        if (key <= 0) {
            return reward_size[i];
        }
    }

    return 0;
}

int main(void)
{
    int T;
    scanf("%d", &T);
    for(int t = 0; t < T; ++t) {
        int a, b;
        scanf("%d%d", &a, &b);
        int reward = (get_reward(0, a) + get_reward(1, b)) * 10000;
        printf("%d\n", reward);
    }

    return 0;
}