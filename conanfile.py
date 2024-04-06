from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, CMakeDeps, cmake_layout
import os
from conan.tools.files import copy


class CoolProject(ConanFile):
    name = "cool project"
    version = "1.0"
    description = """windows service, 
                   to regularly fetch currency rate form NBU bank website 
                   and store them in xml, json , csv format"""
    author = "Bondaruk R.I. (26bondaruk@gmail.com)"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    
    def requirements(self):
        self.requires("libcurl/8.6.0", transitive_headers=True, transitive_libs=True)
        self.requires("nlohmann_json/3.11.2", transitive_headers=True, transitive_libs=True)
        self.requires("pugixml/1.14", transitive_headers=True, transitive_libs=True)

    def Layout(self):
        cmake_layout(self, src_folder="src")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package_info(self):
        self.cpp_info.libs = ["cool_project"]
    