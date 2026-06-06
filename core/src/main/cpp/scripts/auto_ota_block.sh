#!/system/bin/sh
#拦截系统OTA更新，冻结更新分区
setprop persist.ota.disable 1
mount --bind /dev/null /dev/block/by-name/ota
echo "[OTA] OTA升级拦截已启用"
