project(wpp)

set(CMAKE_CXX_STANDARD 17)
add_library(wpp web++.cpp web++.hpp server.cpp server.hpp route.hpp definitions.hpp request.hpp response.hpp list_dir.cpp list_dir.hpp exception.hpp)