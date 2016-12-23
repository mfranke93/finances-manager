find_package(Qt5Widgets)
include_directories(Qt5Widgets_INCLUDE_DIR)
find_package(Qt5Sql)
include_directories(Qt5Sql_INCLUDE_DIR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(${FINANCES_SOURCE_DIR}/src/tests)
link_directories(${FINANCES_BINARY_DIR}/src/tests)

add_executable(tests tests.cpp
        test_daterangefilter.cpp
        ../data/DateRangeFilter.cpp )

#target_link_libraries(cdemo m) #link the math library
target_link_libraries(tests ${Qt5Widgets_LIBRARIES})
target_link_libraries(tests ${Qt5Sql_LIBRARIES})
