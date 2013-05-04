#include "rbtree1.h"
int main(){
        int i=0;
        srand(time(NULL));
        link root=RBinit();
        for(i=0;i<N;i++)
                root=RBinsert(root,rand()%100);
        printf("\t\\tree");
        pprint(root);
        printf("\n");

    	DispBTNode(root);printf("\n");
    	DispBTree(root);
        return 0;
}
