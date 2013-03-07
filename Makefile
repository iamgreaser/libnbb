OBJS = direct_ref_b.o direct_magic_ref_b.o mapped_ref_b.o blconv.o blfmt.o blimg.o bltmp.o bltmp_acquire.o blit.o
CFLAGS = -Wall -Wextra -pedantic -std=c89 -g

all: libnbb.so testapp

clean:
	rm -f $(OBJS) libnbb.so testapp

testapp: testapp.c nbb.h libnbb.so
	$(CC) $(CFLAGS) -o testapp testapp.c -I. ./libnbb.so `sdl-config --libs --cflags`

libnbb.so: $(OBJS)
	$(CC) $(CFLAGS) -shared -fPIC -o libnbb.so $(OBJS)

direct_ref_b.o: direct_ref_b.c nbb.h
	$(CC) $(CFLAGS) -c -fPIC -o direct_ref_b.o direct_ref_b.c

direct_magic_ref_b.o: direct_magic_ref_b.c nbb.h
	$(CC) $(CFLAGS) -c -fPIC -o direct_magic_ref_b.o direct_magic_ref_b.c

mapped_ref_b.o: mapped_ref_b.c nbb.h
	$(CC) $(CFLAGS) -c -fPIC -o mapped_ref_b.o mapped_ref_b.c

blfmt.o: blfmt.c nbb.h
	$(CC) $(CFLAGS) -c -fPIC -o blfmt.o blfmt.c

blconv.o: blconv.c nbb.h
	$(CC) $(CFLAGS) -c -fPIC -o blconv.o blconv.c

blimg.o: blimg.c nbb.h
	$(CC) -c -fPIC -o blimg.o blimg.c

bltmp_acquire.o: bltmp_acquire.c nbb.h
	$(CC) -c -fPIC -o bltmp_acquire.o bltmp_acquire.c

bltmp.o: bltmp.c nbb.h
	$(CC) -c -fPIC -o bltmp.o bltmp.c

blit.o: blit.c nbb.h
	$(CC) -c -fPIC -o blit.o blit.c

