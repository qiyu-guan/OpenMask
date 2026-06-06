#!/system/bin/sh
#OpenMask Boot修复脚本
BOOT_DEV=/dev/block/bootdevice/by-name/boot
TMP_MOUNT=/mnt/om_boot
mkdir -p $TMP_MOUNT
#挂载boot分区修复
./core/src/main/cpp/mount_engine mount $BOOT_DEV $TMP_MOUNT ext4 0
echo "[BOOT] 分区挂载修复完成，备份镜像到/data/openmask/boot.bak"
dd if=$BOOT_DEV of=/data/openmask/boot.bak
