# WARNING = -Wall -Wshadow --pedantic
# ERROR = -Wvla -Werror
# GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

# SRCS = main.c
# OBJS = $(SRCS:%.c=%.o)

# # diff -w means do not care about space

# a5: $(OBJS) 
# 	$(GCC) $(OBJS) -o a5

# .c.o: 
# 	$(GCC) -c $*.c

# run: a5
# 	./a5

# clean: # remove all machine generated files
# 	rm -f a5 *.o output* *~
Build: a5.c
	gcc a5.c -o a5.exe