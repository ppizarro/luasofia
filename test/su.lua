require "luasofia"

su.init()

root = su.root_create()

timer = su.timer_create(root:task(), 200)

timer:set({ timer_handler = function (t)
                print("Timer fired!")
                root:quit()
            end })

root:run()

timer = nil

root = nil

su.deinit()

