#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 5
//typedef struct node *BTNode*;
//struct node{
//        int data;BTNode* l,r;
//};
typedef struct node //¶þ²æÊ÷´æ´¢½á¹¹
{
    int    key;
    int    data;
    struct node *lchild,
                *rchild;
}BTNode;
BTNode* NODE(int data,BTNode* l,BTNode* r){
        BTNode* t=malloc(sizeof *t);
        t->data=data;t->lchild=l;t->rchild=r;
        return t;
}
BTNode* insert_node(BTNode* t,int data){
        if(t==NULL) return  NODE(data,NULL,NULL);
        if(data<t->data)
                t->lchild=insert_node(t->lchild,data);
        else
                t->rchild=insert_node(t->rchild,data);
        return t;
}
void pprint(BTNode* t){  
        printf("(");  
        if(t!=NULL){   
                printf("%c",t->data);  
                pprint(t->lchild);  
                pprint(t->rchild);  
        }  
        printf(")");  
}  
int main(){
        srand(time(NULL));
        int i ;BTNode* root=NULL;
        for(i=0;i<N;i++) root =insert_node(root,rand()%50+65);
	pprint(root);
	return 0;
}
