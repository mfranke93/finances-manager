#FIND_PACKAGE(Boost 1.55 COMPONENTS program_options REQUIRED)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

find_package(Qt5Widgets)
include_directories(Qt5Widgets_INCLUDE_DIR)
find_package(Qt5Sql)
include_directories(Qt5Sql_INCLUDE_DIR)
find_package(Qt5Charts)
include_directories(Qt5Charts_INCLUDE_DIR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(${FINANCES_SOURCE_DIR}/src)
link_directories(${FINANCES_BINARY_DIR}/src)

add_executable(main main.cpp
    data/DateFactory.cpp
    data/DateFactory.h
    data/DateFilter.h
    data/DateRangeFilter.cpp
    data/DateRangeFilter.h
    data/DateToStringFactory.cpp
    data/DateToStringFactory.h
    data/DbHandler.cpp
    data/DbHandler.h
    data/RecipientObject.cpp
    data/RecipientObject.h
    data/RecipientObjectStore.cpp
    data/RecipientObjectStore.h
    data/RecurrentItemNameFactory.cpp
    data/RecurrentItemNameFactory.h
    data/RecurrentItemTemplate.cpp
    data/RecurrentItemTemplate.h
    data/ResourceHandler.cpp
    data/ResourceHandler.h
    data/SettingsManager.cpp
    data/SettingsManager.h
    ui/MainWindow.cpp
    ui/charts/ChartArea.cpp
    ui/charts/ChartArea.h
    ui/charts/ChartAreaFactory.h
    ui/common/DateFilterPane.cpp
    ui/common/DateFilterPane.h
    ui/common/SelectOrAddRecipientButton.cpp
    ui/common/SelectOrAddRecipientButton.h
    ui/delegates/PriceColumnDelegate.cpp
    ui/delegates/PriceColumnDelegate.h
    ui/delegates/RecipientAddressDelegate.cpp
    ui/delegates/RecipientAddressDelegate.h
    ui/delegates/RecipientNameDelegate.cpp
    ui/delegates/RecipientNameDelegate.h
    ui/dialogs/AddItemDialog.cpp
    ui/dialogs/AddItemDialog.h
    ui/dialogs/AddRecipientDialog.cpp
    ui/dialogs/AddRecipientDialog.h
    ui/dialogs/ItemTemplateTableModel.cpp
    ui/dialogs/ItemTemplateTableModel.h
    ui/dialogs/SearchRecipientDialog.cpp
    ui/dialogs/SearchRecipientDialog.h
    ui/dialogs/SelectRecurrentItemTemplateDialog.cpp
    ui/dialogs/SelectRecurrentItemTemplateDialog.h
    ui/dialogs/SettingsDialog.cpp
    ui/dialogs/SettingsDialog.h
    ui/dialogs/additem/AddItemBlock.cpp
    ui/dialogs/additem/AddItemBlock.h
    ui/dialogs/additem/AddItemRow.cpp
    ui/dialogs/additem/AddItemRow.h
    ui/menubar/MenuBar.cpp
    ui/menubar/MenuBar.h
    ui/table/ExpenditureView.cpp
    ui/table/ExpenditureView.h
    ui/tabs/TableTab.cpp
    ui/tabs/TableTab.h
    ui/tabs/QtChartTab.cpp
    ui/tabs/QtChartTab.h
    plotting/aggregation.cpp
    plotting/aggregation.h
    plotting/Filters.h
        )
target_link_libraries(main ${Qt5Widgets_LIBRARIES})
target_link_libraries(main ${Qt5Sql_LIBRARIES})
target_link_libraries(main ${Qt5Charts_LIBRARIES})


