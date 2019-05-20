from conans import ConanFile, CMake

class Roi3DF_Test_OsgConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    requires = "OSG/3.4.0@rtcv/extern"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir="%s/cmake" % self.source_folder)
        cmake.build()