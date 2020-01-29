

all : co_main
.PHONY : all

objects = main.o co_coroutine.o

co_main : $(objects)
	gcc -g -m64 -Wall -o co_main  co_swap.s $(objects)

main.o : main.c 
co_coroutine.o : co_coroutine.c

.PHONY : cleanall clean clean_o

cleanall :  clean  clean_o

clean :  # clean application
	-rm -f co_main
clean_o : # clean *.o files
	-rm -f *.o  