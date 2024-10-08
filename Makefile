WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
#GCC = gcc -g $(WARNING) $(ERROR) 

SRCS = a5.c
OBJS = $(SRCS:%.c=%.o)

# diff -w means do not care about space

a5: $(OBJS) 
	$(GCC) $(OBJS) -o a5

.c.o: 
	$(GCC) -c $*.c

run: a5
	./a5 points.txt

clean: # remove all machine generated files
	rm -f a5 *.o output* *~