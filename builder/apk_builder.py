import os,shutil,subprocess
TMP = "build/tmp_apk"
OUT_APK = "dist/out.apk"
SO_SRC = "./core/src/main/cpp/libopenmask.so"
LIB_DIR = os.path.join(TMP, "lib/arm64-v8a")
RES_COMPILE = "build/res"
KS_FILE = "sign.jks"
KS_PWD = "123456"
# kotlin编译临时目录
KOTLIN_OUT = "build/kotlin_out"

def start_build(build_type):
    os.makedirs(TMP, exist_ok=True)
    os.makedirs(LIB_DIR, exist_ok=True)
    os.makedirs(RES_COMPILE, exist_ok=True)
    os.makedirs(KOTLIN_OUT, exist_ok=True)
    os.makedirs("dist", exist_ok=True)

    #1.资源编译生成arsc
    subprocess.run(["aapt2","compile","--dir","res","-o",f"{RES_COMPILE}/res.zip"])
    subprocess.run(["aapt2","link","--manifest","AndroidManifest.xml","-o",f"{TMP}/resources.arsc",f"{RES_COMPILE}/res.zip"])

    #2.编译Kotlin → classes.dex
    kt_src = "src/main/kotlin"
    if os.path.exists(kt_src):
        #编译kt成class
        subprocess.run(["kotlinc",kt_src,"-d",f"{KOTLIN_OUT}/classes.jar"])
        #jar转dex
        subprocess.run(["d8",f"{KOTLIN_OUT}/classes.jar","--output",TMP])

    #3.拷贝so
    if os.path.isfile(SO_SRC):
        shutil.copy(SO_SRC, LIB_DIR)

    #4.打包apk
    temp_apk = "build/temp.apk"
    subprocess.run(["zip","-r", temp_apk, f"{TMP}/."])

    if os.path.exists(temp_apk):
        shutil.move(temp_apk, OUT_APK)

    #5.签名
    if os.path.exists(KS_FILE):
        subprocess.run(["apksigner","sign","--ks",KS_FILE,"--ks-pass",f"pass:{KS_PWD}",OUT_APK])
        print("✅APK签名完成")

    print("✅成品:",OUT_APK)

if __name__ == "__main__":
    start_build("release")
