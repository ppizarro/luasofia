
local su = require "sofia.su"
local glib = require "sofia.glib"

su.init()

local root = glib.root_create()

local source = root:gsource()

local task = root:task()

print(task)
print(source)
print(root)

