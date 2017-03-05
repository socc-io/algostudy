#include <stdio.h>

int mock_data[] = {7,10,10,26,49,26,10};
int mock_data_len = 7;

struct ListNode {
	int data;
	List* next;
};

void duplication_delete(ListNode *s)
{
	ListNode *cur, i, j;
	i = s;
	while(i->next != 0) {
		cur = i;
		 
	}
}

int main(void)
{
	ListNode *s = (ListNode*)malloc(sizeof(ListNode));
	s->data = mock_data[0];
	s->next = 0;
	ListNode *cur = s;
	for(int i=1;i<mock_data_len;++i) {
		cur->next = (ListNode*)malloc(sizeof(ListNode));
		cur = cur->next;
		cur->data = mock_data[i];
		cur->next = 0;
	}

	duplication_delete(s);

	cur = s;
	ListNode* n = cur->next;
	while(n != 0) {
		free(s);
		s = n;
		n = n->next;
	}
}