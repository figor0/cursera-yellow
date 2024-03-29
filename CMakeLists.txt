cmake_minimum_required(VERSION 2.8)

project(cursera)
set(CMAKE_CXX_STANDARD 17)
set( GENERAL_SOURCES
    "database.cpp"
    "date.cpp"
    "condition_parser.cpp"
    "node.cpp"
    "token.cpp"
    )
set( GENERAL_HEADERS
    "test_runner.h"
    "database.h"
    "date.h"
    "condition_parser.h"
    "node.h"
    "token.h"
    )

set (TEST test_${PROJECT_NAME})
set (TEST_SOURCES "test.cpp" ${GENERAL_SOURCES})
set (TEST_HEADERS  ${GENERAL_HEADERS})

set( SOURCES main.cpp ${GENERAL_SOURCES})
set( HEADERS ${GENERAL_HEADERS} )

find_package(Boost 1.65.1 COMPONENTS system  unit_test_framework timer)
if (Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        add_executable( ${TEST} ${TEST_SOURCES} ${TEST_HEADERS})
        target_link_libraries(${TEST} ${Boost_LIBRARIES})
        add_test(${TEST} ${TEST})

        add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
        target_link_libraries(${PROJECT_NAME}  ${Boost_LIBRARIES})
else()
        message(FATAL_ERROR "boost 1.65.1 not found")
endif()
