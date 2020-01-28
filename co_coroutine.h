#ifndef _CO_COROUTINE_
#define _CO_COROUTINE_

#pragma push_back(1)

typedef struct {
    void* reg[14];
    size_t ss_size;
    char *ss_stack;
    long top;
} ctx_t;

typedef struct {
  ctx_t* stcontext[1024];
  int running;
  ctx_t *mainctx;
} scheduler_t;

#pragma pop

extern scheduler_t g_scheduler;
extern long base;
extern long top;
extern void _co_ctxswap(ctx_t* cur, ctx_t* next) asm("co_swap");
extern void _co_regsave(ctx_t* cur) asm("co_save");
// yield之前和resume之后调用，获取当前函数栈栈
extern void _co_getstack(char* base, char* top)  asm("co_getenv");

//获取到上一层函数的调用站 foo(){foo1(_co_getstackpre(););}获取foo->foo1整个链路调用栈
extern void _co_getstackpre(char* base, char* top) asm("co_getenvpre");


extern ctx_t *_co_new();
extern void _co_delete(ctx_t* cur);


// 成对函数：co_yield， co_resume 内部调用
void co_savecontext(ctx_t* cur, char* base, char* top);
void co_resumecontext(ctx_t* cur);

void co_init();
void co_destory();
// 子协程调用，退出
void co_yield(ctx_t* cur);
// 主协程调用，恢复子协程
void co_resume(ctx_t* next);

#endif