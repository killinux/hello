#include "ptree.h"
void main(int argc,char* argv[])
{
    srand(time(NULL));
    int i ;BTNode* root=NULL;
    for(i=0;i<N;i++) root =insert_node(root,rand()%100);
    DispBTNode(root);printf("\n");
    DispBTree(root);
}
