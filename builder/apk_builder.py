import os,shutil,subprocess
TMP = "build/tmp_apk"
OUT_APK = "dist/out.apk"
SO_SRC = "./core/src/main/cpp/libopenmask.so"
LIB_DIR = os.path.join(TMP, "lib/arm64-v8a")
RES_COMPILE = "build/res"
KS_FILE = "sign.jks"
KS_PWD = "123456"
KEY_PWD = "7891"

def start_build(build_type):
    os.makedirs(TMP, exist_ok=True)
    os.makedirs(LIB_DIR, exist_ok=True)
    os.makedirs(RES_COMPILE, exist_ok=True)
    os.makedirs("dist", exist_ok=True)

    # aapt编译资源
    subprocess.run(["aapt2","compile","--dir","res","-o",f"{RES_COMPILE}/res.zip"])
    subprocess.run(["aapt2","link","--manifest","AndroidManifest.xml","-o",f"{TMP}/resources.arsc",f"{RES_COMPILE}/res.zip"])

    # 拷贝so
    if os.path.exists(SO_SRC):
        shutil.copy(SO_SRC, LIB_DIR)

    temp_apk = "build/temp.apk"
    subprocess.run(["zip","-r", temp_apk, f"{TMP}/."])
    if os.path.exists(temp_apk):
        shutil.move(temp_apk, OUT_APK)

    # 完整签名
    if os.path.exists(KS_FILE):
        subprocess.run([
            "apksigner","sign",
            "--ks",KS_FILE,
            "--ks-pass",f"pass:{KS_PWD}",
            "--key-pass",f"pass:{KEY_PWD}",
            "--v1-enabled","true","--v2-enabled","true",
            OUT_APK
        ])
    print("打包完成：",OUT_APK)

if __name__ == "__main__":
    start_build("release")
