#include <stdio.h>
#include <dlfcn.h>
#include "mylib.h"

int 
main()
{
    int (*dlfunc)();
    void *handle;       //����һ�����
    handle = dlopen("./mylib.so", RTLD_LAZY);//��ÿ���
    dlfunc = dlsym(handle, "myfunc"); //��ú������
    (*dlfunc)();
    dlclose(handle); 

    return 0;
}
