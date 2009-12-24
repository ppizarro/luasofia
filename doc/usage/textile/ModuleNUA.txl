h1. Initialization 

Before usage, the module must be loaded on lua. You can do this using the require statement (available only in Lua 5.1).
All luasofia modules are loaded using require "luasofia.module_name"
NUA Example:
<pre><code class="lua">
nua = require "luasofia.nua"

</code></pre>

Now you can use the global var *nua* to invoke the nua module functions or to get tags and constants. On the examples above we assume this already have been done and the nua module is loaded on the global var *nua*

h1. Functions

*create(su_root, callback_table, tag_table)*
Creates a nua object.

* @param su_root            - su_root lua object.
* @param callback_table - A table mapping the events to the function that will treat the event. 
* @param tag_table         - A [[Tag Table]]
* @return                         - A nua lua object.

Example: 

<pre><code class="lua">
 root = su.root_create()

 callbacks = {}

 callbacks[nua.nua_r_invite] = function (event, status, phrase, ua, uah, sip, tags)
                                print("r_invite: status["..status.."] phrase["..phrase.."]")
                              end

 ua = nua.create(root, callbacks,
                    { NUTAG_URL = "sip:*:5060;transport=udp",
                     NUTAG_USER_AGENT = "luasofia",
                     NUTAG_MEDIA_ENABLE = 1,
                     NUTAG_EARLY_ANSWER = 1,
                     NUTAG_OUTBOUND = "no-validate no-options-keepalive no-natify",
                     NUTAG_M_USERNAME = username
                    })

</code></pre>

*event_name(event_id)*
Given an integer event id returns the event name as string.

* @param  event_id - id of the event.
* @return                 - the event name.

Callback function example, receives an event id and prints it as string:

<pre><code class="lua">
function (event, status, phrase, ua, sip, tags)
    print("event_default: event["..nua:event_name(event)..
          "] status["..status.."] phrase["..phrase.."]")
end

</code></pre>

h1. Class Nua

*set_params(tag_table)*
Sets a tag table on a nua object
* @param tag_table - A [[Tag Table]]

Example:

<pre><code class="lua">
root = su.root_create()

callbacks = {}

callbacks[nua.nua_r_invite] = function (event, status, phrase, ua, uah, sip, tags)
                                 print("r_invite: status["..status.."] phrase["..phrase.."]")
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

</code></pre>

*handle_create(tag_table)*
Given a tag table creates a nua_handle object.
* @param tag_table - A [[Tag Table]]
* @return  nua_handle object.

Example:

<pre><code class="lua">
function make_call(nua_obj, uri, from, to)
    print("make_call: uri["..uri.."] from["..from.."] to["..to.."]")
    nua_handle_obj = nua_obj:handle_create({ NUTAG_URL = uri,
                                             SIPTAG_TO_STR = to,
                                             SIPTAG_FROM_STR = from })
end

</code></pre>

*shutdown()*
Shutdown NUA stack. 
Example:

<pre><code class="lua">
nua_obj:shutdown()

</code></pre>

*__gc()*
Called when lua collects the Nua object.

h1. Class NuaHandle

The NuaHandle class methods are very similar to the functions on Sofia nua module that receives as first argument a nua_handle_t*, but since the NuaHandle is passed implicitly on the method call the only arguments needed are the tag list, but in lua instead of a list of (tag_type, tag_value) we use a tag table.

*"invite":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#08d2f0de8ab234a6c980c5e6b5bfb306 (tag_table)*
* @param tag_table - A [[Tag Table]]

*"register":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#4e109705c6f57678a1ed46a22b2ccb0c (tag_table)*
* @param tag_table - A [[Tag Table]]

*"unregister":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#31e1e8d8f3b8a87e42aa8c7857cd4174 (tag_table)*
* @param tag_table - A [[Tag Table]]

*"ack":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#23fe9ab960269813b47dcb178358f24f (tag_table)*         
* @param tag_table - A [[Tag Table]]

*"prack":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#6cb1a0aad8b84e7f96b0583e7814716a (tag_table)*      
* @param tag_table - A [[Tag Table]]

*"options":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#0e1d81b2dcad7f1f467cdc04eaad66a6 (tag_table)*     
* @param tag_table - A [[Tag Table]]

*"publish":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#636497f34f37e22502606eb89540d9c7 (tag_table)*
* @param tag_table - A [[Tag Table]]

*"unpublish":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#8d0d3ce864a21ecbedbef88bd39bbc8f (tag_table)*
* @param tag_table - A [[Tag Table]]

*"message":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#ff4babef0d9fbb075a1a83bb08d01c94 (tag_table)*
* @param tag_table - A [[Tag Table]]

*"chat":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#0ce37ad42e9efb05ee7963643e81db72 (tag_table)*        
* @param tag_table - A [[Tag Table]]

*"info":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#6e35879dcd15695db409e4192cd45d57 (tag_table)*  
* @param tag_table - A [[Tag Table]]

*"subscribe":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#097676c639124c896fc36757047e004f (tag_table)*    
* @param tag_table - A [[Tag Table]]

*"unsubscribe":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#cf9f52dcfb165c3f89db88e984cf50ba (tag_table)*
* @param tag_table - A [[Tag Table]]

*"notify":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#7ca4178e5d651bd4b549b9a33e049332 (tag_table)*       
* @param tag_table - A [[Tag Table]]

*"notifier":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#4584d03ba5462b2585dfc1874192d5b2 (tag_table)*    
* @param tag_table - A [[Tag Table]]

*"terminate":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#4213ceb7348a55aba5f1e876644377ae (tag_table)*    
* @param tag_table - A [[Tag Table]]

*"refer":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#fa30c00e43df67b491df8325ae64f89e (tag_table)*       
* @param tag_table - A [[Tag Table]]

*"update":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#ce817d53093c64ccfd2f9b88e1b5ecb0 (tag_table)*       
* @param tag_table - A [[Tag Table]]

*"bye":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#64b377a86b175a6307ad6e21e35e18f4 (tag_table)*
* @param tag_table - A [[Tag Table]]
          
*"cancel":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#8ec3db6a10cf98d80c7eb009f05a88ed (tag_table)*      
* @param tag_table - A [[Tag Table]]

*"authenticate":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#a9cf0d8c7f16326be265501cfc3a442e (tag_table)* 
* @param tag_table - A [[Tag Table]]

*"authorize":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#43e68493fc2e849a221c5ccea6855986 (tag_table)*    
* @param tag_table - A [[Tag Table]]

*"method":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#ee0c4a3e3af2af36f2f8bff25816f7a4 (tag_table)* 
* @param tag_table - A [[Tag Table]]
     
*"respond":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#6cb244f191b9140820bf27b626c0b77f (status, phrase, tag_table)*
* @param status      - SIP response status code (see RFCs of SIP). 
* @param phrase     - Free text (default response phrase is used if nil) 
* @param tag_table - A [[Tag Table]]    

*__gc ()*        
Called when lua collects the NuaHandle object.

h1. Nua Event Callback

The signature of the functions passed on the callback table on nua is like the "Sofia callback signature":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#e679327ac260322e02504de2f5a97898 , the only diference is that there is no nua_magic and there is no nua_handle_magic. 

The function prototype is:

*function my_callback (event, status, phrase, ua, uah, sip, tags)*
* @param event -  The "nua_event":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#8f166e3352161a8bcbf50964481cc3db
* @param status - Integer representing the status code.
* @param phrase - The phrase.
* @param ua - The Nua object.
* @param uah - The NuaHandle object.    
* @param sip - The sip lightuserdata (see [[Proxy]]).
* @param tags - The tags lighuserdata (see [[Proxy]]).

Instead of using just one big callback function with a switch inside luasofia uses a callback table, the key is the "nua_event":http://sofia-sip.sourceforge.net/refdocs/nua/nua_8h.html#8f166e3352161a8bcbf50964481cc3db and the value is the function that will treat that event, so instead of one big function you can have a lot of small functions, one to treat each of the nua events. 
You can define a function as default callback function too, so everytime an event that does not have a specific callback function is called, this default function will be called.

Example of how to build a callback table:

<pre><code class="lua">
callbacks = {}

callbacks[nua.event_default] = function (event, status, phrase, ua, sip, tags)
                                 print("event_default: event["..nua:event_name(event)..
                                       "] status["..status.."] phrase["..phrase.."]")
                               end

callbacks[nua.nua_i_terminated] = function (event, status, phrase, ua, sip, tags)
                                    print("nua_i_terminated: status["..status..
                                          "] phrase["..phrase.."]")
                                  end

callbacks[nua.nua_i_active] = function (event, status, phrase, ua, sip, tags)
                                print("nua_i_active: status["..status..
                                      "] phrase["..phrase.."]")
                              end

callbacks[nua.nua_r_invite] = function (event, status, phrase, ua, sip, tags)
                                print("nua_r_invite: status["..status..
                                      "] phrase["..phrase.."]")
                              end

</code></pre>
                                      
Or you can pass an already defined function, instead of defining an anonimous function:

<pre><code class="lua">
function handle_invite
  print("nua_r_invite: status["..status.."] phrase["..phrase.."]")
end

callbacks = {}

callbacks[nua.nua_r_invite] = handle_invite

</code></pre>
                                      
* *See also*: "nua_test":http://github.com/ppizarro/luasofia/blob/master/test/nua.lua
