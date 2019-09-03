cmake_minimum_required(VERSION 2.8)

project(cursera)
set (HEADERS "buse_decomposition.h" )

set (TEST test_${PROJECT_NAME})
set (TEST_SOURCES "test.cpp" "test_framework.h")

find_package(Boost 1.65.1 COMPONENTS system  unit_test_framework timer)
if (Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        add_executable( ${TEST} ${TEST_SOURCES})
        target_link_libraries(${TEST} ${Boost_LIBRARIES})
        enable_testing()
        add_test(${TEST} ${TEST})

        add_executable(${PROJECT_NAME} "main.cpp" ${HEADERS})
        target_link_libraries(${PROJECT_NAME}  ${Boost_LIBRARIES})
else()
        message(FATAL_ERROR "boost 1.65.1 not found")
endif()
