
local glib = require "sofia_glib"
local su = require "sofia.su"

su.init()

local root = glib.root_create()
local root2 = su.root_create()

local source = root:gsource()
local source2 = root2:gsource()

local task = root:task()
local task2 = root2:task()

print(task)
print(task2)
print(source)
print(source2)
print(root)
print(root2)

