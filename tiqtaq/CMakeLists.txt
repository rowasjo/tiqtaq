
qt_add_executable(row_tiqtaq
    #mainwindow.ui
    #mainwindow.cpp
    main.cpp
)

target_link_libraries(row_tiqtaq PRIVATE row_tiqtaqcore::tiqtaq Qt6::Widgets)

set_target_properties(row_tiqtaq PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
