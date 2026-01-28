cmake_minimum_required(VERSION 3.13)

project(fmgen LANGUAGES C CXX)

add_library(fmgen SHARED
  fmgen/fmtimer.cpp
  fmgen/opna.cpp
  fmgen/fmgen.cpp
  fmgen/opm.cpp
  fmgen/psg.cpp
  bridge/fmgen_c.cpp
)

target_include_directories(fmgen PUBLIC .)
target_compile_definitions(fmgen PRIVATE FMGEN_C_EXPORTS)
set_target_properties(fmgen PROPERTIES CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN YES)

if (MSVC)
  target_compile_definitions(fmgen PRIVATE _CRT_SECURE_NO_WARNINGS)
  target_compile_options(fmgen PRIVATE /utf-8)
endif()

# test executable to verify shared-library C API linkage
add_executable(call_test tests/calltest.c)
set_target_properties(call_test PROPERTIES OUTPUT_NAME "calltest")
target_link_libraries(call_test PRIVATE fmgen)
