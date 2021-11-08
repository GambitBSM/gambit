.KEEP_STATE:

.SUFFIXES:	.o .c .h
.PRECIOUS:	.c .h

all:: create_network.x

create_network.x:: create_network.c include_network.h exclusions.h
	$(CC) -c create_network.c;
	$(CC) -o create_network.x create_network.o -lm;
	@rm -f create_network.o;
	@touch create_network.x

clean:
	rm -f create_network.x
	
distclean: 
	rm -f *.x
