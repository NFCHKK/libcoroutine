
all: co_main co_clean
objects = main.o co_coroutine.o

co_main : $(objects)
	gcc -g -m64 -Wall -o co_main  co_swap.s $(objects)

co_clean :   # clean *.o files
	-rm -f *.o

main.o : main.c 
co_coroutine.o : co_coroutine.c

.PHONY : clean
clean :
	-rm -f co_main