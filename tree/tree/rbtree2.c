#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 10
//typedef struct node *BTNode*;
typedef struct node{
        int item,key;struct node *l,*r;
}BTNode;
BTNode* null;
BTNode* NODE(int item,BTNode* l,BTNode* r,int key){
        BTNode* t=malloc(sizeof *t);
        t->item=item;t->l=l;t->r=r;t->key=key;
        return t;
}
BTNode* rotR(BTNode* t){
	BTNode* x=t->l;t->l=x->r;x->r=t;return x;
}
BTNode* rotL(BTNode* t){
        BTNode* x=t->r;t->r=x->l;x->l=t;return x;
}
void pprint(BTNode* t){
        printf("(");
        if(t!=null){ 
                printf("%d%c",t->item,t->key?'+':' ');
                pprint(t->l);
                pprint(t->r);
        }
        printf(")");
}
BTNode* RBinit(){
	null=NODE(0,NULL,NULL,0);
	null->l=null;null->r=null;
	return null;
}
BTNode* insert_node(BTNode* t ,int item, int sw){
	if(t==null) return NODE(item,null,null,1);
	if(t->l->key && t->r->key){
		t->key=1;t->l->key=0;t->r->key=0;
	}
	if(item<t->item){
                t->l=insert_node(t->l,item,0);
                if(t->key && t->l->key && sw) t=rotR(t);
                if(t->l->key && t->l->l->key)
		{ t=rotR(t); t->key=0; t->r->key=1; }	
	}else{
		t->r=insert_node(t->r,item,1);
		if(t->key && t->r->key && !sw) t=rotL(t);	
		if(t->r->key && t->r->r->key)
		{ t=rotL(t); t->key=0; t->l->key=1; }
	}
	return t;		
}
BTNode* RBinsert(BTNode* root,int item){
	root=insert_node(root,item,0);
	root->key=0;
	return root;
}
int main(){
	int i=0;
     	srand(time(NULL));
	BTNode* root=RBinit();
	for(i=0;i<N;i++)
		root=RBinsert(root,rand()%100);
	printf("\t\\tree");
	pprint(root);
	printf("\n");
	return 0;
}
