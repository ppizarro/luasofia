TARGET = luasofia.so

OBJECTS = luasofia.o luasofia_root.o

CFLAGS += -O2 -c -Wall -fPIC
CFLAGS += `pkg-config --cflags sofia-sip-ua lua5.1`

LFLAGS += $(LDFLAGS)
LFLAGS += `pkg-config --libs sofia-sip-ua lua5.1`

all: $(TARGET)

%.o : src/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET) : $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS) $(LFLAGS)

clean:
	rm -f *.o *.so *~ *.out core $(TARGET)

