project(wpp)

set(CMAKE_CXX_STANDARD 17)
add_library(wpp src/web++.cpp src/web++.hpp src/server.cpp src/server.hpp src/route.hpp src/definitions.hpp src/request.hpp src/response.hpp src/list_dir.cpp src/list_dir.hpp src/exception.hpp src/method.cpp src/response.cpp)


add_executable(wpp_demo demo.cpp)
target_link_libraries(wpp_demo PUBLIC wpp)