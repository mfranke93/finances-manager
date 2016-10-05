#FIND_PACKAGE(Boost 1.55 COMPONENTS program_options REQUIRED)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

find_package(Qt5Widgets)
include_directories(Qt5Widgets_INCLUDE_DIR)
find_package(Qt5Sql)
include_directories(Qt5Sql_INCLUDE_DIR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(${FINANCES_SOURCE_DIR}/src)
link_directories(${FINANCES_BINARY_DIR}/src)

add_executable(main main.cpp
        ui/main_window.cpp ui/ExpenditureView.cpp ui/ExpenditureView.h ui/AddItemDialog.cpp ui/AddItemDialog.h data/DbHandler.cpp data/DbHandler.h)
target_link_libraries(main ${Qt5Widgets_LIBRARIES})
target_link_libraries(main ${Qt5Sql_LIBRARIES})

