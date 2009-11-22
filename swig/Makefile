
all: luasofia.so

su_wrap.c : su.i su_socket.i su_time.i su_wait.i
	swig -I/usr/local/include/sofia-sip-1.12 -I/usr/include -lua -importall -ignoremissing su.i
	swig -v -Wall -Wextra \
	     -I/usr/include \
	     -I/usr/include/linux \
	     -I/usr/include/c++/4.3 \
	     -I/usr/include/c++/4.3/tr1 \
	     -I/usr/include/c++/4.3/i486-linux-gnu \
	     -I/usr/local/include/sofia-sip-1.12 \
	     -lua -importall su.i
#	swig -I/usr/local/include/sofia-sip-1.12 -I/usr/include -lua -importall -ignoremissing su.i

su_wrap.o : su_wrap.c
	$(CC) -Wall -I/usr/include/lua5.1 -I/usr/local/include/sofia-sip-1.12 -c su_wrap.c 

luasofia.so : su_wrap.o
	$(CC) -shared -I/usr/include/lua -L/usr/lib/lua -L/usr/local/lib su_wrap.o -o luasofia.so -lsofia-sip-ua
clean:
	rm *.o su_wrap.c luasofia.so

test: all
	lua test_su.lua
