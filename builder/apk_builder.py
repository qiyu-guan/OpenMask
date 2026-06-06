import os,shutil,subprocess
TMP = "build/tmp_apk"
OUT_APK = "dist/out.apk"
SO_SRC = "./core/src/main/cpp/libopenmask.so"
LIB_DIR = os.path.join(TMP, "lib/arm64-v8a")
RES_COMPILE = "build/res"

def start_build(build_type):
    os.makedirs(TMP, exist_ok=True)
    os.makedirs(LIB_DIR, exist_ok=True)
    os.makedirs(RES_COMPILE, exist_ok=True)

    # 1.aapt2编译资源生成有效resources.arsc
    subprocess.run([
        "aapt2", "compile", "--dir", "res", "-o", f"{RES_COMPILE}/res.zip"
    ])
    subprocess.run([
        "aapt2", "link", "--manifest", "AndroidManifest.xml",
        "-o", f"{TMP}/resources.arsc", f"{RES_COMPILE}/res.zip"
    ])

    # 2.复制so
    if os.path.exists(SO_SRC):
        shutil.copy(SO_SRC, LIB_DIR)

    # 3.后续补充：kotlinc编译kt→classes.dex，当前先占位
    # 4.打包zip为apk
    os.chdir(TMP)
    subprocess.run(["zip","-r","../temp.apk","./"])
    os.chdir("../")
    os.makedirs("dist", exist_ok=True)
    shutil.move("build/temp.apk", OUT_APK)

    # ========== 签名位置，后续替换你的jks信息 ==========
    # sign_cmd = ["apksigner","sign","--ks","sign.jks","--ks-pass","pass:密码",OUT_APK]
    # subprocess.run(sign_cmd)

    print(f"[SUCCESS] APK输出:{OUT_APK}")
