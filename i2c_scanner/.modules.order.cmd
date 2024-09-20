cmd_/home/debian/i2c_scanner/modules.order := {   echo /home/debian/i2c_scanner/i2c_scanner.ko; :; } | awk '!x[$$0]++' - > /home/debian/i2c_scanner/modules.order
