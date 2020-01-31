.globl co_swap
#if !defined( __APPLE__)
.type co_swap, @function
#endif
co_swap:

   leaq 8(%rsp),%rax     # 保存
   leaq 112(%rdi),%rsp
   pushq %rax
   pushq %rbx
   pushq %rcx
   pushq %rdx

   pushq -8(%rax) # ret func addr

   pushq %rsi
   pushq %rdi
   pushq %rbp
   pushq %r8
   pushq %r9
   pushq %r12
   pushq %r13
   pushq %r14
   pushq %r15

   movq %rsi, %rsp
   popq %r15
   popq %r14
   popq %r13
   popq %r12
   popq %r9
   popq %r8
   popq %rbp
   popq %rdi
   popq %rsi
   popq %rax # ret func addr
   popq %rdx
   popq %rcx
   popq %rbx
   popq %rsp
   pushq %rax

   xorl %eax, %eax
   ret

.globl co_getenv
#if !defined( __APPLE__ )
.type co_getenv, @function
#endif
co_getenv:
    leaq 8(%rsp), %rax # get stack top address
    movq %rsi, %rbx    # get first arg, stack top pointer
    movq %rax, (%rbx)  # mov stack top address to stack top pointer
    movq %rdi, %rbx    # get second arg, stack base pointer
    leaq (%rbp), %rax  # get stack base address
    movq %rax, (%rbx)  # move stack base address to stack base pointer
    ret

.globl co_getenvpre
#if !defined(__APPLE__)
.type co_getenvpre, @function
#endif
co_getenvpre:
    
    #  %rbp寄存器存储的是 上一个栈帧的 %rbp地址
    leaq 8(%rsp), %rax # get stack top address
    movq %rsi, %rbx    # get second arg, stack top pointer
    movq %rax, (%rbx)  # mov stack top address to stack top pointer
    movq %rdi, %rbx    # get first arg, stack base pointer
    movq (%rbp), %rax    # get last function stack base address
    movq %rax, (%rbx)  # move stack base address to stack base pointer
    ret

.globl co_save
#if !defined(__APPLE__)
.type co_save, @function
#endif
co_save:

   leaq 8(%rsp),%rax     # 保存
   leaq 112(%rdi),%rsp
   pushq %rax
   pushq %rbx
   pushq %rcx
   pushq %rdx

   pushq -8(%rax) # ret func addr

   pushq %rsi
   pushq %rdi
   pushq %rbp
   pushq %r8
   pushq %r9
   pushq %r12
   pushq %r13
   pushq %r14
   pushq %r15

   # restore rsp
   leaq -8(%rax), %rsp
   xorl %eax, %eax
   ret
    

