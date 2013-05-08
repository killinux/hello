gcc -g -finstrument-functions rbtree5.c instrument.c -o rbtree

make
./rbtree
./pvtrace rbtree
./rbtree
dot -Tjpg graph.dot -o graph.jpg
