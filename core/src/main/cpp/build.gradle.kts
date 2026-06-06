plugins {
    id("com.android.library")
}
android {
    namespace = "com.openmask.native"
    compileSdk = 34
    defaultConfig {
        minSdk = 24
        ndk { abiFilters.addAll(listOf("arm64-v8a")) }
        externalNativeBuild {
            cmake { cppFlags("-O2") }
        }
    }
    externalNativeBuild {
        cmake { path(file("CMakeLists.txt")) }
    }
}
