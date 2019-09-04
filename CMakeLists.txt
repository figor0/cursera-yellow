cmake_minimum_required(VERSION 2.8)

project(cursera)
set (TEST test_${PROJECT_NAME})
set (TEST_SOURCES "test.cpp" "phone_number.cpp")
set (TEST_HEADERS "test_framework.h" "phone_number.h")

set( SOURCES main.cpp )
set( HEADERS )

find_package(Boost 1.65.1 COMPONENTS system  unit_test_framework timer)
if (Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        add_executable( ${TEST} ${TEST_SOURCES} ${TEST_HEADERS})
        target_link_libraries(${TEST} ${Boost_LIBRARIES})

        add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
        target_link_libraries(${PROJECT_NAME}  ${Boost_LIBRARIES})
else()
        message(FATAL_ERROR "boost 1.65.1 not found")
endif()
