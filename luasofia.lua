
local core = require "luasofia.core"

local function struct_new(s_proto, ptr)
  local buf = core.buffer(ptr or s_proto.size)
  local function struct_get(_, key)
    if s_proto.offsets[key] then
      return buf:get(s_proto.offsets[key] + 1, s_proto.types[key])
    else 
      error("field " .. key .. " does not exist")
    end
  end
  local function struct_set(_, key, val)
    if s_proto.offsets[key] then
      buf:set(s_proto.offsets[key] + 1, val, s_proto.types[key])
    else
      error("field " .. key .. " does not exist")
    end
  end
  return setmetatable({}, { __index = struct_get, __newindex = struct_set,
                            __call = function () return buf end })
end

function defstruct(t)
  local off = 0
  local names, offsets, types = {}, {}, {}
  for _, field in ipairs(t) do
    local name, type = field[1], field[2]
    names[#names + 1] = name
    off = math.ceil(off / core.align(type)) * core.align(type)
    offsets[name] = off
    types[name] = type
    off = off + core.sizeof(type)
  end
  return { names = names, offsets = offsets, types = types, size = off, new = struct_new }
end

su = require "luasofia.su"
nua = require "luasofia.nua"
sip = require "luasofia.sip"
soa = require "luasofia.soa"

url = defstruct{
    { "pad",      "short"  },
    { "type",     "char"   },
    { "root",     "char"   },
    { "scheme",   "string" },
    { "user",     "string" },
    { "password", "string" },
    { "host",     "string" },
    { "port",     "string" },
    { "path",     "string" },
    { "params",   "string" },
    { "headers",  "string" },
    { "fragment", "string" }
}

