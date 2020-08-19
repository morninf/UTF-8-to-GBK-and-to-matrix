MYNAME = makefile
CC = gcc

CFLAGS = -g -std=c99 -w

objects = Example.o font_convert.o

example: $(objects)
	cc $(CFLAGS) -o example $(objects)

Example.o: Example.c font_convert.h
	cc $(CFLAGS) -c Example.c 
	
font_convert.o: font_convert.c  
	cc $(CFLAGS) -c font_convert.c 
	
#比较稳健的clean做法，表示clean是一个伪目标
.PHONY: clean

#前面-的意思是：也许某些文件出现问题，忽略，继续执行
clean:
	-rm example $(objects) 

