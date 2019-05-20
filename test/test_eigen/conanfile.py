from conans import ConanFile, CMake

class Roi3DF_Test_EigenConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    requires = "eigen/3.3.4@conan/stable"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir="%s/cmake" % self.source_folder)
        cmake.build()