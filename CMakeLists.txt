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
add_executable(PrintRange PrintRange.cpp)
#add_executable(task2 2.cpp)
#add_executable(task3 3.cpp)
#add_executable(task4 4.cpp)
#add_executable(task5 5.cpp)
#add_executable(task6 6.cpp)
#add_executable(task7 7.cpp)
#add_executable(task8 8.cpp)
#add_executable(task9 9/1.cpp 9/log_duration.h)
#add_executable(task10 9/2.cpp 9/log_duration.h)
#add_executable(task11 9/3.cpp 9/log_duration.h)
#add_executable(task12 10/main.cpp 10/compressor.h 10/decompressor.h)
#add_executable(task13 13.cpp)
#add_executable(task14 14.cpp)
#add_executable(task15 15.cpp)
#add_executable(task16 16.cpp)
#add_executable(task17 17.cpp)
#add_executable(task18 18.cpp)
#add_executable(task19 19/main.cpp 19/octopus.h 19/ptrvector.h 19/scopedptr.h)
#add_executable(task20 20.cpp)
#add_executable(task21 21/main.cpp 21/my_assert.h)
add_executable(task22 22.cpp)
add_executable(task23 23/main.cpp 23/log_duration.h 23/my_assert.h 23/stack_vector.h)
add_executable(task24 24/main.cpp 24/array_ptr.h 24/simple_vector.h 24/tests.h)