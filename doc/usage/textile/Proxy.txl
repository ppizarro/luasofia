One of the reasons we decided to use "proxy pattern":1 on luasofia is because of the way sofia works on its callbacks.
When Sofia calls a callback all the structures it passes to the callback function are valid only inside the callback function, once you got out the callback function Sofia free all alocated structures used in the callback. 

Because of that behaviour we had to decide between copy all the structures (it would be expensive since some Sofia structures are gigantic) and pass to lua as full userdata, and use lua garbage collector, or use a proxy pattern to acess the lightuserdata, because of the cost involved on copying all the time we decided for the proxy.

Some lightuserdata pointer passed on the callback function by Sofia can be transformed on a proxy, this proxy turns possible to access the attributes of the struct, (but only access, no modifications are allowed). But remember, it is still lightuserdata, lua gc will not handle it, and after the callback function ends it is NOT safe to use the proxy object, because Sofia could already freed it.

So you will find out that some objects on luasofia are full userdata (Lua objects) and have they're own __gc method defined, while other objects are only Sofia lighuserdata, you must take care when you create the proxy of a lightuserdata, read the modules documentation carefully and see the examples, the lifetime of the lightuserdata on memory may be different, depending on Sofia memory management, callbacks are one case, but there is more cases where proxies are used.

This difference between a proxy and a full userdata is clear since proxies must be created explicitly, luasofia will never return a proxy to you, it returns a full userdata with its own __gc method (sometimes we call this a object, since it is a full Lua object, that can be collected by Lua) or it returns a pointer to lightuserdata, it is you that must create the proxy of the lightuserdata using the right proxy function (or creating yours if you intend to expand the luasofia, since not all the Sofia structures have a proxy function).

[1]http://en.wikipedia.org/wiki/Proxy_pattern
