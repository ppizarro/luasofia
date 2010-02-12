--[[

@author Paulo Pizarro  <paulo.pizarro@gmail.com>
@author Tiago Katcipis <tiagokatcipis@gmail.com>

This file is part of Luasofia.

Luasofia is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Luasofia is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Luasofia.  If not, see <http://www.gnu.org/licenses/>.
]]--

su = require "luasofia.su"
nua = require "luasofia.nua"
sip = require "luasofia.sip"
soa = require "luasofia.soa"
url = require "luasofia.url"
sdp = require "luasofia.sdp"
tport = require "luasofia.tport"

function make_call(ua, uri, from, to)
    print("make_call: uri["..uri.."] from["..from.."] to["..to.."]")

    nh = ua:handle_create({ NUTAG_URL = uri,
                            SIPTAG_TO_STR = to,
                            SIPTAG_FROM_STR = from })
    nh:invite();
end

function make_user_agent(username, sip_port, rtp_port, f_shutdown)

    callbacks = {}

    callbacks[nua.nua_r_shutdown] = f_shutdown

    callbacks[nua.nua_event_default] = function (event, status, phrase, ua, nh, sip_lu, tags)
                                           print("event_default: event["..nua:event_name(event)..
                                            "] status["..status.."] phrase["..phrase.."]")
                                       end

    callbacks[nua.nua_i_invite] = function (event, status, phrase, ua, nh, sip_lu, tags)
                                      local sip_proxy = sip.get_proxy(sip_lu)
                                      local from = sip.get_proxy_addr(sip_proxy.sip_from)
                                      local to = sip.get_proxy_addr(sip_proxy.sip_to)
                                      local contact = sip.get_proxy_contact(sip_proxy.sip_contact)
                                      local from_url = url.get_proxy(from.a_url)
                                      local to_url = url.get_proxy(to.a_url)
                                      local contact_url = url.get_proxy(contact.m_url)

                                      print("nua_i_invite: status["..status.."] phrase["..phrase.."]")
                                      print("from:    "..from_url.user.."@"..from_url.host)
                                      print("to:      "..to_url.user.."@"..to_url.host)
                                      print("contact: "..contact_url.user.."@"..contact_url.host)

                                      local req_proxy = sip.get_proxy_request(sip_proxy.sip_request)
                                      local req_url = url.get_proxy(req_proxy.rq_url)
                                      print("Request method name: "..req_proxy.rq_method_name)
                                      print("Request version: "..req_proxy.rq_version)
                                      print("Request url: "..req_url.user.."@"..req_url.host)
                                      nh:respond(200, "OK",
                                                 { SOATAG_USER_SDP_STR = "m=audio "..rtp_port.." RTP/AVP 0 8\r\n"..
                                                                         "a=rtpmap:0 PCMU/8000\r\n"..
                                                                         "a=rtpmap:8 PCMA/8000\r\n" })
                                  end
  
    callbacks[nua.nua_r_invite] = function (event, status, phrase, ua, nh, sip_lu, tags)
                                      print("nua_r_invite: status["..status.."] phrase["..phrase.."]")
                                  end
  
    callbacks[nua.nua_i_state] = function (event, status, phrase, ua, nh, sip_lu, tags)
                                     local tags_proxy = su.get_proxy_tags(tags)
                                     print("nua_i_state: status["..status.."] phrase["..phrase.."]")

                                     print ("callstate:" .. tags_proxy.NUTAG_CALLSTATE)
                                     if(tags_proxy.NUTAG_CALLSTATE == nua.nua_callstate_completed) then
                                         print("Sending bye !!")
                                         nh:bye()
                                     end

                                     local local_sdp = tags_proxy.SOATAG_LOCAL_SDP
                                     if local_sdp then 
                                         sdp_session_proxy    = sdp:get_proxy_session(local_sdp)
                                         sdp_connection_proxy = sdp:get_proxy_connection(sdp_session_proxy.sdp_connection)
                                         print("sdp_connection address =" .. sdp_connection_proxy.c_address)
                                         print ("local SDP:\n" .. tags_proxy.SOATAG_LOCAL_SDP_STR)
                                     end
                                     local remote_sdp = tags_proxy.SOATAG_REMOTE_SDP
                                     if remote_sdp then 
                                         print ("remote SDP:\n" .. tags_proxy.SOATAG_REMOTE_SDP_STR)
                                     end
                                 end

    callbacks[nua.nua_i_active] = function (event, status, phrase, ua, nh, sip_lu, tags)
                                      print("nua_i_active: status["..status.."] phrase["..phrase.."]")
                                  end

    callbacks[nua.nua_i_terminated] = function (event, status, phrase, ua, nh, sip_lu, tags)
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

function shutdown_a (event, status, phrase, ua, sip_lu, tags)
    print("User Agent A shutdown: status["..status.."] phrase["..phrase.."]")
    if (status == 200) then
        a_quit = true
    end
    if (a_quit and b_quit) then
        root:quit()
    end
end

ua_a = make_user_agent("1000", 5060, 4000, shutdown_a)

function shutdown_b (event, status, phrase, ua, sip_lu, tags)
    print("User Agent B shutdown: status["..status.. "] phrase["..phrase.."]")
    if (status == 200) then
        b_quit = true
    end
    if (a_quit and b_quit) then
        root:quit()
    end
end

ua_b = make_user_agent("1001", 5080, 5000, shutdown_b)

timer = su.timer_create(root:task(), 500)

timer:set(function (t)
              print("timer fired: shutdown...")
              ua_a:shutdown()
              ua_b:shutdown()
          end)

make_call(ua_a, "sip:1001@127.0.0.1:5080",
                "<sip:1000@127.0.0.1>",
                "<sip:1001@127.0.0.1>")

root:run()

su.deinit()

