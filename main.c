#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"co_coroutine.h"

uint8_t bcoro1Run = 0, bcoro2Run = 0;
void coro1()
{
    g_scheduler.stcontext[1] = _co_new();
    printf("coro1 start\n");
    bcoro1Run = 1;
    int32_t a = 0, b = 1;
    while(g_scheduler.stcontext[1])
    {
        sleep(1);
        printf("coro1 yield\n");
        co_yield(g_scheduler.stcontext[1]);
        printf("coro1 resume\n");
    }
    
}

void coro2()
{
   g_scheduler.stcontext[2] = _co_new();
   printf("coro2 start\n");
   bcoro2Run = 1;
   int32_t a = 0, b = 1;
    while(g_scheduler.stcontext[2])
    {
        sleep(1);
        printf("coro2 yield\n");
        co_yield(g_scheduler.stcontext[2]);
        printf("coro2 resume\n");
    }
}

int main()
{
    co_init();
    //保存住协程栈
    _co_getstack((uint8_t *)&base, (uint8_t *)&top);
    co_savecontext(g_scheduler.mainctx, (uint8_t *)base, (uint8_t *)top);
    //保存住协程寄存器
    _co_regsave(g_scheduler.mainctx);
    printf("main corotuine start\n");
    if(!bcoro1Run)
    {
        coro1();
    }
    if(!bcoro2Run)
    {
        coro2();
    }
    
    while(1)
    {
        g_scheduler.running = 1;
        co_resume(g_scheduler.stcontext[1]);
        g_scheduler.running = 2;
        co_resume(g_scheduler.stcontext[2]);
    }

    return 0;
}