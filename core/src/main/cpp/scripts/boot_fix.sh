#!/system/bin/sh
BOOT=/dev/block/bootdevice/by-name/boot
TMP=/mnt/omboot
mkdir -p $TMP
/data/openmask/bin/mount_engine mount $BOOT $TMP ext4 0
dd if=$BOOT of=/data/openmask/boot_back.img
echo "Boot备份修复完成"
