cmd_/home/debian/spi_comm/Module.symvers := sed 's/ko$$/o/' /home/debian/spi_comm/modules.order | scripts/mod/modpost -m    -o /home/debian/spi_comm/Module.symvers -e -i Module.symvers   -T -
