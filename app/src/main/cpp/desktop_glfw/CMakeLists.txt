cmake_minimum_required(VERSION 2.8)


project(HatchBaby)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -gdwarf-2")

add_definitions(-DDESKTOP_BUILD)

add_executable(HatchBaby
  "${CMAKE_CURRENT_SOURCE_DIR}/../app.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../effect.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../hearteffect.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../heightmap.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../shader.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../texture.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../watereffect.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../watershader.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../bgshader.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../soundwave.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../smokeeffect.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/../framebuffer.cpp"
  bitmap.c
  main.cpp
)

target_include_directories(HatchBaby PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(HatchBaby

  GL GLU glfw3 X11 Xxf86vm Xrandr pthread Xi Xinerama Xcursor pthread dl
)