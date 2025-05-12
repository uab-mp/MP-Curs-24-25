# Compilación semiautomática para Linux
#
# Miguel Hernández-Cabronero <miguel.hernandez@uab.cat>, 2025/05/12
cmake_minimum_required(VERSION 3.10)

project(codi_lliurament_final)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

add_executable(codi_lliurament_final)

# Compile with verbose output, add debug information and don't optimize anything for easier instruction stepping
target_compile_options(codi_lliurament_final PRIVATE -Wextra -g -O0)

# Include from anywhere
include_directories("0. C++ Code/Graphic Lib")
include_directories("0. C++ Code/Graphic Lib/NFont")
include_directories("0. C++ Code/Logic Game")
include_directories("2. Platforms")
include_directories("2. Platforms/0. Windows Desktop")
include_directories("2. Platforms/0. Windows Desktop/extlibs")
include_directories("2. Platforms/0. Windows Desktop/extlibs/libpng")
include_directories("2. Platforms/0. Windows Desktop/extlibs/SDL")
include_directories("2. Platforms/0. Windows Desktop/extlibs/SDL/include")
include_directories("2. Platforms/0. Windows Desktop/extlibs/SDL_ttf")
include_directories("2. Platforms/0. Windows Desktop/extlibs/SDL_ttf/include")


# Automatically add everything under the Logic Game folder
file(GLOB_RECURSE files
        "0. C++ Code/*.h"
        "0. C++ Code/*.cpp"
        "0. C++ Code/*.hpp"
        "2. Platforms/*.h"
        "2. Platforms/*.cpp"
        "2. Platforms/*.hpp"
)
target_sources(codi_lliurament_final PRIVATE ${files})

target_link_libraries(codi_lliurament_final PRIVATE
        SDL2_ttf
        SDL2_image
        SDL2_mixer
        SDL2_gfx
        SDL2_test
        SDL2main
        SDL2
        png
        png16
)