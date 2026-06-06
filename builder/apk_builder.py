import os
import shutil
from builder.build_config import *
from builder.res_compile import compile_res

def start_build(bt):
    tmp = "build/tmp_apk"
    os.makedirs(tmp,exist_ok=True)
    compile_res(RES_ROOT,tmp)
    # 编译dex、打包、对齐、签名省略自研逻辑
    shutil.copy(f"{tmp}/resources.arsc",OUT_APK)
    print(f"✅ APK编译完成 -> {OUT_APK}")
