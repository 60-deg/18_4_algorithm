#include <stdio.h>
#include <stdlib.h>

typedef struct lnode{
	struct lnode *next;
	int v;
} lnode;

lnode *createLnode(int value){
	lnode *p;
	p = malloc(sizeof(lnode));
	p->v = value;
	p->next = NULL;
	return p;
}

void insertNext(lnode *x, lnode *t){
	// xの指すノードの後ろにtの指すノードを挿入して，繋ぎなおす
	lnode *tmp = x->next;
	x->next = t;
	t->next = tmp;
	free(tmp);
	return;
}

void deleteNext(lnode *x){
	// xの指すノードを削除して，繋ぎなおす
	lnode *tmp = x->next;
	x->next = tmp->next;
	free(tmp);
	return;
}

void deleteIndex(int n, lnode *p){
	// pからnだけ進んだ位置にあるノードを削除して繋ぎ直す
	// n>=1 とする
	for (int i=0; i<n-1; i++){
		p = p->next;
	}
	deleteNext(p);
}

void printList(lnode *x){
	// xの指すノード以降を空白区切で出力する
	printf("%d ", x->v);
	if (x->next!=NULL){
		printList(x->next);
	}else{
		printf("\n");
	}
	return;
}

int main(void){
	int len, value, index;
	lnode *root=NULL, *p, *prev;
	scanf("%d", &len);		// 初期リストに入れるノードの個数は指定されることにする
	
	for (int i=0; i<len; i++){
		scanf("%d", &value);
		p = createLnode(value);
		if (root==NULL){
			root = p;
		}else{
			insertNext(prev, p);
		}
		prev = p;
	}
	
	printList(root);
	
	while(scanf("%d", &index)!=EOF){
		if (index>=len){
			printf("ERROR\n");
		}else{
			len--;
			if (len==0){
				printf("\n");
				break;
			}
			if (index==0){
				lnode *tmp = root;
				root = root->next;
				free(tmp);
			}else{
				deleteIndex(index, root);
			}
		}
			printList(root);
		}
	
  return 0;    
}
