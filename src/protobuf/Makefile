
CFLAGS = -g -I/usr/local/include -I.
LDFLAGS = -g -L/usr/local/lib/ -lprotobuf-c

OBJECTS = encode.o cache.pb-c.o
DECODE = decode.o cache.pb-c.o

all: encode decode

encode: $(OBJECTS)
	    $(CC) $(CFLAGS) $(OBJECTS) -o encode $(LDFLAGS)

decode: $(DECODE)
	    $(CC) $(CFLAGS) $(DECODE) -o decode $(LDFLAGS)

encode.o: encode.c
decode.o: decode.c
cache.pb-c.o: cache.pb-c.c

cache.pb-c.c: cache.proto
	protoc-c --c_out=. cache.proto


.PHONY: clean

clean:
	rm *.o encode decode cache.pb-c.c
