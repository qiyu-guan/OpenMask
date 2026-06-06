#!/system/bin/sh
MODDIR=${0%/*}
mkdir -p /data/openmask/{cache,log,bin}
[ ! -f /data/openmask/auth.list ] && touch /data/openmask/auth.list
ln -sf $MODDIR/root_enable /data/openmask/magisk_root_switch
cp $MODDIR/bin/* /data/openmask/bin/* 2>/dev/null
chmod 755 /data/openmask/bin/*
