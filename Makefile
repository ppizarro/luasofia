TARGET = luasofia.so

OBJECTS = luasofia.o \
          luasofia_su.o \
	  luasofia_su_root.o \
	  luasofia_su_home.o

CFLAGS += -O2 -c -Wall -fPIC
CFLAGS += `pkg-config --cflags sofia-sip-ua lua5.1`

LFLAGS += $(LDFLAGS)
LFLAGS += `pkg-config --libs sofia-sip-ua lua5.1`

all: $(TARGET)

%.o : src/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET) : $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS) $(LFLAGS)

check: all check_root check_home

check_root:
	lua test/root.lua

check_home:
	lua test/home.lua

clean:
	rm -f *.o *.so *~ *.out core $(TARGET)

