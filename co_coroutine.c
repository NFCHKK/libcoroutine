#include<stdio.h>
#include"co_coroutine.h"

#define DEFAULT_STACK_SIZE (1024 * 1024)


long base = 0, top = 0; 
scheduler_t g_scheduler;

ctx_t *_co_new()
{
    ctx_t* ctx = (ctx_t *)malloc(sizeof(ctx_t));
    char* stack = (char *)malloc(sizeof(char) * DEFAULT_STACK_SIZE);
    ctx->ss_size = DEFAULT_STACK_SIZE;
    ctx->ss_stack = stack; 

    return ctx;
}

void _co_delete(ctx_t* cur)
{
    if(cur)
    {
        if(cur->ss_stack)
        {
            free(cur->ss_stack);
            cur->ss_stack = 0;
        }

        cur->ss_size = 0;

        free(cur);
    }
    cur = 0;
}


void co_savecontext(ctx_t* cur, char* tbase, char* ttop)
{
    if(cur)
    {
        if(cur->ss_stack)
        {
            //栈增长是从高地址到低地址
            memcpy(cur->ss_stack, ttop, tbase - ttop);
            cur->ss_size = tbase - ttop;
            cur->top = ttop;
        }
    }
}

void co_resumecontext(ctx_t* cur)
{
    if(cur)
    {
        if(cur->ss_stack)
        {
            memcpy(cur->top, cur->ss_stack, cur->ss_size);
        }
    }
}

void co_yield(ctx_t* cur)
{
    _co_getstackpre(&base, &top);
    co_savecontext(cur, base, top);
    //子协程退出点
    _co_ctxswap(cur, g_scheduler.mainctx);
    //子协程恢复点
    co_resumecontext(g_scheduler.stcontext[g_scheduler.running]);
}

void co_resume(ctx_t* next)
{
    char dummy;
    _co_getstackpre(&base, &top);
    co_savecontext(g_scheduler.mainctx, base, top);
    //主协程退出点
    _co_ctxswap(g_scheduler.mainctx, next);
    //主协程恢复点
    co_resumecontext(g_scheduler.mainctx);
}

void co_init()
{
    g_scheduler.mainctx = _co_new();
}

void co_destory()
{
    if(g_scheduler.mainctx)
    {
      _co_delete(g_scheduler.mainctx);
    }  
}