#!/system/bin/sh
BD=/dev/block/bootdevice/by-name/boot
mkdir -p /mnt/omboot
/data/openmask/bin/mount_engine mount $BD /mnt/omboot ext4 0
dd if=$BD of=/data/openmask/boot_bak.img
