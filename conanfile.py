from conans import ConanFile, CMake

class Roi3DFConan(ConanFile):
    name = "Roi3DF"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports_sources = "cmake/*", "include/*", "src/*"
    options = { 
        "build_test_cuda": [True, False],
        "build_test_custom_no_operators": [True, False],
        "build_test_custom_with_operators": [True, False],
        "build_test_eigen": [True, False],
        "build_test_osg": [True, False],
        "build_test_qt": [True, False],
        "build_all_tests": [True, False]
    }
    default_options = {
        "build_test_cuda": False,
        "build_test_custom_no_operators": False,
        "build_test_custom_with_operators": False,
        "build_test_eigen": False,
        "build_test_osg": False,
        "build_test_qt": False,
        "build_all_tests": False
    }

    def requirements(self):
        if self.options.build_test_osg or self.options.build_all_tests:
            self.requires("openscenegraph/3.6.3@bincrafters/stable")
        if self.options.build_test_eigen or self.options.build_all_tests:
            self.requires("eigen/3.3.7@conan/stable")
            
    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_EXAMPLES"] = \
            self.options.build_test_cuda or \
            self.options.build_test_custom_no_operators or \
            self.options.build_test_custom_with_operators or \
            self.options.build_test_eigen or \
            self.options.build_test_osg or \
            self.options.build_test_qt or \
            self.options.build_all_tests
        cmake.definitions["BUILD_EXAMPLE_CUDA"] = self.options.build_test_cuda or self.options.build_all_tests
        cmake.definitions["BUILD_EXAMPLE_CUSTOM_NO_OPERATORS"] = self.options.build_test_custom_no_operators or self.options.build_all_tests
        cmake.definitions["BUILD_EXAMPLE_CUSTOM_WITH_OPERATORS"] = self.options.build_test_custom_with_operators or self.options.build_all_tests
        cmake.definitions["BUILD_EXAMPLE_EIGEN"] = self.options.build_test_eigen or self.options.build_all_tests
        cmake.definitions["BUILD_EXAMPLE_OSG"] = self.options.build_test_osg or self.options.build_all_tests
        cmake.definitions["BUILD_EXAMPLE_QT"] = self.options.build_test_qt or self.options.build_all_tests
        cmake.configure(source_dir="%s/cmake" % self.source_folder)
        return cmake
    
    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = [self.name]