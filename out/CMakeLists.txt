project(ksrp)

add_library(ksrp INTERFACE)
add_subdirectory(src)

target_include_directories(ksrp INTERFACE "include/ksrp")
target_link_libraries(ksrp INTERFACE)