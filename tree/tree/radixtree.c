#include <stdio.h>
#include <stdlib.h>

typedef struct RadixNode {
     struct RadixNode *lchild, *rchild;
     char *str;
} RadixNode;

void radix_insert(RadixNode *node, char *str)
{
     int i;
     for (i = 0; str[i] != '\0'; i++) {               
          if (str[i] == '0') {
               if (node->lchild == NULL)
                    node->lchild = calloc(sizeof(RadixNode), 1);
               node = node->lchild;               
          } 
          else {
               if (node->rchild == NULL)
                    node->rchild = calloc(sizeof(RadixNode), 1);
               node = node->rchild;
          }               
     }
     node->str = str;
}

void radix_preorder_walk(RadixNode *node)
{
     if (node != NULL) {
          if (node->str != NULL)
               printf("%s\n", node->str);
          radix_preorder_walk(node->lchild);
          radix_preorder_walk(node->rchild);
     }
}

int main(void)
{
     RadixNode *root = malloc(sizeof(RadixNode));
     radix_insert(root, "1011");
     radix_insert(root, "10");
     radix_insert(root, "011");
     radix_insert(root, "100");
     radix_insert(root, "0");
     
     radix_preorder_walk(root);

     return 1;
}

