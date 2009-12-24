h1. Initialization 

Before usage, the module must be loaded on lua. You can do this using the require statement (available only in Lua 5.1).
All luasofia modules are loaded using require "luasofia.module_name"
SOAExample:

<pre><code class="lua">
soa= require "luasofia.soa"
</code></pre>

Now you can use the global var *soa* to invoke the soa module functions or to get tags and constants. On the examples above we assume this already have been done and the soa module is loaded on the global var *soa*.
