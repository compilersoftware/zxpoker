
all: 
	zcc +zxansi -vn -O3 zxpoker.c -o zxpoker.bin -lndos
	bin2tap zxpoker.bin zxpoker.tap
	rm -f zcc_opt.def

clean:
	rm -f *.bin *.i *.op* *.o *~
