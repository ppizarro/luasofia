TARGET = luasofia.so

OBJECTS = luasofia.o \
	  luasofia_weak_table.o \
	  luasofia_utils.o \
          luasofia_su.o \
	  luasofia_su_root.o \
	  luasofia_su_home.o \
	  luasofia_su_timer.o \
	  luasofia_su_task.o \
	  luasofia_nua.o

CFLAGS += -O2 -c -Wall -fPIC
CFLAGS += `pkg-config --cflags sofia-sip-ua lua5.1`

LDFLAGS += `pkg-config --libs sofia-sip-ua lua5.1`

all: $(TARGET)

%.o : src/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET) : $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS) $(LDFLAGS)

check: all check_root check_home check_timer check_nua

check_root:
	lua test/root.lua

check_home:
	lua test/home.lua

check_timer:
	lua test/timer.lua

check_nua:
	lua test/nua.lua

clean:
	rm -f *.o *.so *~ *.out core $(TARGET)

