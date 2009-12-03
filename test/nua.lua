
require "luasofia"

su = require "luasofia.su"
nua = require "luasofia.nua"
sip = require "luasofia.sip"
soa = require "luasofia.soa"
url = require "luasofia.url"

function make_call(ua, uri, from, to)
    print("gera_chamada: uri["..uri.."] from["..from.."] to["..to.."]")

    nh = ua:handle_create({ NUTAG_URL = uri,
                            SIPTAG_TO_STR = to,
                            SIPTAG_FROM_STR = from })
    nh:invite();
end

function make_user_agent(username, sip_port, rtp_port, f_shutdown)

    callbacks = {}

    callbacks[nua.nua_r_shutdown] = f_shutdown

    callbacks["event_handler"] = function (event, status, phrase, ua, sip, tags)
                                     print("event_handler: event["..nua:event_name(event)..
                                           "] status["..status.."] phrase["..phrase.."]")
                                     if (#tags > 0) then
                                         print("\ttags size[" .. #tags .. "]:")
                                         for i=1, #tags do
                                             print("\t\t" .. tags[i])
                                         end
                                     end
                                 end

    callbacks[nua.nua_i_invite] = function (event, status, phrase, ua, lu_sip, tags)
                                      local s = sip:get_proxy_sip(lu_sip)
                                      local from = sip:get_proxy_sip_addr(s.sip_from)
                                      local to = sip:get_proxy_sip_addr(s.sip_to)
                                      local contact = sip:get_proxy_sip_contact(s.sip_contact)

                                      print("nua_i_invite: status["..status.."] phrase["..phrase.."]")
                                      print("from:    "..from.a_url_user.."@"..from.a_url_host)
                                      print("to:      "..to.a_url_user.."@"..to.a_url_host)
                                      print("contact: "..contact.m_url_user.."@"..contact.m_url_host)
                                  end
  
    callbacks[nua.nua_r_invite] = function (event, status, phrase, ua, sip, tags)
                                      print("nua_r_invite: status["..status.."] phrase["..phrase.."]")
                                  end
  
    callbacks[nua.nua_i_state] = function (event, status, phrase, ua, sip, tags)
                                     print("nua_i_state: status["..status.."] phrase["..phrase.."]")
                                 end

    callbacks[nua.nua_i_active] = function (event, status, phrase, ua, sip, tags)
                                      print("nua_i_active: status["..status.."] phrase["..phrase.."]")
                                  end

    callbacks[nua.nua_i_terminated] = function (event, status, phrase, ua, sip, tags)
                                         print("nua_i_terminated: status["..status.."] phrase["..phrase.."]")
                                      end

    ua = nua.create(root, callbacks,
                    { NUTAG_URL = "sip:*:" .. sip_port .. ";transport=udp",
                      NUTAG_USER_AGENT = "luasofia",
                      NUTAG_MEDIA_ENABLE = 1,
                      NUTAG_EARLY_ANSWER = 1,
                      NUTAG_OUTBOUND = "no-validate no-options-keepalive no-natify",
                      NUTAG_M_USERNAME = username
                    })

    ua:set_params({ NUTAG_ENABLEINVITE = 1,
                    NUTAG_AUTOALERT = 1,
                    NUTAG_SESSION_TIMER = 0,
                    NUTAG_AUTOANSWER = 1,
                    SOATAG_USER_SDP_STR = "m=audio "..rtp_port.." RTP/AVP 0 8\r\n"..
                                          "a=rtpmap:0 PCMU/8000\r\n"..
                                          "a=rtpmap:8 PCMA/8000\r\n"
                  })

    return ua
end

su.init()

root = su.root_create()

local a_quit = false
local b_quit = false

shutdown_a = function (event, status, phrase, ua, sip, tags)
                 print("User Agent A shutdown: status["..status.."] phrase["..phrase.."]")
                 if (status == 200) then
                    a_quit = true
                 end
                 if (a_quit and b_quit) then
                    print("Terminate root!")
                    root:quit()
                 end
             end

ua_a = make_user_agent("1000", 5060, 4000, shutdown_a)

shutdown_b = function (event, status, phrase, ua, sip, tags)
                 print("User Agent B shutdown: status["..status.. "] phrase["..phrase.."]")
                 if (status == 200) then
                    b_quit = true
                 end
                 if (a_quit and b_quit) then
                    print("Terminate root!")
                    root:quit()
                 end
             end

ua_b = make_user_agent("1001", 5080, 5000, shutdown_b)

timer = su.timer_create(root:task(), 500)

timer:set( { timer_handler = function (t)
                                 print("timer fired: shutdown...")
                                 ua_a:shutdown()
                                 ua_b:shutdown()
                             end })

make_call(ua_a, "sip:1001@127.0.0.1:5080",
                "<sip:1000@127.0.0.1>",
                "<sip:1001@127.0.0.1>")

root:run()

ua_a = nil
ua_b = nil
timer = nil
root = nil

su.deinit()

