-----------------------------------------------------------------------------
--
-- @author Paulo Pizarro  <paulo.pizarro@gmail.com>
-- @author Tiago Katcipis <tiagokatcipis@gmail.com>
--
-- This file is part of Luasofia.
--
-- Luasofia is free software: you can redistribute it and/or modify
-- it under the terms of the GNU Lesser General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
-- 
-- Luasofia is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU Lesser General Public License for more details.

-- You should have received a copy of the GNU Lesser General Public License
-- along with Luasofia.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------

require "lunit"
local sdp = require "sofia.sdp"

module("sdp_testcase", lunit.testcase, package.seeall)

local sdp_parser_msg = table.concat({"v=0\r\n",
                                     "o=- 449464639571140607 115495315904426258 IN IP4 192.168.170.145\r\n",
                                     "s=-\r\n",
                                     "c=IN IP4 192.168.170.145\r\n",
                                     "t=0 0\r\n",
                                     "m=audio 5000 RTP/AVP 0\r\n",
                                     "a=rtpmap:0 PCMU/8000\r\n",
                                     "a=fmtp:0 annexb=yes\r\n",
                                     "a=ptime:8\r\n",
                                     "a=crypto:1 AES_CM_128_HMAC_SHA1_80 inline:NzB4d1BINUAvLEw6UzF3WSJ+PSdFcGdUJShpX1Zj\r\n"})

function setUp()
    sdp_parser = sdp.parse(sdp_parser_msg, 0)
    sdp_session       = sdp_parser:get_sdp_session()
    sdp_session_proxy = sdp.get_proxy_session(sdp_session)
    sdp_media         = sdp_session_proxy.sdp_media
    sdp_media_proxy   = sdp.get_proxy_media(sdp_media)
end

function test_an_sdp_parser_has_a_string_representation()
    assert_not_nil(sdp_parser)
    assert_equal(sdp_parser_msg, tostring(sdp_parser))
end

-----------------------
-- sdp_session tests --
-----------------------
function test_can_get_sdp_session_lightudata()
    assert_not_nil(sdp_session)
    assert_equal("userdata", type(sdp_session))
end

function test_can_get_sdp_session_proxy()
    assert_not_nil(sdp_session)
    assert_not_nil(sdp_session_proxy)
    assert_equal("userdata", type(sdp_session_proxy))
end

function test_can_access_sdp_session_proxy_members()
    assert_not_nil(sdp_session)
    assert_not_nil(sdp_session_proxy)
    
    -- 64 bits size test assert_equal(128, sdp_session_proxy.sdp_size)
    -- 32 bits size test assert_equal(64, sdp_session_proxy.sdp_size)
    assert_equal("-", sdp_session_proxy.sdp_subject)
    assert_equal(nil, sdp_session_proxy.sdp_information)
    assert_equal(nil, sdp_session_proxy.sdp_uri)
    assert_equal(nil, sdp_session_proxy.sdp_charset)
    assert_equal("userdata", type(sdp_session_proxy.sdp_origin))
    assert_equal(nil, sdp_session_proxy.sdp_emails)
    assert_equal(nil, sdp_session_proxy.sdp_phones)
    assert_equal("userdata", type(sdp_session_proxy.sdp_connection))
    assert_equal(nil, sdp_session_proxy.sdp_bandwidths)
    assert_equal("userdata", type(sdp_session_proxy.sdp_time))
    assert_equal(nil, sdp_session_proxy.sdp_key)
    assert_equal(nil, sdp_session_proxy.sdp_attributes)
    assert_equal("userdata", type(sdp_session_proxy.sdp_media))
end

----------------------
-- sdp_origin tests --
----------------------
function test_can_get_sdp_origin_lightudata()
    local sdp_origin = sdp_session_proxy.sdp_origin
    assert_not_equal(nil, sdp_origin)
    assert_equal("userdata", type(sdp_origin))
end

function test_can_get_sdp_origin_proxy()
    local sdp_origin = sdp_session_proxy.sdp_origin
    assert_not_equal(nil, sdp_origin)
    local sdp_origin_proxy = sdp.get_proxy_origin(sdp_origin)
    assert_not_equal(nil, sdp_origin_proxy)
    assert_equal("userdata", type(sdp_origin_proxy))
end

function test_can_access_sdp_origin_proxy_members()
    local sdp_origin = sdp_session_proxy.sdp_origin
    assert_not_equal(nil, sdp_origin)
    local sdp_origin_proxy = sdp.get_proxy_origin(sdp_origin)
    assert_not_equal(nil, sdp_origin_proxy)   
     
    -- 64 bits assert_equal(40, sdp_origin_proxy.o_size)
    -- 32 bits assert_equal(28, sdp_origin_proxy.o_size)
    assert_equal("-", sdp_origin_proxy.o_username)
    assert_equal(tostring(1.2701222966836e-278), tostring(sdp_origin_proxy.o_id))
    assert_equal(tostring(6.1412919304867e-301), tostring(sdp_origin_proxy.o_version))
    assert_not_equal(nil, sdp_origin_proxy.o_address)
    assert_equal("userdata", type(sdp_origin_proxy.o_address))
 
end

--------------------------
-- sdp_connection tests --
--------------------------
function test_can_get_sdp_connection_lightudata()
    local sdp_connection = sdp_session_proxy.sdp_connection
    assert_not_equal(nil, sdp_connection)
    assert_equal("userdata", type(sdp_connection))
end

function test_can_get_sdp_connection_proxy()
    local sdp_connection = sdp_session_proxy.sdp_connection
    assert_not_equal(nil, sdp_connection)
    local sdp_connection_proxy = sdp.get_proxy_connection(sdp_connection)
    assert_not_equal(nil, sdp_connection_proxy)
    assert_equal("userdata", type(sdp_connection_proxy))
end

function test_can_access_sdp_connection_proxy_members()
    local sdp_connection = sdp_session_proxy.sdp_connection
    assert_not_equal(nil, sdp_connection)
    local sdp_connection_proxy = sdp.get_proxy_connection(sdp_connection)
    assert_not_equal(nil, sdp_connection_proxy)
    assert_equal("userdata", type(sdp_connection_proxy))

    -- 64 bits assert_equal(40, sdp_connection_proxy.c_size)
    -- 32 bits assert_equal(28, sdp_connection_proxy.c_size)
    assert_equal(nil, sdp_connection_proxy.c_next)
    assert_equal(sdp.sdp_net_in,    sdp_connection_proxy.c_nettype)
    assert_equal(sdp.sdp_addr_ip4,  sdp_connection_proxy.c_addrtype)
    assert_equal("192.168.170.145", sdp_connection_proxy.c_address)
    assert_equal(1, sdp_connection_proxy.c_groups)
end

--------------------
-- sdp_time tests --
--------------------
function test_can_get_sdp_time_lightudata()
    local sdp_time = sdp_session_proxy.sdp_time
    assert_not_equal(nil, sdp_time)
    assert_equal("userdata", type(sdp_time))
end

function test_can_get_sdp_time_proxy()
    local sdp_time = sdp_session_proxy.sdp_time
    assert_not_equal(nil, sdp_time)
    local sdp_time_proxy = sdp.get_proxy_time(sdp_time)
    assert_not_equal(nil, sdp_time_proxy)
    assert_equal("userdata", type(sdp_time_proxy))
end

function test_can_access_sdp_time_proxy_members()
    local sdp_time = sdp_session_proxy.sdp_time
    assert_not_equal(nil, sdp_time)
    local sdp_time_proxy = sdp.get_proxy_time(sdp_time)
    assert_not_equal(nil, sdp_time_proxy)
    assert_equal("userdata", type(sdp_time_proxy))

    -- 64 bits assert_equal(48,  sdp_time_proxy.t_size)
    -- 32 bits assert_equal(24,  sdp_time_proxy.t_size)
    assert_equal(nil, sdp_time_proxy.t_next)
    assert_equal(0,   sdp_time_proxy.t_start)
    assert_equal(0,   sdp_time_proxy.t_stop)
    assert_equal(nil, sdp_time_proxy.t_repeat)
end

---------------------
-- sdp_media tests --
---------------------
function test_can_get_sdp_media_lightudata()
    assert_not_equal(nil, sdp_media)
    assert_equal("userdata", type(sdp_media))
end

function test_can_get_sdp_media_proxy()
    assert_not_equal(nil, sdp_media)
    assert_not_equal(nil, sdp_media_proxy)
    assert_equal("userdata", type(sdp_media_proxy))
end

function test_can_access_sdp_media_proxy_members()
    assert_not_equal(nil, sdp_media)
    assert_not_equal(nil, sdp_media_proxy)
    assert_equal("userdata", type(sdp_media_proxy))

    -- 64 bits assert_equal(144, sdp_media_proxy.m_size) 
    -- 32 bits assert_equal(72, sdp_media_proxy.m_size) 
    assert_equal(nil, sdp_media_proxy.m_next)
    assert_equal(sdp_session, sdp_media_proxy.m_session)
    assert_equal(sdp.sdp_media_audio, sdp_media_proxy.m_type)
    assert_equal("audio", sdp_media_proxy.m_type_name)
    assert_equal(5000, sdp_media_proxy.m_port)
    assert_equal(0, sdp_media_proxy.m_number_of_ports)
    assert_equal(sdp.sdp_proto_rtp,sdp_media_proxy.m_proto)
    assert_equal("RTP/AVP", sdp_media_proxy.m_proto_name)
    assert_equal(nil, sdp_media_proxy.m_format)
    assert_equal("userdata", type(sdp_media_proxy.m_rtpmaps))
    assert_equal(nil, sdp_media_proxy.m_information)
    assert_equal(nil, sdp_media_proxy.m_connections)
    assert_equal(nil, sdp_media_proxy.m_bandwidths)
    assert_equal(nil, sdp_media_proxy.m_key)
    assert_not_nil(sdp_media_proxy.m_attributes)
    assert_equal(nil, sdp_media_proxy.m_user)
end

----------------------
-- sdp_rtpmap tests --
----------------------
function test_can_get_sdp_rtpmap_lightudata()
    local sdp_rtpmap        = sdp_media_proxy.m_rtpmaps
    assert_not_nil(sdp_rtpmap)
    assert_equal("userdata", type(sdp_rtpmap))
end

function test_can_get_sdp_rtpmap_proxy()
    local sdp_rtpmap        = sdp_media_proxy.m_rtpmaps

    assert_not_nil(sdp_rtpmap)
    assert_equal("userdata", type(sdp_rtpmap))
    
    local sdp_rtpmap_proxy = sdp.get_proxy_rtpmap(sdp_rtpmap)
    assert_not_nil(sdp_rtpmap_proxy)
    assert_equal("userdata", type(sdp_rtpmap_proxy))
end

function test_can_get_sdp_rtpmap_fields()
    local sdp_rtpmap        = sdp_media_proxy.m_rtpmaps

    assert_not_nil(sdp_rtpmap)
    assert_equal("userdata", type(sdp_rtpmap))

    local sdp_rtpmap_proxy = sdp.get_proxy_rtpmap(sdp_rtpmap)

    assert_not_nil(sdp_rtpmap_proxy)
    assert_equal("userdata", type(sdp_rtpmap_proxy))
    assert_nil(sdp_rtpmap_proxy.rm_params)        
    assert_equal("annexb=yes", sdp_rtpmap_proxy.rm_fmtp)   
    assert_equal("PCMU",       sdp_rtpmap_proxy.rm_encoding)
    assert_equal(8000,         sdp_rtpmap_proxy.rm_rate)
end


-------------------------
-- sdp_attribute tests --
-------------------------
function test_can_get_sdp_attribute_lightudata()
    local sdp_attribute     = sdp_media_proxy.m_attributes

    assert_not_nil(sdp_attribute)
    assert_equal("userdata", type(sdp_attribute))
end

function test_can_get_sdp_attribute_proxy()
    local sdp_attribute     = sdp_media_proxy.m_attributes

    assert_not_nil(sdp_attribute)
    assert_equal("userdata", type(sdp_attribute))

    local sdp_attribute_proxy = sdp.get_proxy_attribute(sdp_attribute)

    assert_not_nil(sdp_attribute_proxy)
    assert_equal("userdata", type(sdp_attribute_proxy))
end

function test_can_get_sdp_attribute_fields()
    local sdp_attribute     = sdp_media_proxy.m_attributes

    assert_not_nil(sdp_attribute)
    assert_equal("userdata", type(sdp_attribute))

    local sdp_attribute_proxy = sdp.get_proxy_attribute(sdp_attribute)

    assert_not_nil(sdp_attribute_proxy)
    assert_equal("userdata", type(sdp_attribute_proxy))

    assert_equal("ptime", sdp_attribute_proxy.a_name)
    assert_equal("8", sdp_attribute_proxy.a_value)

    sdp_attribute = sdp_attribute_proxy.a_next
    assert_not_nil(sdp_attribute)

    sdp_attribute_proxy = sdp.get_proxy_attribute(sdp_attribute)
    assert_not_nil(sdp_attribute_proxy)

    assert_equal("crypto", sdp_attribute_proxy.a_name)
    assert_equal("1 AES_CM_128_HMAC_SHA1_80 inline:NzB4d1BINUAvLEw6UzF3WSJ+PSdFcGdUJShpX1Zj", sdp_attribute_proxy.a_value)
end

lunit.main()
