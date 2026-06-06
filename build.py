import os
from builder.apk_builder import start_build

if __name__ == "__main__":
    print("==== OpenMask Build Engine V1.0 ====")
    os.system("./core/src/main/cpp/build_helper")
    start_build("release")
