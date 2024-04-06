mkdir build
mkdir run
conan build . -of build -s build_type=Debug --build=missing
cd build
cmake --build . --target copy_executable