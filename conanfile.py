import os
from conans import ConanFile, CMake, tools


class MercuryConan(ConanFile):
    name = "Mercury"
    version = "1.0"
    license = "GPLv2"
    url = "https://github.com/KanoComputing/mercury"
    description = "A cross-platform base layer for configuring the system"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
    }
    default_options = {
        "shared": False
    }
    exports_sources = [
        "CMakeLists.txt",
        "src/*.cpp",
        "src/*.txt",
        "include/*.h",
        "include/*.in",
        "cmake/*",
    ]
    requires = (
        "gtest/1.8.1@bincrafters/stable",
        "parson/0.1.0@bincrafters/stable",
        "Poco/1.9.2@pocoproject/stable",
        "yaml-cpp/0.6.3",
    )
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure(
            source_folder=".",
            build_folder=".",
            defs={
                "BUILD_PYTHON": "OFF",
                "BUILD_PYTHON2": "OFF",
                "BUILD_CSHARP": "OFF"
            }
        )
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include")

        if self.options.shared:
            self.copy("*.so", dst="lib", keep_path=False)
            self.copy("*.dylib", dst="lib", keep_path=False)
            self.copy("*.dll", dst="bin", keep_path=False)
            self.copy("*mercury.lib", dst="lib", keep_path=False)
        else:
            self.copy("*.a", dst="lib", keep_path=False)
            self.copy("*static.lib", dst="lib", keep_path=False)

    def package_info(self):
        # Only on Windows, for now, the static library is called mercury_static.lib
        if not self.options.shared and os.name == 'nt':
            self.cpp_info.libs = ["mercury_static"]
        else:
            self.cpp_info.libs = ["mercury"]
