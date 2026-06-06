import os,shutil
TMP = "build/tmp_apk"
OUT_APK = "dist/out.apk"
SO_SRC = "./core/src/main/cpp/libopenmask.so"
LIB_DIR = os.path.join(TMP, "lib/arm64-v8a")

def start_build(build_type):
    os.makedirs(TMP, exist_ok=True)
    os.makedirs(LIB_DIR, exist_ok=True)

    # 1.生成空arsc
    arsc_path = os.path.join(TMP, "resources.arsc")
    open(arsc_path, "w").close()

    # 2.拷贝编译产出so进apk目录
    if os.path.exists(SO_SRC):
        shutil.copy(SO_SRC, LIB_DIR)

    os.makedirs("dist", exist_ok=True)
    shutil.make_archive(OUT_APK.replace(".apk",""), 'zip', TMP)
    os.rename(OUT_APK.replace(".apk",".zip"), OUT_APK)

    print(f"[SUCCESS] APK输出路径:{OUT_APK}")
