SRC1 = $(HOME)/LFT_Work/LinuxFoundationTraining/LFD401/MakeFiles/Lab2/AddSub
SRC2 = $(HOME)/LFT_Work/LinuxFoundationTraining/LFD401/MakeFiles/Lab2/MulDiv
HEADER = $(HOME)/LFT_Work/LinuxFoundationTraining/LFD401/MakeFiles/Lab2/include
INCLUDE = -I$(HEADER)

CFLAGS = -O2 -Wall -c
all: libadd.a libmul.so.1.0


add.o: $(SRC1)/add.c  $(HEADER)/addHeader.h 
	$(CC) $(CFLAGS) $(INCLUDE)/ -o add.o $(SRC1)/add.c
sub.o: $(SRC1)/sub.c  $(HEADER)/addHeader.h 
	$(CC) $(CFLAGS) $(INCLUDE)/ -o sub.o $(SRC1)/sub.c

libadd.a: add.o sub.o
	ar rv libadd.a add.o sub.o
	ar -s libadd.a

mul.o: $(SRC2)/mul.c  $(HEADER)/mulHeader.h
	$(CC) -fPIC $(CFLAGS) $(INCLUDE)/ -o mul.o $(SRC2)/mul.c 
div.o: $(SRC2)/div.c  $(HEADER)/mulHeader.h 
	$(CC) -fPIC $(CFLAGS) $(INCLUDE)/ -o div.o $(SRC2)/div.c 

libmul.so.1.0: mul.o div.o
	$(CC) -shared -Wl,-soname=libmul.so.1 mul.o div.o -o libmul.so.1.0 -lc
	ln -s libmul.so.1.0 libmul.so
	ln -s libmul.so.1.0 libmul.so.1

clean:
	rm -rf *.o libadd.a libmul.so.1.0 libmul.so libmul.so.1
