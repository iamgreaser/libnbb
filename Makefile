OBJS = direct_ref_b.o direct_magic_ref_b.o mapped_ref_b.o blfmt.o blimg.o
CFLAGS = -Wall -Wextra -pedantic -std=c89 -g

all: libnbb.so testapp

clean:
	rm -f $(OBJS) libnbb.so testapp

testapp: testapp.c nbb.h libnbb.so
	$(CC) $(CFLAGS) -o testapp testapp.c -I. ./libnbb.so `sdl-config --libs --cflags`

libnbb.so: $(OBJS)
	$(CC) $(CFLAGS) -shared -fPIC -o libnbb.so $(OBJS)

direct_ref_b.o: direct_ref_b.c
	$(CC) $(CFLAGS) -c -fPIC -o direct_ref_b.o direct_ref_b.c

direct_magic_ref_b.o: direct_magic_ref_b.c
	$(CC) $(CFLAGS) -c -fPIC -o direct_magic_ref_b.o direct_magic_ref_b.c

mapped_ref_b.o: mapped_ref_b.c
	$(CC) $(CFLAGS) -c -fPIC -o mapped_ref_b.o mapped_ref_b.c

blfmt.o: blfmt.c
	$(CC) $(CFLAGS) -c -fPIC -o blfmt.o blfmt.c

blimg.o: blimg.c
	$(CC) -c -fPIC -o blimg.o blimg.c

