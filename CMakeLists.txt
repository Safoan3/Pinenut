cmake_minimum_required(VERSION 3.23)
project(PineNut CXX)

if(MSVC)
    add_compile_options(/O2 /arch:AVX2)
else()
  add_compile_options(-O3 -march=native)
  #add_compile_options(-O0 -g)
endif()

# Uncomment ONLY if ../VizEngine defines the 'engine' target:
# add_subdirectory(../VizEngine ${CMAKE_BINARY_DIR}/VizEngine)

add_library(pinenut STATIC
    pinenut.cpp
    ../graphicsapi/graphicsapi.cpp
)

target_include_directories(pinenut PUBLIC
    ../graphicsapi/
    ./
)

if(WIN32)
    target_link_libraries(pinenut PUBLIC user32 gdi32)
elseif(APPLE)
    target_link_libraries(pinenut PUBLIC "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
else()
    target_link_libraries(pinenut PUBLIC  X11 Xrandr Xcursor m)
endif()
