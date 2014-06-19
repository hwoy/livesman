cc = gcc
bin = livesman
CFLAGS = -O2 -std=c89 -pedantic -Wall -DANSI -D_VALGRIND_
ar = ar
.PHONY: all clean require

all: $(bin)
$(bin): main.o hmg_engine.a grap/grap.o spec/atoui.o
	$(cc) -o $(bin) main.o hmg_engine.a grap/grap.o spec/atoui.o
main.o: main.c
	$(cc) -c $(CFLAGS) main.c
hmg_engine.o: hmg_engine.c
	$(cc) -c $(CFLAGS) hmg_engine.c
hmg_engine.a: hmg_engine.o linklist/linklistc.o linklist/linklistx.o
	$(ar) rc hmg_engine.a hmg_engine.o linklist/linklistc.o linklist/linklistx.o

require:
	git clone https://github.com/hwoy/spec.git && \
git clone https://github.com/hwoy/linklist.git && \
git clone https://github.com/hwoy/grap.git && \
make -C spec && make -C linklist && make -C grap

clean:
	rm -f $(bin) *.o *~ *.a
