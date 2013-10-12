#include <stdio.h>
#include <dlfcn.h>
#include "mylib.h"

int 
main()
{
    int (*dlfunc)();
    void *handle;       //定义一个句柄
    handle = dlopen("./mylib.so", RTLD_LAZY);//获得库句柄
    dlfunc = dlsym(handle, "myfunc"); //获得函数入口
    (*dlfunc)();
    dlclose(handle); 

    return 0;
}
