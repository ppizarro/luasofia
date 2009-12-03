require "luasofia"
sip = require "luasofia.sip"

u = sip:create_url()

u.user = "7382"
u.host = "sip.digitro.com.br"
u.password = "4567"
u.port = nil
u.path = nil

--print(u)
print(u.host)
print(u.user)
print(u.password)
print(u.port)
print(u.path)

