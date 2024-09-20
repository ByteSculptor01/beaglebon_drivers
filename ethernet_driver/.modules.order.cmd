cmd_/home/debian/ethernet_driver/modules.order := {   echo /home/debian/ethernet_driver/ethernet_driver.ko; :; } | awk '!x[$$0]++' - > /home/debian/ethernet_driver/modules.order
