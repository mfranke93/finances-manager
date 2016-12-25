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
        ui/MainWindow.cpp
        ui/table/ExpenditureView.cpp
        ui/table/ExpenditureView.h
        ui/dialogs/AddItemDialog.cpp
        ui/dialogs/AddItemDialog.h
        data/DbHandler.cpp
        data/DbHandler.h
        data/ResourceHandler.cpp
        data/ResourceHandler.h
        ui/dialogs/AddRecipientDialog.cpp
        ui/dialogs/AddRecipientDialog.h
        ui/dialogs/AddCategoryDialog.cpp
        ui/dialogs/AddCategoryDialog.h
        ui/tabs/TableTab.cpp
        ui/tabs/TableTab.h
        ui/tabs/PlotTab.cpp
        ui/tabs/PlotTab.h
        ui/plotting/PlotArea.cpp
        ui/plotting/PlotArea.h
        ui/plotting/graphics/PlotPoint.cpp
        ui/plotting/graphics/PlotPoint.h
        ui/plotting/graphics/Plottable.h
        ui/plotting/graphics/PlotLine.cpp
        ui/plotting/graphics/PlotLine.h
        ui/plotting/PlotBottomBar.cpp
        ui/plotting/PlotBottomBar.h
        ui/plotting/PlotLeftAxis.cpp
        ui/plotting/PlotLeftAxis.h
        ui/plotting/PlotGrid.cpp
        ui/plotting/PlotGrid.h
        ui/tabs/ChartTab.cpp
        ui/tabs/ChartTab.h
        ui/charts/BarGraph.cpp
        ui/charts/BarGraph.h
        ui/charts/GraphArea.cpp
        ui/charts/GraphArea.h
        ui/plotting/PlotCategoryFilter.cpp
        ui/plotting/PlotCategoryFilter.h
        ui/common/DateFilterPane.cpp
        ui/common/DateFilterPane.h
        data/DateFilter.h
        data/DateRangeFilter.cpp
        data/DateRangeFilter.h ui/plotting/graphics/PlotElement.h data/RangeConverter.cpp data/RangeConverter.h)
target_link_libraries(main ${Qt5Widgets_LIBRARIES})
target_link_libraries(main ${Qt5Sql_LIBRARIES})

