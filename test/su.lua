--[[

@author Paulo Pizarro  <paulo.pizarro@gmail.com>
@author Tiago Katcipis <tiagokatcipis@gmail.com>

This file is part of Luasofia.

Luasofia is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Luasofia is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Luasofia.  If not, see <http://www.gnu.org/licenses/>.
]]--

local su = require "sofia.su"

su.init()

local root = su.root_create()

local timer1 = su.timer_create(root:task(), 1000)

local timer2 = su.timer_create(root:task(), 100)

timer1:set(function(t)
               print("Timer1 fired!")
               timer2:reset()
               timer2 = nil
               collectgarbage("collect")
               print("Timer1 set again!")
               t:set(function(t)
                         print("Timer1 fired again!")
                         root:quit()
                     end)
           end)

timer2:set_for_ever(function(t)
                        print("Timer2 fired!")
                    end)

timer1 = nil
collectgarbage("collect")

root:run()

su.deinit()

