get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(ProjectId "${ProjectId}")
project( ${ProjectId} )
message( STATUS "-- " ${ProjectId} )

file(GLOB_RECURSE header_files "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
#file(GLOB_RECURSE source_files "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(PACK_LIB "${ProjectId}_lib")
add_library(${PACK_LIB} INTERFACE)
set_target_properties(${PACK_LIB} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PACK_LIB} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(test_cases "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

target_link_libraries(test_cases ${PACK_LIB} gtest gtest_main)