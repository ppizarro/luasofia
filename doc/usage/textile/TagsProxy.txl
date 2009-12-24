The Tags proxy is a little different from the normal proxies. The get_proxy_tags function can be found on the [[Module SU]], here we explain on how to use it. On a normal proxy you can access the fields that exist on the original C struct, in this case things are different. The Tags proxy is actually a proxy to a list of tags, the usage is basically call "tags_proxy.TAG_NAME", if there is a TAG_NAME inside the tags_proxy it will return the value associated with that TAG_NAME, if there is not a TAG_NAME on the tags_proxy it will return nil and if a TAG_NAME is invalid (not exist) it will raise an error.

Example:

<pre><code class="lua">
function nua_event_callback(event, status, phrase, ua, nh, sip, tags)
    local tags_proxy = su.get_proxy_tags(tags)
    print ("callstate:" .. tags_proxy.NUTAG_CALLSTATE)
    if(tags_proxy.NUTAG_CALLSTATE == nua.nua_callstate_completed) then
        print("Sending bye !!")
        nh:bye()
    end

    local local_sdp = tags_proxy.SOATAG_LOCAL_SDP
    if local_sdp then
        s = sdp:get_proxy_session(local_sdp)
        c = sdp:get_proxy_connection(s.sdp_connection)
        print("c=" .. c.c_address)
        print ("local SDP:\n" .. t.SOATAG_LOCAL_SDP_STR)
    end

end
</code></pre>

As you can see the value returned by the tag list can be from different types, in the given example the tags_proxy.NUTAG_CALLSTATE returns a integer, that is compared with the nua_callstate_completed constant (mapping to the Sofia enum value), but the tags_proxy.SOATAG_LOCAL_SDP returns a sdp_session lightuserdata. 

To use the proxy always check how the tags are defined on Sofia SIP, for example, the nua tags are documented on "nua module doc":http://sofia-sip.sourceforge.net/refdocs/nua/nua__tag_8h.html . 
