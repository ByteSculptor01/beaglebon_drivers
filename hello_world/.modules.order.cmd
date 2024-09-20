cmd_/home/debian/hello_world/modules.order := {   echo /home/debian/hello_world/hello.ko; :; } | awk '!x[$$0]++' - > /home/debian/hello_world/modules.order
