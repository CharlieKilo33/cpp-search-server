cmake_minimum_required(VERSION 3.26)
project(Practicum)

set(CMAKE_CXX_STANDARD 17)

add_executable(main search-server/main.cpp
        search-server/document.cpp
        search-server/document.h
        search-server/paginator.h
        search-server/read_input_functions.cpp
        search-server/read_input_functions.h
        search-server/request_queue.cpp
        search-server/request_queue.h
        search-server/search_server.cpp
        search-server/search_server.h
        search-server/string_processing.cpp
        search-server/string_processing.h)
