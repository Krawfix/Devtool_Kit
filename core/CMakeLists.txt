cmake_minimum_required(VERSION 3.15)
project(MyGlobalEngine)

# 1. Create the static library
add_library(MyGlobalLib STATIC 
    src/global_core.cpp
)

# 2. Expose its header file directory to consumers automatically
target_include_directories(MyGlobalLib PUBLIC include)

# 3. Create other modules (e.g., components, executables)
add_library(NetworkModule STATIC src/network.cpp)
add_executable(GameApp src/main.cpp)

# 4. Link against your modules. 
# Because of CMake target propagation, linking MyGlobalLib here 
# satisfies all downstream module requirements.
target_link_libraries(NetworkModule PRIVATE MyGlobalLib)
target_link_libraries(GameApp PRIVATE NetworkModule MyGlobalLib)
