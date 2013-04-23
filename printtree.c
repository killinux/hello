#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100

//Pstart是二叉树根结点在一行中的位置，一行最能打印124个字符，取其1/2。
//如果你的屏不够宽的话，可以输出文本文件里， aa.exe>>aa.txt
#define Pstart 62

typedef struct node //二叉树存储结构
{
    int    key;
    int    data;
    struct node *lchild,
		*rchild;
}BTNode;
typedef struct pnode        //为打印二叉树建了一个结构。
{
    int key;                   //关键字数据１
    int data;                  //关键字数据２
    struct pnode *lchild,      //左孩子
		 *rchlid,      //右孩子
		 *parent;      //父节点
    int lrflag,                //标记本节点是左孩子（等于０时），还是右孩子（等于１时）
	space,                 //存储本节点打印位置
	level;                 //存储本节点所在层次。
}PBTNode;

/*建立二叉树。
  用括号表示法表示二叉树字符串，创建二叉树。
  */	
BTNode* CreateBTNode(char *s)
{
    char ch;
    BTNode *p=NULL,
	   *b=NULL,
	   *ps[MaxSize];
    int top=-1,
	tag=-1;
    ch=*s;
    while(ch)
    {
	switch(ch)
	{
	    case '(':ps[++top]=p;tag=1;break;
	    case ',':tag=2;break;
	    case ')':top--;break;
	    default:
		     p=(BTNode*)malloc(sizeof(BTNode));
		     p->data=ch;
		     p->lchild=p->rchild=NULL;
		     if(b==NULL)
			 b=p;
		     else
		     {
			 switch(tag)
			 {
			     case 1:ps[top]->lchild=p;break;
			     case 2:ps[top]->rchild=p;break;
			 }
		     }
	}
	ch=*(++s);
    }
    return b;
}

//用适号表示法打印二叉树。
void DispBTNode(BTNode *b)
{
    if(b!=NULL)
    {
	printf("%c",b->data);
	if(b->lchild!=NULL||b->rchild!=NULL)
	{
	    printf("(");
	    DispBTNode(b->lchild);
	    if(b->rchild!=NULL)printf(",");
	    DispBTNode(b->rchild);
	    printf(")");
	}
    }
}
int BTNodeHeight(BTNode *b)
{
    int lchildh,rchildh;
    if(b==NULL)return 0;
    else
    {
	lchildh=BTNodeHeight(b->lchild);
	rchildh=BTNodeHeight(b->rchild);
	return (lchildh>rchildh)?(lchildh+1):(rchildh+1);
    }
}

/*建立一个二叉树打印结点的信息，
  只被int CreatePBTNode(BTNode *b,PBTNode *pqu[])调用*/
void SetPBTNodeInfo(BTNode *b,PBTNode *parent,PBTNode *pb,int level,int lrflag)
{
    int f=3;
    pb->data=b->data;
    pb->key =b->key;
    pb->parent=parent;
    pb->level=level;
    pb->lrflag=lrflag;
    pb->space=-1;
}

/*用层次遍历法，BTNode结构存储的二叉树转换为，PBTNode结构的二叉树*/
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
	if(p->lchild!=NULL)
	{
	    rear++;
	    qu[rear]=p->lchild;
	    pqu[rear]=(PBTNode*)malloc(sizeof(PBTNode));
	    SetPBTNodeInfo(p->lchild,pqu[front],pqu[rear],pqu[front]->level+1,0);
	}
	if(p->rchild!=NULL)
	{
	    rear++;
	    qu[rear]=p->rchild;
	    pqu[rear]=(PBTNode*)malloc(sizeof(PBTNode));
	    SetPBTNodeInfo(p->rchild,pqu[front],pqu[rear],pqu[front]->level+1,1);
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
	printf("%c",pb[0]->data);
	printf("\n");
	return;
    }
    h=h-pb[0]->level+2;
    for(k=0;k<h;k++)
    {
	j=0;
	l--;
	r++;

	for(i=0;i<n;i++)//打印线条
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
    for(i=0;i<n;i++)//计算本层结点打印位置
    {
	p=pb[i];
	if(p->lrflag==0)
	    p->space=p->parent->space+l;
	else
	    p->space=p->parent->space+r;
    }
    for(i=0,j=0;i<n;i++)//打印关键字数据
    {
	p=pb[i];
	for(;j<p->space;j++)
	    printf(" ");
	printf("%c",p->data);
    }
    printf("\n");
}
//循环打印所有层的数据
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
void main(int argc,char* argv[])
{
    int iDepth=0,
	iWidth=0,
	iCount=0;
    char *str1="A(B(D,E(H,X(J,K(L,M(T,Y))))),C(F,G(X,I)))";
   // char *str1="(E(A()())(n(Y(N()())())()))";
 //   char str1[512];
 //char string[512];
//        fgets(str1 ,512,stdin);
    char *str2="A(B(D(,G)),C(E,F))";
    BTNode *b=CreateBTNode(str1);
    DispBTNode(b);printf("\n");
    iDepth=BTNodeHeight(b);
    printf("Depth:%d\n",iDepth);
    DispBTree(b);
}
//发现一件事，认识我越久的人越喜欢我，................除了我自己

