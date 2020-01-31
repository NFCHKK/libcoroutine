#ifndef _CO_COROUTINE_
#define _CO_COROUTINE_

#include<stdint.h>
#pragma push_back(1)

typedef struct {
    void* reg[14];
    size_t ss_size;
    uint8_t *ss_stack;
    uint64_t top;
} ctx_t;

typedef struct {
  ctx_t* stcontext[1024];
  uint32_t running;
  ctx_t *mainctx;
} scheduler_t;

#pragma pop

extern scheduler_t g_scheduler;
extern uint64_t base;
extern uint64_t top;
extern void _co_ctxswap(ctx_t* cur, ctx_t* next) asm("co_swap");
extern void _co_regsave(ctx_t* cur) asm("co_save");
// yield之前和resume之后调用，获取当前函数栈栈
extern void _co_getstack(uint8_t* base, uint8_t* top)  asm("co_getenv");

//获取到上一层函数的调用站 foo(){foo1(_co_getstackpre(););}获取foo->foo1整个链路调用栈
extern void _co_getstackpre(uint8_t* base, uint8_t* top) asm("co_getenvpre");


extern ctx_t *_co_new();
extern void _co_delete(ctx_t* cur);


// 成对函数：co_yield， co_resume 内部调用
void co_savecontext(ctx_t* cur, uint8_t* base, uint8_t* top);
void co_resumecontext(ctx_t* cur);

void co_init();
void co_destory();
// 子协程调用，退出
void co_yield(ctx_t* cur);
// 主协程调用，恢复子协程
void co_resume(ctx_t* next);

#endif