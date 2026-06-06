"""资源编译，自动生成资源索引"""
import os
def compile_res(res_dir, tmp_build):
    os.system(f"aapt package -f -M {tmp_build}/AndroidManifest.xml -S {res_dir} -I android.jar -F {tmp_build}/resources.arsc")
    print("✅ 资源编译完成")
