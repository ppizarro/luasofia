require "luasofia"
require "luasofia.sip"
require "lunit"

module( "url_testcase", lunit.testcase, package.seeall)

function setup()
             empty_url =  sip.create_url()
         end

function test_pad_default_value_nil()
             assert_equal(nil, empty_url.pad)
         end

function test_type_default_value_nil()
             assert_equal(nil, empty_url.type)
         end

function test_root_default_value_nil()
             assert_equal(nil, empty_url.root)
         end

function test_scheme_default_value_nil()
             assert_equal(nil, empty_url.scheme)
         end

function test_user_default_value_nil()
             assert_equal(nil, empty_url.user)
         end

function test_password_default_value_nil()
             assert_equal(nil, empty_url.password)
         end

function test_host_default_value_nil()
             assert_equal(nil, empty_url.host)
         end

function test_port_default_value_nil()
             assert_equal(nil, empty_url.port)
         end

function test_path_default_value_nil()
             assert_equal(nil, empty_url.path)
         end

function test_params_default_value_nil()
             assert_equal(nil, empty_url.params)
         end

function test_headers_default_value_nil()
             assert_equal(nil, empty_url.headers)
         end

function test_fragment_default_value_nil()
             assert_equal(nil, empty_url.fragment)
         end
