CC := gcc
CLFAGS := -O2 -Wall 
DEBUG = -g
LFLAGS := -o 
LOADLIBS := -L$(pwd)
LDLIBS := -lhello
INCLUDE := -I$(pwd)

lab_hello: lab_hello_main.o libhello.a
	$(CC) $(LFLAGS) lab_hello lab_hello_main.o $(LOADLIBS) $(LDLIBS)

lab_hello_main.o: lab_hello_main.c lab_header.h
	$(CC) $(DEBUG) $(CFLAGS) -c $(INCLUDE) -o lab_hello_main.o lab_hello_main.c

lab_func.o: lab_func.c lab_header.h
	$(CC) $(DEBUG) $(CFLAGS) -c $(INCLUDE) -o lab_func.o lab_func.c

libhello.a: lab_func.o 
	ar rv libhello.a lab_func.o
	ar -s libhello.a

clean:
	rm *.o;rm lab_hello; rm libhello.a
