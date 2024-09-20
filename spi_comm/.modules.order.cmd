cmd_/home/debian/spi_comm/modules.order := {   echo /home/debian/spi_comm/spi_comm.ko; :; } | awk '!x[$$0]++' - > /home/debian/spi_comm/modules.order
