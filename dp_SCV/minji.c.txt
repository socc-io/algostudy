
#include <stdio.h>
 
// i,j+1 
// i+1,j
 
int main(){
    int map;
    int mine[102][102] = {0, };
    scanf("%d",&map);
    for(int i=1;i<=map;i++){
        for(int j=1;j<=map;j++){
            scanf("%d",&mine[i][j]);
        }
    }
    for(int i=1;i<=map;i++){
        for(int j=1;j<=map;j++){
            if(mine[i][j-1] >= mine[i-1][j]){
                mine[i][j] += mine[i][j-1];
            }
            else if(mine[i][j-1] < mine[i-1][j]){
                mine[i][j] += mine[i-1][j];
            }
        }
    }
    printf("%d\n",mine[map][map]);
}