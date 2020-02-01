

all : co_main clean_o
.PHONY : all

objects = main.o co_coroutine.o


co_main : $(objects)
	@gcc -g -m64 -Wall -o co_main  co_swap.s $(objects)
	@echo make co_main !

main.o : main.c
	@gcc -c -o main.o main.c
co_coroutine.o : co_coroutine.c
	@gcc -c -o co_coroutine.o co_coroutine.c
.PHONY : cleanall clean clean_o

cleanall :  clean  clean_o

clean :  # clean application
	@-rm -f co_main
clean_o : # clean *.o files  @:used to kill echo
	@-rm -f *.o  