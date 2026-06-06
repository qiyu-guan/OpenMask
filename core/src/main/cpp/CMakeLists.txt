cmake_minimum_required(VERSION 3.22)
project(OpenMaskCore)

set(CMAKE_C_FLAGS "-Wall -O2 -DANDROID")

#编译动态库libopenmask.so
add_library(openmask SHARED
    cache_clean.c DeviceSpoof.c kern_auth.c kprobe_inject.c log_ctrl.c
    mount_engine.c selinux_ctrl.c virt_isolate.c
)

#编译su可执行
add_executable(om-su om-su.c)
target_link_libraries(om-su openmask)

#编译守护进程
add_executable(om_sud om_sud.c)
target_link_libraries(om_sud openmask)
