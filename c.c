#include<stdio.h>
void extern_fun_2()
{
    extern_fun();
    int a = 666;
    printf("extern_fun2 is execute, a is %d \n", a);
}
