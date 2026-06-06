#!/system/bin/sh
setprop persist.ota.disable=1
mount --bind /dev/null /dev/block/by-name/ota
