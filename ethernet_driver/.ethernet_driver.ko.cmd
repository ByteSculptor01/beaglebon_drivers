cmd_/home/debian/ethernet_driver/ethernet_driver.ko := ld -r -EL -z noexecstack --build-id=sha1  -T scripts/module.lds -o /home/debian/ethernet_driver/ethernet_driver.ko /home/debian/ethernet_driver/ethernet_driver.o /home/debian/ethernet_driver/ethernet_driver.mod.o;  true
