# This file is managed by Conan, contents will be overwritten.
# To keep your changes, remove these comment lines, but the plugin won't be able to modify your requirements

from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain, CMake

class ConanApplication(ConanFile):
    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        # tc.user_presets_path = False
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def requirements(self):
        requirements = self.conan_data.get('requirements', [])
        # self.requires("openssl/3.2.1", force=True)
        for requirement in requirements:
            self.requires(requirement)