require "luasofia"

su.init()

root = su.root_create()

n = nua.create(root,
               { event_handler = function (m, event, status, phrase, tags)
                     print("=> event: " .. event .. " status: " ..
                           status .. " phrase: " .. phrase)
                     print("=> tags size: " .. #tags)
                     for i=1, #tags do
                        print("\t" .. tags[i])
                     end
                     if (event == 25) then
                         root:quit()
                     end
                 end 
               },
               { NUTAG_URL = "sip:*:5060;transport=udp",
                 NUTAG_USER_AGENT = "lua_test",
                 NUTAG_MEDIA_ENABLE = 1,
                 NUTAG_EARLY_ANSWER = 1,
                 NUTAG_OUTBOUND = "no-validate no-options-keepalive no-natify",
                 NUTAG_M_USERNAME = "1001"
               })

n:set_params({ NUTAG_ENABLEMESSAGE = 1,
               NUTAG_ENABLEINVITE = 1,
               NUTAG_AUTOALERT = 0,
               NUTAG_SESSION_TIMER = 0,
               NUTAG_AUTOANSWER = 0
             })

timer = su.timer_create(root:task(), 200)

timer:set( { timer_handler = function (t)
                 print("nua shutdown!")
                 n:shutdown()
             end })

root:run()

n = nil
timer = nil
root = nil

su.deinit()

