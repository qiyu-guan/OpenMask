#!/system/bin/sh
MODDIR=${0%/*}
mkdir -p /data/openmask/{cache,log,bin}
touch /data/openmask/auth.list
# 模块内root_enable就是开关，面具勾选生效
ln -sf $MODDIR/root_enable /data/openmask/magisk_root_switch
