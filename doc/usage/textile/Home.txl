<img src="http://www.lua.org/images/powered-by-lua.gif" alt="" />

h1. Getting Started

LuaSofia is a "Lua":http://www.lua.org binding of Sofia-Sip library. Sofia-SIP is an open-source SIP User-Agent library, compliant with the IETF RFC3261 specification.

The best way to start using Luasofia is by understanding the [[Tag Table]], [[Proxy]], [[Tags Proxy]] and [[Tags and Constants]] concepts used on the design of the bind. A good look at the tests should help you to get started too:

* "sdp test":http://github.com/ppizarro/luasofia/blob/master/test/sdp.lua
* "nua test":http://github.com/ppizarro/luasofia/blob/master/test/nua.lua
* "su test":http://github.com/ppizarro/luasofia/blob/master/test/su.lua

Before using Luasofia on more advanced applications it is a good idea to read the modules documentation, since each module has it's own classes, proxies (the lifetime of the proxies can change), tags, constants. Everytime we talk about Class or Object you can understand it as a Lua full userdata, while a proxy is only a wrap around a Lua light userdata. 

* [[Module NUA]]
* [[Module SDP]]
* [[Module SOA]]
* [[Module SU]]
* [[Module SIP]]
* [[Module URL]]

Luasofia is a work in progress (today we have only enough to make Luasofia usable, but a lot of Sofia SIP code is not binded yet), we need help developing it and documenting it. To anyone interested on expanding Luasofia, a good look at the doc folder of the project should help.

Contact can be made through the project mailing list: 
* *luasofia-devel@lists.sourceforge.net*
