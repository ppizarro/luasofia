#!/usr/bin/lua

require("luasofia")

function time_test()

  now = luasofia.su_now()
  sthen = now

  print(luasofia.su_time_print(now))

  for us=0,1000000,300 do 
    sthen.tv_sec = now.tv_sec
    sthen.tv_usec = now.tv_usec + us
    if sthen.tv_usec >= 1000000 then
      sthen.tv_usec = sthen.tv_usec - 1000000
      sthen.tv_sec = sthen.tv_sec + 1
    end
    t1 = luasofia.su_duration(now, sthen)
    t2 = luasofia.su_duration(sthen, now)
    if t1 ~= -t2 then
      print("ERROR: t1 ~= -t2")
    end
  end
end

function udpsocket()

  su = luasofia.su_sockaddr_u()
  su.su_family = luasofia.SU_PF_INET
  luasofia.su_getlocalip(su)

  s = luasofia.su_socket(su.su_family, luasofia.SU_SOCK_DGRAM, 0)
  if s == luasofia.INVALID_SOCKET then 
    su_perror("udpsocket: socket")
    exit(1)
  end

  luasofia.su_close(s)
end

luasofia.su_init()

udpsocket()

time_test()

root = luasofia.su_root_create(nil)
if not root then
    print("ERROR: su_root_create")
    exit(1)
end

print("test_su: testing " .. luasofia.su_root_name(root) .. " port implementation")

luasofia.su_root_threading(root, 0)

finit   = function (root, magic) print("lua init") return 1 end
fdeinit = function (root, magic) print("lua deinit") end

ping = luasofia.su_clone_start(root, nil, finit, fdeinit)
if not ping then
    print("su_clone_start")
    exit(1)
end
--[[
if not luasofia.su_clone_start(root, pong, &ponger, do_init, do_destroy) then
    print("su_clone_start")
    exit(1)
end
--]]

luasofia.su_root_destroy(root)

luasofia.su_deinit()

