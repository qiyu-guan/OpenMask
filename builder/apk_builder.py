import os,shutil
TMP = "build/tmp_apk"
OUT_APK = "dist/out.apk"

def start_build(build_type):
    # 调用C程序生成resources.arsc
    os.system("./core/src/main/cpp/resource_build AndroidManifest.xml res/")
    src_arsc = f"{TMP}/resources.arsc"
    if not os.path.exists(src_arsc):
        raise Exception("资源编译失败：未生成resources.arsc")
    os.makedirs("dist",exist_ok=True)
    shutil.copy(src_arsc,OUT_APK)
    os.system(f"./core/src/main/cpp/apk_packer {OUT_APK}")
    print(f"[SUCCESS] APK输出路径:{OUT_APK}")
