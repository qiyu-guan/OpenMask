import os
def check_env():
    need = ["aapt", "zipalign", "apksigner"]
    miss = [i for i in need if os.system(f"which {i} >/dev/null")]
    if miss:
        raise Exception(f"缺失编译工具: {miss}")
    print("✅ 编译环境校验通过")
