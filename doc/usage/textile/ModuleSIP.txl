h1. Initialization 

Before usage, the module must be loaded on lua. You can do this using the require statement (available only in Lua 5.1).
All luasofia modules are loaded using require "luasofia.module_name"
SIP Example:

<pre><code class="lua">
sip = require "luasofia.sip"
</code></pre>

Now you can use the global var *sip* to invoke the sip module functions or to get tags and constants. On the examples above we assume this already have been done and the sip module is loaded on the global var *sip*

h1. Functions

All the examples are made inside the nua event callback function, that passes a sip lightuserdata. The "sip_t":http://sofia-sip.sourceforge.net/refdocs/sip/structsip__s.html struct is quite big, not all the fields on it already has a proxy to handle it, if you need to access some data that is on the sip_t structure and there in no proxy for it, feel free to do the proxy of this filed and contribute :-).

*get_proxy(sip_lightudata)*
Given a sip lightuserdata, returns the proxy of the sip lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy = sip.get_proxy(sip_lightudata)
end
</code></pre>

*get_proxy_addr(sip_addr_lightudata)*
Given a sip_addr lightuserdata, returns the proxy of the sip_addr lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy = sip.get_proxy(sip_lightudata)
    local from = sip.get_proxy_addr(sip_proxy.sip_from)
end
</code></pre>

*get_proxy_contact(sip_contact_lightudata)*
Given a sip_contact lightuserdata, returns the proxy of the sip_contact lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy    = sip.get_proxy(sip_lightudata)
    local sip_contact = sip.get_proxy_contact(sip_proxy.sip_contact)
end
</code></pre>

*get_proxy_request(sip_request_lightudata)*
Given a sip_request lightuserdata, returns the proxy of the sip_request lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy    = sip.get_proxy(sip_lightudata)
    local sip_request = sip.get_proxy_request(sip_proxy.sip_request)
end
</code></pre>

*get_proxy_via(sip_via_lightudata)*
Given a sip_via lightuserdata, returns the proxy of the sip_via lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy    = sip.get_proxy(sip_lightudata)
    local sip_via= sip.get_proxy_via(sip_proxy.sip_via)
end
</code></pre>

*get_proxy_status(sip_status_lightudata)*
Given a sip_status lightuserdata, returns the proxy of the sip_status lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy    = sip.get_proxy(sip_lightudata)
    local sip_status= sip.get_proxy_status(sip_proxy.sip_status)
end
</code></pre>

*get_proxy_event(sip_event_lightudata)*
Given a sip_event lightuserdata, returns the proxy of the sip_event lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy    = sip.get_proxy(sip_lightudata)
    local sip_event = sip.get_proxy_event(sip_proxy.sip_event)
end
</code></pre>


*get_proxy_content_type(sip_content_type_lightudata)*
Given a sip_content_type lightuserdata, returns the proxy of the sip_content_type lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy  = sip.get_proxy(sip_lightudata)
    local sip_content_type = sip.get_proxy_content_type(sip_proxy.sip_content_type)
end
</code></pre>


*get_proxy_content_length(sip_content_length_lightudata)*
Given a sip_content_length lightuserdata, returns the proxy of the sip_content_length lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy    = sip.get_proxy(sip_lightudata)
    local sip_content_length = sip.get_proxy_content_length(sip_proxy.sip_content_length)
end
</code></pre>


*get_proxy_accept(sip_accept_lightudata)*
Given a sip_accept lightuserdata, returns the proxy of the sip_accept lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy    = sip.get_proxy(sip_lightudata)
    local sip_accept   = sip.get_proxy_accept(sip_proxy.sip_accept)
end
</code></pre>


*get_proxy_allow(sip_allow_lightudata)*
Given a sip_allow lightuserdata, returns the proxy of the sip_allow lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy    = sip.get_proxy(sip_lightudata)
    local sip_allow   = sip.get_proxy_allow(sip_proxy.sip_allow)
end
</code></pre>


*get_proxy_call_id(sip_call_id_lightudata)*
Given a sip_call_id lightuserdata, returns the proxy of the sip_call_id lightuserdata. 
Example:

<pre><code class="lua">
function (event, status, phrase, ua, nh, sip_lightudata, tags)
    local sip_proxy    = sip.get_proxy(sip_lightudata)
    local sip_call_id   = sip.get_proxy_allow(sip_proxy.sip_call_id)
end
</code></pre>

