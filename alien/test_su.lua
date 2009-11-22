require "sofia"

function time_test()

  now = su_time_t:new()
  sofia.su_time(now)

  sthen = now

  s = alien.buffer(256)
  sofia.su_time_print(s, 256, now)
  --print(tostring(s))

end

sofia.su_init()

time_test()

root = sofia.su_root_create(nil)
if not root then
    print("ERROR: su_root_create")
    exit(1)
end

print("test_su: testing " .. sofia.su_root_name(root) .. " port implementation")

sofia.su_deinit()

