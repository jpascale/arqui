include ../Makefile.inc

MODULE=sampleCodeModule.bin
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
ASMSOURCES=$(wildcard *.asm)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)
STATICLIBS=


all: $(MODULE)

$(MODULE): $(OBJECTS) $(ASMOBJECTS) $(STATICLIBS)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld -o ../$(MODULE) $(OBJECTS) $(ASMOBJECTS) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./lib -c $< -o $@
%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o

.PHONY: all clean
