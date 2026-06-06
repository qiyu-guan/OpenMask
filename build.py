import os
from builder.apk_builder import start_build

if __name__ == "__main__":
    print("==== OpenMask Build Engine V1.0 ====")
    # 注释掉不存在的build_helper、resource_build，规避文件找不到
    # os.system("./core/src/main/cpp/build_helper")
    start_build("release")
