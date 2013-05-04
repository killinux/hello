#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 10
typedef struct node *link;
struct node{
        int item,key;link l,r;
};
link null;
link NODE(int item,link l,link r,int key){
        link t=malloc(sizeof *t);
        t->item=item;t->l=l;t->r=r;t->key=key;
        return t;
}
link rotR(link t){
	link x=t->l;t->l=x->r;x->r=t;return x;
}
link rotL(link t){
        link x=t->r;t->r=x->l;x->l=t;return x;
}
void pprint(link t){
        printf("(");
        if(t!=null){ 
                printf("%d%c",t->item,t->key?'+':' ');
                pprint(t->l);
                pprint(t->r);
        }
        printf(")");
}
link RBinit(){
	null=NODE(0,NULL,NULL,0);
	null->l=null;null->r=null;
	return null;
}
link insert_node(link t ,int item, int sw){
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
link RBinsert(link root,int item){
	root=insert_node(root,item,0);
	root->key=0;
	return root;
}
