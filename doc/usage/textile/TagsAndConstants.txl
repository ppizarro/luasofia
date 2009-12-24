Each Luasofia module register its own set of tags and constants. 

h1. Tags

The registered Tags are used to build a [[Tag Table]] and to use the [[Tags Proxy]]. Although the tags registration is made by each module, the tags registered are global, so when you build a [[Tag Table]] or use a [[Tags Proxy]] you must just be sure that someone have registered that tag. 

Examples of tags usage can be found on [[Tags Proxy]] and [[Tag Table]].

h1. Constants

The constants registration are a little different, they are used to access Sofia enums, and they are not global, to access a module constant you must call module.my_constant, calling module.my_constant will return an integer with the same value of the enum on Sofia SIP.

Example:

<pre><code class="lua">
function nua_event_callback(event, status, phrase, ua, nh, sip, tags)
    local t = su.get_proxy_tags(tags)
    print("nua_i_state: status["..status.."] phrase["..phrase.."]")
    print ("callstate:" .. t.NUTAG_CALLSTATE)
    if(t.NUTAG_CALLSTATE == nua.nua_callstate_completed) then
        print("Sending bye !!")
        nh:bye()
    end
end
</code></pre>

The name of the constants are the same used on the Enums defined on Sofia SIP, for example the nua_callstate_completed used on the example above is defined "here":http://sofia-sip.sourceforge.net/refdocs/nua/nua__tag_8h.html#7b5fb7519f1476fdb802b9a60b496176 

