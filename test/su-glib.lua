
glib = require "luasofia-glib"
su = require "luasofia.su"

root = glib.root_create()
root2 = su.root_create()

source = root:gsource()
source2 = root2:gsource()

task = root:task()
task2 = root2:task()

print(task)
print(task2)
print(source)
print(source2)
print(root)
print(root2)

