h1. Initialization 

Before usage, the module must be loaded on lua. You can do this using the require statement (available only in Lua 5.1).
All luasofia modules are loaded using require "luasofia.module_name"
SUExample:

<pre><code class="lua">
su= require "luasofia.su"

</code></pre>

Now you can use the global var *su* to invoke the nua module functions. On the examples above we assume this already have been done and the su module is loaded on the global var *su*.

h1. Functions

*"init":http://sofia-sip.sourceforge.net/refdocs/su/su_8h.html#503686af5011b14e80c40d00446509d8 ()*
Example:
<pre><code class="lua">
su.init()

</code></pre>

*"deinit ()":http://sofia-sip.sourceforge.net/refdocs/su/su_8h.html#38b7bd53ac4298a064eda38156d29bf9 ()*
Example:
<pre><code class="lua">
su.deinit()

</code></pre>

*root_create()*
Create a SURoot object.
* @return - SURoot object.

Example:
<pre><code class="lua">
su.init()
root = su.root_create()

</code></pre>

*timer_create(task, duration)*
Create a SUTimer object.
* @param - A SUTask object
* @param - Duration in miliseconds.
* @return  - SUTimer object.

Example:
<pre><code class="lua">
su.init()
root = su.root_create()
timer_create(root:task(), 200)

</code></pre>

*task_create()*
Create and init a task.
* @return The SUTask object, initialized.

Example:
<pre><code class="lua">
su.init()
task = su.task_create()

</code></pre>

*get_proxy_tags(tags_lightudata)*
* @param  tags_lightudata - A tagi_t* lightudata.
* @return  - A tagi_t proxy to acess the tags.

Example:
<pre><code class="lua">
function (event, status, phrase, ua, nh, sip, tags)
    local tags_proxy = su.get_proxy_tags(tags)
        if(tags_proxy.NUTAG_CALLSTATE == nua.nua_callstate_completed) then
            print("Sending bye !!")
            nh:bye()
        end
end

</code></pre>

h1. Class SUTimer

Since we use Lua closures to pass data to the callback functions, in Luasofia we do not use userdata on the callback functions. So the "su_timer_f":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#9d72b50d3b4faa31657f257c75aaefa5 in Luasofia will only receive a SUTimer object. It is like the su_timer_f changes to typedef void(*su_timer_f )(su_timer_t *t), there is no need for "magic" or the arg userdata to be passed.

*"set":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#2aeb29a79d667eb782596dbb5b126934 (wakeup_func)*
* @param wakeup_func - The callback function.
* @return  0 if successful, -1 otherwise. 

Example:
<pre><code class="lua">
su.init()
root = su.root_create()
timer = su.timer_create(root:task(), 200)
timer:set( function (su_timer_obj)
                    print("Timer fired!")
                    root:quit()
                end )

</code></pre>

*"set_interval":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#65b42881323946ae3d1240ca16fb3d02 (wakeup_func, interval)*
* @param wakeup_func - The callback function.
* @param interval          - Duration in milliseconds before timer wakeup is called.
* @return  0 if successful, -1 otherwise. 

Example:

<pre><code class="lua">
su.init()
root = su.root_create()
timer = su.timer_create(root:task(), 200)
timer:set_interval(function (su_timer_obj)
                                  print("Timer fired!")
                                  root:quit()
                             end, 200)

</code></pre>

*set_at()*
*TODO*

*"run":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#0edf53a2ba5e0eddee5642db29afc3a2 (wakeup_func)*
* @param wakeup_func - The callback function.
* @return  0 if successful, -1 otherwise. 

Example:

<pre><code class="lua">
su.init()
root = su.root_create()
timer = su.timer_create(root:task(), 200)
timer:run(function (su_timer_obj)
                    print("Timer fired!")
                    root:quit()
                end )

</code></pre>

*"set_for_ever":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#bedfb2d8572da135e8c6357f3f3a0fb6 (wakeup_func)*
* @param wakeup_func - The callback function.
* @return  0 if successful, -1 otherwise. 

Example:

<pre><code class="lua">
su.init()
root = su.root_create()
timer = su.timer_create(root:task(), 200)
timer:set_for_ever(function (su_timer_obj)
                                  print("Timer fired!")
                                  root:quit()
                              end)

</code></pre>

*"reset":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#e4a4b4fd968585a34aa4925004759881 ()*
* @return  0 if successful, -1 otherwise.


Example:

<pre><code class="lua">
su.init()
root = su.root_create()
timer = su.timer_create(root:task(), 200)
timer:reset()

</code></pre>

*"root":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#ec923ac3dd2720d604294fa8370ed5e0 ()*
* @return  The SURoot object owning the timer.

Example:

<pre><code class="lua">
su.init()
root = su.root_create()
timer = su.timer_create(root:task(), 200)
root2 = timer:root()

</code></pre>

*expire()*
*TODO*

*__gc()*

Called when lua collects the SUTimer object.

h1. Class SURoot

*register()*
*TODO*

*deregister()*
*TODO*

*unregister()*
*TODO*

*"run":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#01edbb4dee468eaf37ed367aa9f52e76 ()*

Example:

<pre><code class="lua">
su.init()
root = su.root_create()
timer = su.timer_create(root:task(), 200)
timer:set(function (t)
                  print("Timer fired!")
                  root:quit()
                end )
root:run()

</code></pre>

*"quit":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#fcbd6522a57210db684b2592e52ee9ab ()*

Example:

<pre><code class="lua">
su.init()
root = su.root_create()
timer = su.timer_create(root:task(), 200)
timer:set(function (t)
                  print("Timer fired!")
                  root:quit()
                end )
root:run()

</code></pre>


*"step":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#de5a78e4599465e91a0380e83b0a397d (tout)*
* @param tout - timeout in milliseconds
* @return  Milliseconds to the next invocation of timer 

*"get_max_defer":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#0e2fa776d326c7abd9569b01cf3a388b ()*
* @return Maximum defer time

*"set_max_defer":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#16cf0e457658f58b92a751fe87dfd639 (max_defer)*
* @param max_defer - maximum defer time in milliseconds
* @return 0 if successful, -1 otherwise.

*"task":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#2fe45fa59ae19b7fe379267dd09216c6 ()*
* @return A SUTask object.

Example:
<pre><code class="lua">
su.init()
root = su.root_create()
timer = su.timer_create(root:task(), 200)

</code></pre>

*__gc()*
Called when lua collects the SURoot object.

h1. Class SUTask

The SUTask class exists for internal use (like creating a timer). But there is no public methods implemented yet. The methods implementation are missing because we still do not use it.

*__gc()*
Called when lua collects the SUTask object.


h1. SUTimer Wakeup Callback

The signature of the functions passed as wakeup on su is like the "Sofia callback signature":http://sofia-sip.sourceforge.net/refdocs/su/su__wait_8h.html#9d72b50d3b4faa31657f257c75aaefa5 , the only diference is that there is no su_timer_arg_t and no su_root_magic_t. 

The function prototype is:

*function my_callback (task)*
* @param timer -  A SUTimer object.


Example:

<pre><code class="lua">
su.init()
root = su.root_create()
timer = su.timer_create(root:task(), 200)
timer:set(function (timer)
              print("Timer fired!")
              root:quit()
          end)

</code></pre>
                                      
Or you can pass an already defined function, instead of defining an anonimous function:

<pre><code class="lua">
su.init()
root = su.root_create()
timer = su.timer_create(root:task(), 200)

function wakeup_func(timer)
    print("Timer fired!")
    root:quit()
end

timer:set(wakeup_func)

</code></pre>
                                      
* *See also*: "su_test":http://github.com/ppizarro/luasofia/blob/master/test/su.lua
