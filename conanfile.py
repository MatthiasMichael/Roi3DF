from conans import ConanFile, CMake

class Roi3DFConan(ConanFile):
    name = "Roi3DF"
    version = "HEAD"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports_sources = "cmake/*", "include/*", "src/*"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir="%s/cmake" % self.source_folder)
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = [self.name]