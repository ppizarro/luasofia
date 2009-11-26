require "luasofia"

su.init()

root = su.root_create()

callbacks = {
    event_handler = function (nua, event, status, phrase)
        print("=> event: " .. event .. " status: " ..
              status .. " phrase: " .. phrase)
        if (event == 25) then
            root:quit()
        end
    end,

    timer_handler = function (t)
        print("nua shutdown!")
        nua:shutdown()
    end
}

nua = nua.create(root, callbacks, {
                        NUTAG_URL = "sip:*:5060;transport=udp",
                        NUTAG_USER_AGENT = "lua_test",
                        NUTAG_MEDIA_ENABLE = 1,
                        NUTAG_EARLY_ANSWER = 1,
                        NUTAG_OUTBOUND = "no-validate no-options-keepalive no-natify",
                        NUTAG_M_USERNAME = "1001" })

nua:set_params({ NUTAG_ENABLEMESSAGE = 1,
                 NUTAG_ENABLEINVITE = 1,
                 NUTAG_AUTOALERT = 0,
                 NUTAG_SESSION_TIMER = 0,
                 NUTAG_AUTOANSWER = 0 })

timer = su.timer_create(root:task(), 200)

timer:set(callbacks)

root:run()

nua = nil
timer = nil
root = nil

su.deinit()

