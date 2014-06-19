cc = gcc
bin = livesman
CFLAGS = -O2 -std=c89 -pedantic -Wall -DANSI -D_VALGRIND_
ar = ar
.PHONY: all clean

all: $(bin)
$(bin): main.o hmg_engine.a grap/grap.o spec/atoui.o
	$(cc) -o $(bin) main.o hmg_engine.a grap/grap.o spec/atoui.o
main.o: main.c
	$(cc) -c $(CFLAGS) main.c
hmg_engine.o: hmg_engine.c
	$(cc) -c $(CFLAGS) hmg_engine.c
hmg_engine.a: hmg_engine.o linklist/linklistc.o linklist/linklistx.o
	$(ar) rc hmg_engine.a hmg_engine.o linklist/linklistc.o linklist/linklistx.o
clean:
	rm -f $(bin) *.o *~ *.a
