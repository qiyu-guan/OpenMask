#!/usr/bin/env python3
"""OpenMask 自研Python打包构建引擎｜替代Gradle"""
import sys
from builder.apk_builder import start_build
from builder.env_check import check_env

def main():
    print("==== OpenMask Build Engine V1.0 ====")
    check_env()
    build_type = sys.argv[1] if len(sys.argv)>1 else "release"
    start_build(build_type)

if __name__ == "__main__":
    main()
