require "luasofia"

su.init()

root = su.root_create()

timer = su.timer_create(nil, 200)

--[[
timer:set({ timer_handler = function ()
                print("Timer fired!")
                root:quit()
            end })
--]]

--root:run()

timer = nil

root = nil

su.deinit()

