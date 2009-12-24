On luasofia, instead of using a list of  (tag_type_t tag, tag_value_t value, ...) like it is used on Sofia SIP we use a table every time we have to pass a list of tag_type-tag_value pairs. We decided to do that this way because it would be less C-like and more Lua-like. Luasofia will internally convert this table to a list of tag_type-tag_value to you.

For example, instead of calling:

<pre><code class="lua">
function_that_receives_tags ( TAG_1 , 1, TAG_2, "2", TAG_3, 44 )

</code></pre>

on luasofia you will call:

<pre><code class="lua">
function_that_receives_tags ( { TAG_1 = 1,  TAG_2 = "2", TAG_3 = 44 } ) 

</code></pre>

you can do something like this too:

<pre><code class="lua">
table = {}

table["TAG_1"] = 1
table["TAG_2"] = "2"
table["TAG_3"] = 44

function_that_receives_tags (table)

</code></pre>

The keys of the table are the tag_type_t, and the values of the table are the tag_value_t. When building a tag_table always use as key the name of the tag defined on Sofia, a real table for a Nua object would be:

<pre><code class="lua">
table = { NUTAG_URL = "url", 
              NUTAG_USER_AGENT = "luasofia", 
              NUTAG_MEDIA_ENABLE = 1, 
              NUTAG_EARLY_ANSWER = 1, 
              NUTAG_OUTBOUND = "no-validate no-options-keepalive no-natify", 
              NUTAG_M_USERNAME = "username" }

function_that_receives_nuatags(table)

</code></pre>

to build the table always check how the tags are defined on Sofia SIP, for example, the nua tags are documented on "nua module doc":http://sofia-sip.sourceforge.net/refdocs/nua/nua__tag_8h.html . 
 
