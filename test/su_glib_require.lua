function print_table(table)
    if not table then print("nil table !!!"); return end
    for k, v in pairs(table) do
        print(k, v)
    end
end

local su = require "sofia.su"

print("\n<<<<<<<<<<<<<<< Required su >>>>>>>>>>>>>>>>\n")

print("\nPrinting local su: ")
print_table(su)

print("\nPrinting global sofia: ")
print_table(sofia)

print("\nPrinting global su: ")
print_table(sofia.su)


local glib = require "sofia.glib"

print("\n<<<<<<<<<<<<<<< Required glib >>>>>>>>>>>>>>>>\n")

print("\nPrinting local su: ")
print_table(su)

print("\nPrinting local glib: ")
print_table(glib)

print("\nPrinting global sofia: ")
print_table(sofia)

print("\nPrinting global su: ")
print_table(sofia.su)

print("\nPrinting global glib: ")
print_table(sofia.glib)

assert(glib == sofia.glib)
assert(su == sofia.su)
