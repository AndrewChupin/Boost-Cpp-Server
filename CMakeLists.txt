cmake_minimum_required(VERSION 3.9)
project(Boosting)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.65.1 COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(Boosting
        connection.cpp
        connection.hpp

        connection_manager.cpp
        connection_manager.hpp

        header.hpp

        main.cpp

        mime_types.cpp
        mime_types.hpp

        reply.cpp
        reply.hpp

        request.hpp

        request_handler.cpp
        request_handler.hpp

        request_parser.cpp
        request_parser.hpp

        server.cpp
        server.hpp)

if(Boost_FOUND)
    target_link_libraries(Boosting ${Boost_LIBRARIES})
endif()
