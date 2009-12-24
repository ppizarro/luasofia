h1. Initialization 

Before usage, the module must be loaded on lua. You can do this using the require statement (available only in Lua 5.1).
All luasofia modules are loaded using require "luasofia.module_name"
SDP Example:

<pre><code class="lua">
sdp = require "luasofia.sdp"

</code></pre>

Now you can use the global var *sdp* to invoke the sdp module functions or to get tags and constants. On the examples above we assume this already have been done and the sdp module is loaded on the global var *sdp*

h1. Class SDPParser

*__gc*
Is called when Lua decides to garbage collect the SDPParser.
WARNING: After SDPParser is collected the sdp_session lightuserdata and its proxy no longer exists, since they cant be colected by lua they are freed when the sdp_parser that originated them is colected. 

*__tostring*
Parses the sdp msg and returns the sdp_session as a string.

*get_sdp_session()*
Parses the sdp msg and returns the sdp_session lightuserdata.
* @return - sdp_session lightuserdata.
WARNING: After SDPParser is collected the sdp_session lightuserdata and its proxy no longer exists, since they cant be colected by lua they are freed when the sdp_parser that originated them is colected.  

Example:
<pre><code class="lua">
sdp_session = sdp_parser:get_sdp_session()

</code></pre>

h1. Functions

*parse(msg, flags)*
Given an string msg and the sdp_flags parses it and returns a parser.
* @param msg - The sdp message.
* @param flags - sdp flags.
* @return A SDPParser object

Example:

<pre><code class="lua">
sdp_parser_msg = "v=0\r\n"
                               "o=- 449395707 11549558 IN IP4 192.168.170.145\r\n"
                               "s=-\r\n"
                               "c=IN IP4 192.168.170.145\r\n"
                               "t=0 0\r\n"
                               "m=audio 5000 RTP/AVP 0\r\n"
                               "a=rtpmap:0 PCMU/8000\r\n"

sdp_parser = sdp.parse(sdp_parser_msg, 0)

</code></pre>
                
*get_proxy_session(sdp_session_lightudata)*
Given a sdp_session lightuserdata, returns the proxy of the sdp_session lightuserdata. 

* @param sdp_session_lightudata
* @return sdp_session_proxy

Example:

<pre><code class="lua">
sdp_parser = sdp.parse(sdp_parser_msg, 0)

sdp_session = sdp_parser:get_sdp_session()

sdp_session_proxy = sdp.get_proxy_session(sdp_session)

</code></pre>

*get_proxy_attribute(sdp_attribute_lightudata)*
Given a sdp_attribute lightuserdata, returns the proxy of the sdp_attribute lightuserdata. 

* @param sdp_attribute_lightudata
* @return sdp_attribute_proxy

Example:

<pre><code class="lua">
sdp_parser = sdp.parse(sdp_parser_msg, 0)

sdp_session = sdp_parser:get_sdp_session()

sdp_session_proxy = sdp.get_proxy_session(sdp_session)

sdp_attribute_proxy = sdp.get_proxy_attribute(sdp_session_proxy.sdp_attributes)

</code></pre>

*get_proxy_bandwidth(sdp_bandwidth_lightudata)*
Given a sdp_bandwidth lightuserdata, returns the proxy of the sdp_bandwidth lightuserdata. 

* @param sdp_bandwidth_lightudata
* @return sdp_bandwidth_proxy

Example:

<pre><code class="lua">
sdp_parser = sdp.parse(sdp_parser_msg, 0)

sdp_session = sdp_parser:get_sdp_session()

sdp_session_proxy = sdp.get_proxy_session(sdp_session)

sdp_bandwidth_proxy = sdp.get_proxy_bandwidth(sdp_session_proxy.sdp_bandwidths)

</code></pre>

*get_proxy_connection(sdp_connection_lightudata)*
Given a sdp_connectionlightuserdata, returns the proxy of the sdp_connection lightuserdata. 

* @param sdp_connection_lightudata
* @return sdp_connection_proxy

Example:

<pre><code class="lua">
sdp_parser = sdp.parse(sdp_parser_msg, 0)

sdp_session = sdp_parser:get_sdp_session()

sdp_session_proxy = sdp.get_proxy_session(sdp_session)

sdp_connection_proxy = sdp.get_proxy_connection(sdp_session_proxy.sdp_connection)

</code></pre>

*get_proxy_key(sdp_key_lightudata)*
Given a sdp_key lightuserdata, returns the proxy of the sdp_key lightuserdata. 

* @param sdp_key_lightudata
* @return sdp_key_proxy

Example:

<pre><code class="lua">
sdp_parser = sdp.parse(sdp_parser_msg, 0)

sdp_session = sdp_parser:get_sdp_session()

sdp_session_proxy = sdp.get_proxy_session(sdp_session)

sdp_key_proxy = sdp.get_proxy_key(sdp_session_proxy.sdp_key)

</code></pre>

*get_proxy_media(sdp_media_lightudata)*
Given a sdp_media lightuserdata, returns the proxy of the sdp_media lightuserdata. 

* @param sdp_media_lightudata
* @return sdp_media_proxy

Example:

<pre><code class="lua">
sdp_parser = sdp.parse(sdp_parser_msg, 0)

sdp_session = sdp_parser:get_sdp_session()

sdp_session_proxy = sdp.get_proxy_session(sdp_session)

sdp_media_proxy = sdp.get_proxy_media(sdp_session_proxy.sdp_media)

</code></pre>

*get_proxy_rtpmap(sdp_rtpmap_lightudata)*
Given a sdp_rtpmap lightuserdata, returns the proxy of the sdp_rtpmap lightuserdata. 

* @param sdp_rtpmap_lightudata
* @return sdp_rtpmap_proxy

Example:

<pre><code class="lua">
sdp_parser = sdp.parse(sdp_parser_msg, 0)

sdp_session = sdp_parser:get_sdp_session()

sdp_session_proxy = sdp.get_proxy_session(sdp_session)

sdp_media_proxy = sdp.get_proxy_media(sdp_session_proxy.sdp_media)

sdp_rtpmap_proxy = sdp.get_proxy_rtpmap(sdp_media_proxy.m_rtpmaps)

</code></pre>

*get_proxy_list(sdp_list_lightudata)*
Given a sdp_list lightuserdata, returns the proxy of the sdp_list lightuserdata. 

* @param sdp_list_lightudata
* @return sdp_list_proxy

Example:

<pre><code class="lua">
sdp_parser = sdp.parse(sdp_parser_msg, 0)

sdp_session = sdp_parser:get_sdp_session()

sdp_session_proxy = sdp.get_proxy_session(sdp_session)

sdp_media_proxy = sdp.get_proxy_media(sdp_session_proxy.sdp_media)

sdp_list_proxy = sdp.get_proxy_list(sdp_media_proxy.m_format)

</code></pre>

*get_proxy_origin(sdp_origin_lightudata)*
Given a sdp_origin lightuserdata, returns the proxy of the sdp_origin lightuserdata. 

* @param sdp_origin_lightudata
* @return sdp_origin_proxy

Example:

<pre><code class="lua">
sdp_parser = sdp.parse(sdp_parser_msg, 0)

sdp_session = sdp_parser:get_sdp_session()

sdp_session_proxy = sdp.get_proxy_session(sdp_session)

sdp_origin_proxy = sdp.get_proxy_attribute(sdp_session_proxy.sdp_origin)

</code></pre>

*get_proxy_repeat(sdp_repeat_lightudata)*
Given a sdp_repeat lightuserdata, returns the proxy of the sdp_repeat lightuserdata. 

* @param sdp_repeat_lightudata
* @return sdp_repeat_proxy

Example:

<pre><code class="lua">
sdp_parser = sdp.parse(sdp_parser_msg, 0)

sdp_session = sdp_parser:get_sdp_session()

sdp_session_proxy = sdp.get_proxy_session(sdp_session)

sdp_time_proxy = sdp.get_proxy_time(sdp_session_proxy.sdp_time)

sdp_repeat_proxy =  sdp.get_proxy_repeat(sdp_time_proxy.t_repeat)

</code></pre>

*get_proxy_time(sdp_time_lightudata)*
Given a sdp_time lightuserdata, returns the proxy of the sdp_time lightuserdata. 

* @param sdp_time_lightudata
* @return sdp_time_proxy

Example:

<pre><code class="lua">
sdp_parser = sdp.parse(sdp_parser_msg, 0)

sdp_session = sdp_parser:get_sdp_session()

sdp_session_proxy = sdp.get_proxy_session(sdp_session)

sdp_time_proxy = sdp.get_proxy_time(sdp_session_proxy.sdp_time)

</code></pre>

* *See also*: "sdp_test":http://github.com/ppizarro/luasofia/blob/master/test/sdp.lua
