OBJS = direct_ref_b.o blfmt.o blimg.o
WARN = -Wall -Wextra -pedantic -std=c89

all: libnbb.so testapp

clean:
	rm -f $(OBJS) libnbb.so testapp

testapp: testapp.c nbb.h libnbb.so
	$(CC) $(WARN) -o testapp testapp.c -I. ./libnbb.so `sdl-config --libs --cflags`

libnbb.so: $(OBJS)
	$(CC) $(WARN) -shared -fPIC -o libnbb.so $(OBJS)

direct_ref_b.o: direct_ref_b.c
	$(CC) $(WARN) -c -fPIC -o direct_ref_b.o direct_ref_b.c

blfmt.o: blfmt.c
	$(CC) $(WARN) -c -fPIC -o blfmt.o blfmt.c

blimg.o: blimg.c
	$(CC) -c -fPIC -o blimg.o blimg.c

