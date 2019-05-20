from conans import ConanFile, CMake

class Roi3DF_Test_CustomConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir="%s/cmake" % self.source_folder)
        cmake.build()