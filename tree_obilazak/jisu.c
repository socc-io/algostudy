#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int num = 0;

void make_tree(int *tree, int *input, int nodeIndex, int nNode){
	if (nodeIndex * 2 > nNode){
		tree[nodeIndex - 1] = input[num];
		num++; return;
	}
	make_tree(tree, input, nodeIndex * 2, nNode);
	tree[nodeIndex - 1] = input[num]; num++;
	make_tree(tree, input, nodeIndex * 2 + 1, nNode);
}

int main(void){
	int height, nNode, i, j=1,
		*input, *tree;

	scanf("%d", &height);
	nNode = pow(2, height) - 1;
	input = (int *)calloc(nNode, sizeof(int));
	tree = (int *)calloc(nNode, sizeof(int));
	for (i = 0; i < nNode; i++){
		scanf("%d", &input[i]);
	}
	make_tree(tree, input, 1, nNode);
	for (i = 0; i < nNode; i++){
		printf("%d ", tree[i]);
		if (i + 1 == pow(2, j) - 1){
			puts(""); j++;
		}
	}
	return 0;
}