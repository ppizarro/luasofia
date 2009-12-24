h1. Initialization 

Before usage, the module must be loaded on lua. You can do this using the require statement (available only in Lua 5.1).
All luasofia modules are loaded using require "luasofia.module_name"
URL Example:

<pre><code class="lua">
url= require "luasofia.url"
</code></pre>

Now you can use the global var *url* to call the url module functions or to get tags and constants. On the examples above we assume this already have been done and the url module is loaded on the global var *url*.

h1. Functions

*get_proxy(url_lightudata)*
Given a url lightuserdata, returns the proxy of the url lightuserdata. 

* @param url_lightudata.
* @return url proxy.

Example

<pre><code class="lua">
function nua_event_callback(event, status, phrase, ua, nh, lu_sip, tags)
    local s = sip.get_proxy(lu_sip)
    local from = sip.get_proxy_addr(s.sip_from)
    local to = sip.get_proxy_addr(s.sip_to)
    local contact = sip.get_proxy_contact(s.sip_contact)
    local from_url = url.get_proxy(from.a_url)
    local to_url = url.get_proxy(to.a_url)
    local contact_url = url.get_proxy(contact.m_url)
 
    print("nua_i_invite: status["..status.."] phrase["..phrase.."]")
    print("from: "..from_url.user.."@"..from_url.host)
    print("to: "..to_url.user.."@"..to_url.host)
    print("contact: "..contact_url.user.."@"..contact_url.host)
 
    local req = sip.get_proxy_request(s.sip_request)
    local req_url = url.get_proxy(req.rq_url)
    print("Request method name: "..req.rq_method_name)
    print("Request version: "..req.rq_version)
    print("Request url: "..req_url.user.."@"..req_url.host)

end
</code></pre>

