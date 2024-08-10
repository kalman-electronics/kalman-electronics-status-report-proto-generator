project(ksrp)

file(GLOB SRC "src/*.c")

include_directories(include)
add_library(ksrp ${SRC})

target_include_directories(ksrp INTERFACE include)
target_link_libraries(ksrp INTERFACE)