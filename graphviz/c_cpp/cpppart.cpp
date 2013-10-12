#include <stdio.h> 
#include <iostream> 
extern "C" int f_test();
int test(){
//    printf("Hello world!");                   
 //   puts("Hello world!");                
  //  puts("Hello" " " "world!");             
    std::cout << "Hello world!" << std::endl;

}
//char* a="string".c_str()
int f_test(int i)
{
	test();
}
 
