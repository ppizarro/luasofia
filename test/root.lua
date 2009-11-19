require "luasofia"

su.init()

root = su.root_create()

root:run()

root = nil

su.deinit()

