#include<stdio.h>
extern void head_fun()
{
    extern_fun_2();
    int a = 1000;
    printf("head_fun is execute, a is %d \n", a);
}
