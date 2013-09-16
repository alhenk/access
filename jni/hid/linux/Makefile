PROGRAMM = Cr95hf
all: $(PROGRAMM)

CC       ?= gcc
CFLAGS   ?= -Wall -g

COBJS     = hid-libusb.o 
OBJS      = $(COBJS)
LIBS      = `pkg-config libusb-1.0 libudev --libs`
INCLUDES ?= -I../hidapi `pkg-config libusb-1.0 --cflags`

JNIINCLUDES ?= -I/usr/lib/jvm/java-7-openjdk-i386/include
JNISHAREDLIB = $(PROGRAMM)

$(PROGRAMM): $(OBJS)
	$(CC) $(CFLAGS) $(JNIINCLUDES) $(LDFLAGS) $^ $(LIBS) -o ../cr95hf/lib$(JNISHAREDLIB).so -shared ../cr95hf/Cr95hf.c

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) Cr95hf


