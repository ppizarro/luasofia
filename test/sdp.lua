require "lunit"
sdp = require "luasofia.sdp"

module("sdp_testcase", lunit.testcase, package.seeall)
sdp_parser_msg = "v=0\r\no=- 449464639571140607 115495315904426258 IN IP4 192.168.170.145\r\ns=-\r\nc=IN IP4 192.168.170.145\r\nt=0 0\r\nm=audio 5000 RTP/AVP 0\r\na=rtpmap:0 PCMU/8000\r\n"

function setUp()
    sdp_parser = sdp.parse(sdp_parser_msg, 0)
end

function test_an_sdp_parser_has_a_string_representation()
    assert_not_equal(nil, sdp_parser)
    assert_equal(sdp_parser_msg, tostring(sdp_parser))
end

function test_can_get_the_sdp_session_lightudata()
    local sdp_session = sdp_parser:get_sdp_session()
    assert_not_equal(nil, sdp_session)
end

function test_can_get_the_sdp_session_proxy()
    local sdp_session = sdp_parser:get_sdp_session()
    assert_not_equal(nil, sdp_session)
    local sdp_session_proxy = sdp.get_proxy_session(sdp_session)
    assert_not_equal(nil, sdp_session_proxy)
end

function test_can_access_the_sdp_session_proxy_members()
    local sdp_session = sdp_parser:get_sdp_session()
    assert_not_equal(nil, sdp_session)
    local sdp_session_proxy = sdp.get_proxy_session(sdp_session)
    assert_not_equal(nil, sdp_session_proxy)
    --TODO acess members and test values
end


lunit.main()
