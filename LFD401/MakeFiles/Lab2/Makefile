CFLAGS = -O2 -Wall 
TARGET = small_cal
LIBDIR = $(PWD)/lib
INCLUDE = $(PWD)/include 
LOADLIBS = -L$(PWD)/lib/
LINKLIB = -ladd -lmul
STATIC_LIB = $(PWD)/lib/libadd.a
SHARED_LIB = $(PWD)/lib/libmul.so.1.0
MAIN_SRC = $(PWD)/main

ALL: $(TARGET)

$(TARGET): $(STATIC_LIB) $(SHARED_LIB) $(MAIN_SRC)/main.c
	$(CC) $(CFLAGS)  -I$(INCLUDE) -o $(TARGET) $(MAIN_SRC)/main.c $(LOADLIBS) $(LINKLIB)

$(STATIC_LIB):
	$(MAKE) -C $(LIBDIR)
$(SHARED_LIB):
	$(MAKE) -C $(LIBDIR)
clean:
	rm -f $(TARGET)
	$(MAKE) -C $(LIBDIR) clean
