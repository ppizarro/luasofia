-------------------------------------------------------------------------------
-- @author Paulo Pizarro  <paulo.pizarro@gmail.com>
-- @author Tiago Katcipis <tiagokatcipis@gmail.com>
--
-- This file is part of Luasofia.
--
-- Luasofia is free software: you can redistribute it and/or modify
-- it under the terms of the GNU Lesser General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.

-- Luasofia is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU Lesser General Public License for more details.
--
-- You should have received a copy of the GNU Lesser General Public License
-- along with Luasofia.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------------

local nta = require "luasofia.nta"
local su = require "luasofia.su"

su.init()
root = su.root_create()

local function nta_callback(nta, msg, sip)
    print("callback call !")
end

local nta_a = nta.agent_create(root, "sip:*:5060;transport=udp", nta_callback)
local nta_b = nta.agent_create(root, "sip:*:5061;transport=udp", nta_callback)

if(nta_a and nta_b) then
    print("NTA agent created successfully !!")
else
    print("ERROR CREATING NTA Agent !!")
end

--TODO, test more :-)
