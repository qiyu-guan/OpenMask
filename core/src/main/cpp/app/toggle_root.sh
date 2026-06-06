#!/system/bin/sh
MODDIR=${0%/*}
if [ -f $MODDIR/root_enable ];then
    rm -f $MODDIR/root_enable
    echo "ROOT已关闭"
else
    touch $MODDIR/root_enable
    echo "ROOT已开启"
fi
