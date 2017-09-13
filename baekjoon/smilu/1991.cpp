#include<cstdio>

int left[26];
int right[26];

void visit_pre(int pos)
{
    if(pos == -1) return;
    putchar('A'+pos);
    visit_pre(left[pos]);
    visit_pre(right[pos]);
}
void visit_in(int pos)
{
    if(pos == -1) return;
    visit_in(left[pos]);
    putchar('A'+pos);
    visit_in(right[pos]); 
}
void visit_post(int pos)
{
    if(pos == -1) return;
    visit_post(left[pos]);
    visit_post(right[pos]);
    putchar('A'+pos);
}

int main()
{
    int n;
    char a,b,c;
    scanf("%d", &n); getchar();
    for(int i=0; i<n; ++i) {
        a = getchar() - 'A'; getchar();
        b = getchar() - 'A'; getchar();
        c = getchar() - 'A'; getchar();
        left[a] = b == '.'-'A' ? -1 : b;
        right[a]= c == '.'-'A' ? -1 : c;
    }
    visit_pre(0); putchar('\n');
    visit_in(0);  putchar('\n');
    visit_post(0);putchar('\n');
}
