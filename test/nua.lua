require "luasofia"

su.init()

home = su.home_new()

root = su.root_create()

nua = nua.create(root, {
        event_handler = function (nua, event, status, phrase)
            print("=> event: " .. event .. " status: " ..
                  status .. " phrase: " .. phrase)
            if (event == 25) then
                root:quit()
            end
        end })

timer = su.timer_create(root:task(), 200)

timer:set({ timer_handler = function (t)
                print("nua shutdown!")
                nua:shutdown()
            end })

root:run()

nua = nil
timer = nil
root = nil

su.deinit()

