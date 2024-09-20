cmd_/home/debian/uart_driver/modules.order := {   echo /home/debian/uart_driver/uart_driver.ko; :; } | awk '!x[$$0]++' - > /home/debian/uart_driver/modules.order
