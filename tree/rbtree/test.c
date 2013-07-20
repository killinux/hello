#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define Pstart 62
#define N 10
#define BLACK 0
#define RED 1

typedef struct node 
{
    int    color;
    int    item;
    struct node *left,
		*parent,
		*right;
    
}BTNode;
typedef struct pnode        
{
    int color;                   
    int item;                  
    struct pnode *parent;     
    int lrflag,                //left 0,right 1
	space,                 //print point
	level;                 //the node level
}PBTNode;
BTNode* null;//null node
int BTNodeHeight(BTNode *b)
{
    int lh,rh;
    if(b==null)return 0;
    else
    {
	lh=BTNodeHeight(b->left);
	rh=BTNodeHeight(b->right);
	return (lh>rh)?(lh+1):(rh+1);
    }
}
void SetPBTNodeInfo(BTNode *b,PBTNode *parent,PBTNode *pb,int level,int lrflag)
{
    int f=3;
    pb->item=b->item;
    pb->color =b->color;
    pb->parent=parent;
    pb->level=level;
    pb->lrflag=lrflag;
    pb->space=-3;
}
/*Level Order BTNode----->PBTNode*/
int CreatePBTNode(BTNode *b,PBTNode *pqu[])
{
    BTNode *p;
    BTNode *qu[MaxSize];
    int front=-1,
	rear=-1;
    rear++;
    qu[rear]=b;
    pqu[rear]=(PBTNode*)malloc(sizeof(PBTNode));
    SetPBTNodeInfo(b,NULL,pqu[rear],1,-1);
    while(rear!=front)
    {
	front++;
	p=qu[front];
	if(p->left!=null)
	{
	    rear++;
	    qu[rear]=p->left;
	    pqu[rear]=(PBTNode*)malloc(sizeof(PBTNode));
	    SetPBTNodeInfo(p->left,pqu[front],pqu[rear],pqu[front]->level+1,0);
	}
	if(p->right!=null)
	{
	    rear++;
	    qu[rear]=p->right;
	    pqu[rear]=(PBTNode*)malloc(sizeof(PBTNode));
	    SetPBTNodeInfo(p->right,pqu[front],pqu[rear],pqu[front]->level+1,1);
	}
    }
    return rear;
}
//打印一层结点，及该层结点与父结点的连线路径。
void PBTNodePrint(PBTNode *pb[],int n,int h)
{
    int l=-1,
	r=0,
	i,j,k,
	end;
    char c;
    PBTNode *p;
    if(n<=0||h<=0)
    {
	return;
    }
    else if(n==1)
    {
	for(i=0;i<pb[0]->space;i++)
	    printf(" ");
        printf("%d%c",pb[0]->item,pb[0]->color?'+':' ');
	printf("\n");
	return;
    }
    h=h-pb[0]->level+2;
    for(k=0;k<h;k++)
    {
	j=0;
	l--;
	r++;

	for(i=0;i<n;i++)//print line
	{
	    p=pb[i];
	    end=(p->lrflag==0)?l:r;
	    end+=p->parent->space;
	    for(;j<end;j++)
		printf(" ");
	    c=(p->lrflag==0)?'/':'\\';
	    printf("%c",c);
	}
	printf("\n");
    }
    for(i=0;i<n;i++)//this level ,the node should point
    {
	p=pb[i];
	if(p->lrflag==0)
	    p->space=p->parent->space+l;
	else
	    p->space=p->parent->space+r;
    }
    for(i=0,j=0;i<n;i++)//data
    {
	p=pb[i];
	for(;j<p->space;j++)
	    printf(" ");
                printf("%d%c",p->item,p->color?'+':' ');
    }
    printf("\n");
}
void DispBTree(BTNode *b)
{
    int n,i,j,high,
	level;
    PBTNode *p;
    PBTNode *pqu[MaxSize];
    PBTNode *levelpqu[MaxSize];
    n=CreatePBTNode(b,pqu);
    high=BTNodeHeight(b);
    j=0;
    level=1;
    pqu[0]->space=Pstart;
    for(i=0;i<=n;i++)
    {
	p=pqu[i];
	if(p->level==level)
	{
	    levelpqu[j]=p;
	    j++;
	}
	else
	{
	    PBTNodePrint(levelpqu,j,high);
	    level=p->level;
	    j=0;
	    levelpqu[j]=p;
	    j++;
	}
    }
    PBTNodePrint(levelpqu,j,high);

}

//----------------------rbtree2.c
BTNode* NODE(int item,BTNode* l,BTNode* r,int color){
        BTNode* t=malloc(sizeof *t);
        t->item=item;t->left=l;t->right=r;t->color=color;
        return t;
}
BTNode* rotR(BTNode* t){
        BTNode* x=t->left;t->left=x->right;x->right=t;return x;
}
BTNode* rotL(BTNode* t){
        BTNode* x=t->right;t->right=x->left;x->left=t;return x;
}
BTNode* RBinit(){
        null=NODE(0,null,null,0);
        null->left=null;null->right=null;
        return null;
}
BTNode* insert_node(BTNode* t ,int item, int sw){//sw是分左右的,color 0是黑，1是红
	if(t==null) return NODE(item,null,null,1);
	if(t->left->color && t->right->color){
	    	printf("trace:t->left->color && t->right->color\n");
                t->color=1;t->left->color=0;t->right->color=0;
        }
        if(item<t->item){
		printf("item<t->item\n");
                t->left=insert_node(t->left,item,0);
                if(t->color && t->left->color && sw){ 
			t=rotR(t);
		}
                if(t->left->color && t->left->left->color) {
			 t=rotR(t);
			 t->color=0; 	
			 t->right->color=1;
		}
        }else{
		printf("item>t->item\n");
                t->right=insert_node(t->right,item,1);
                if(t->color && t->right->color && !sw){
			t=rotL(t);
		}
                if(t->right->color && t->right->right->color){
			t=rotL(t); 
			t->color=0;
			t->left->color=1;
		}
        }
        return t;
}
BTNode* RBinsert(BTNode* root,int item){
        root=insert_node(root,item,0);
        root->color=0;
        return root;
}
int main(){
        int i=0;
        srand(time(NULL));
        BTNode* root=RBinit();
//        for(i=0;i<N;i++)
//                root=RBinsert(root,rand()%100);
        root=RBinsert(root,11);
        root=RBinsert(root,41);
        root=RBinsert(root,31);
        root=RBinsert(root,39);
        root=RBinsert(root,79);
        root=RBinsert(root,86);
        root=RBinsert(root,36);
//        root=RBinsert(root,55);
//        root=RBinsert(root,35);
//        root=RBinsert(root,65);
        printf("DispBTree:\n");
        DispBTree(root);
        return 0;
}
BTNode* grandparent(BTNode* n) {
    return n->parent->parent;
}
BTNode* uncle(BTNode* n) {
    if (n->parent == grandparent(n)->left)
        return grandparent(n)->right;
    else
        return grandparent(n)->left;
}

void insert_case1(BTNode* n) {
     if (n->parent == NULL)
         n->color = BLACK;
     else
         insert_case2(n);
}
void insert_case2(BTNode* n) {
    if (n->parent->color == BLACK)
        return; /* 树仍旧有效 */
    else
        insert_case3(n);
}
void insert_case3(BTNode* n) {
    if (uncle(n) != NULL && uncle(n)->color == RED) {
        n->parent->color = BLACK;
        uncle(n)->color = BLACK;
        grandparent(n)->color = RED;
        insert_case1(grandparent(n));
    }
    else
        insert_case4(n);
}
void insert_case4(BTNode* n) {
     if (n == n->parent->right && n->parent == grandparent(n)->left) {
         rotate_left(n->parent);
         n = n->left;
     } else if (n == n->parent->left && n->parent == grandparent(n)->right) {
         rotate_right(n->parent);
         n = n->right;
     }
     insert_case5(n);
}
void insert_case5(BTNode* n) {
     n->parent->color = BLACK;
     grandparent(n)->color = RED;
     if (n == n->parent->left && n->parent == grandparent(n)->left) {
         rotate_right(grandparent(n));
     } else {
         /* Here, n == n->parent->right && n->parent == grandparent(n)->right */
         rotate_left(grandparent(n));
     }
}

BTNode* rotate_right(BTNode* t){ 
        BTNode* x=t->left;t->left=x->right;x->right=t;return x;
}
BTNode* rotate_left(BTNode* t){ 
        BTNode* x=t->right;t->right=x->left;x->left=t;return x;
}
