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
    data/DateFilter.h
    data/DateRangeFilter.cpp
    data/DateRangeFilter.h
    data/DbHandler.cpp
    data/DbHandler.h
    data/RangeConverter.cpp
    data/RangeConverter.h
    data/ResourceHandler.cpp
    data/ResourceHandler.h
    ui/MainWindow.cpp
    ui/charts/BarGraph.cpp
    ui/charts/BarGraph.h
    ui/charts/GraphArea.cpp
    ui/charts/GraphArea.h
    ui/common/DateFilterPane.cpp
    ui/common/DateFilterPane.h
    ui/dialogs/AddCategoryDialog.cpp
    ui/dialogs/AddCategoryDialog.h
    ui/dialogs/AddItemDialog.cpp
    ui/dialogs/AddItemDialog.h
    ui/dialogs/AddRecipientDialog.cpp
    ui/dialogs/AddRecipientDialog.h
    ui/menubar/MenuBar.cpp 
    ui/menubar/MenuBar.h
    ui/plotting/PlotArea.cpp
    ui/plotting/PlotArea.h
    ui/plotting/PlotBottomBar.cpp
    ui/plotting/PlotBottomBar.h
    ui/plotting/PlotCategoryFilter.cpp
    ui/plotting/PlotCategoryFilter.h
    ui/plotting/PlotGrid.cpp
    ui/plotting/PlotGrid.h
    ui/plotting/PlotLeftAxis.cpp
    ui/plotting/PlotLeftAxis.h
    ui/plotting/graphics/CumulativePlotLine.cpp
    ui/plotting/graphics/CumulativePlotLine.h
    ui/plotting/graphics/DailyChangesPlotLine.cpp
    ui/plotting/graphics/DailyChangesPlotLine.h
    ui/plotting/graphics/PlotBar.cpp
    ui/plotting/graphics/PlotBar.h
    ui/plotting/graphics/PlotElement.h
    ui/plotting/graphics/PlotLineFactory.cpp
    ui/plotting/graphics/PlotLineFactory.h
    ui/plotting/graphics/PlotPoint.cpp
    ui/plotting/graphics/PlotPoint.h
    ui/plotting/graphics/Plottable.h
    ui/table/ExpenditureView.cpp
    ui/table/ExpenditureView.h
    ui/table/PriceColumnDelegate.cpp 
    ui/table/PriceColumnDelegate.h
    ui/tabs/ChartTab.cpp
    ui/tabs/ChartTab.h
    ui/tabs/PlotTab.cpp
    ui/tabs/PlotTab.h
    ui/tabs/TableTab.cpp
    ui/tabs/TableTab.h
    version.h ui/dialogs/SearchRecipientDialog.cpp ui/dialogs/SearchRecipientDialog.h data/RecipientObjectStore.cpp data/RecipientObjectStore.h data/RecipientObject.cpp data/RecipientObject.h)
target_link_libraries(main ${Qt5Widgets_LIBRARIES})
target_link_libraries(main ${Qt5Sql_LIBRARIES})

