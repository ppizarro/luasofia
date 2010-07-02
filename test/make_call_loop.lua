------------------------------------------------------------------------------
-- @author Paulo Pizarro  <paulo.pizarro@gmail.com>
-- @author Tiago Katcipis <tiagokatcipis@gmail.com>
--
-- This file is part of Luasofia.
--
-- Luasofia is free software: you can redistribute it and/or modify
-- it under the terms of the GNU Lesser General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.

-- Luasofia is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU Lesser General Public License for more details.
--
-- You should have received a copy of the GNU Lesser General Public License
-- along with Luasofia.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------------

su = require "sofia.su"
nua = require "sofia.nua"
sip = require "sofia.sip"
soa = require "sofia.soa"
url = require "sofia.url"
sdp = require "sofia.sdp"
tport = require "sofia.tport"

local callbacks = {}

local calls = 0
callbacks[nua.nua_i_invite] = function (event, status, phrase, ua, magic, nh, hmagic, sip_lu, tags)
                                  if nh then
                                      calls = calls + 1
                                      print("New call: "..calls)
                                      nh:respond(200, "Ok")
                                  end
                              end
  
callbacks[nua.nua_i_state] = function (event, status, phrase, ua, magic, nh, hmagic, sip_lu, tags)
                                 local tags_proxy = su.get_proxy_tags(tags)
                                 if(tags_proxy.NUTAG_CALLSTATE == nua.nua_callstate_completed) then
                                     print("Call terminated!")
                                     nh:bye()
                                 end
                             end

callbacks[nua.nua_i_terminated] = function (event, status, phrase, ua, magic, nh, hmagic, sip_lu, tags)
                                      if nh then
                                          nh:destroy()
                                      end
                                  end

local function make_call(ua, uri, from, to)

    local nh = ua:handle_create({ NUTAG_URL = uri,
                                  SIPTAG_TO_STR = to,
                                  SIPTAG_FROM_STR = from })
    if not nh then
        error("error on create nua handle!")
    end

    nh:invite()
end

local function make_user_agent(root, username, sip_port, rtp_port, obj)

    local url = "sip:*:" .. sip_port .. ";transport=udp"

    local ua = nua.create(root, callbacks, obj,
                          { NUTAG_URL = url,
                            NUTAG_USER_AGENT = "luasofia",
                            NUTAG_MEDIA_ENABLE = 1,
                            NUTAG_EARLY_ANSWER = 1,
                            NUTAG_OUTBOUND = "no-validate no-options-keepalive no-natify",
                            NUTAG_M_USERNAME = username
                          })

    if not ua then
        error("error on create nua!")
    end

    ua:set_params({ NUTAG_ENABLEINVITE = 1,
                    NUTAG_AUTOALERT = 1,
                    NUTAG_SESSION_TIMER = 0,
                    NUTAG_AUTOANSWER = 0,
                    SOATAG_USER_SDP_STR = "m=audio "..rtp_port.." RTP/AVP 0 8\r\n"..
                                          "a=rtpmap:0 PCMU/8000\r\n"..
                                          "a=rtpmap:8 PCMA/8000\r\n"
                  })
    return ua
end

su.init()

local root = su.root_create()

root:threading(false)

local ua_a = make_user_agent(root, "1000", 5090, 4000 )

local ua_b = make_user_agent(root, "1001", 5080, 5000 )

local timer = su.timer_create(root:task(), 500)

timer:set_for_ever(function (t)
                       collectgarbage("collect")
                       make_call(ua_a, "sip:1001@127.0.0.1:5080",
                                       "<sip:1000@127.0.0.1>",
                                       "<sip:1001@127.0.0.1>")
                   end)

root:run()

su.deinit()

