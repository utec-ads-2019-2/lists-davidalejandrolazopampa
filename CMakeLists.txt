cmake_minimum_required(VERSION 3.14)
project(lists_davidalejandrolazopampa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(iterators)
include_directories(mock)
include_directories(test)

add_executable(lists_davidalejandrolazopampa
        iterators/bidirectional_iterator.h
        iterators/forward_iterator.h
        mock/mocker.cpp
        mock/mocker.h
        test/tester.cpp
        test/tester.h
        circular.h
        forward.h
        iterator.h
        linked.h
        list.h
        main.cpp
        node.h)
