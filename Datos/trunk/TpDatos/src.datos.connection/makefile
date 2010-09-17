LIB=./lib
TEST =./miTest

all:
	make -C $(LIB)
	cp $(LIB)/libspopc.a $(LIB)/libspopc.h $(TEST)
	#cd $(TEST)
	make -C $(TEST)
	mv $(TEST)/gmail-poptest .