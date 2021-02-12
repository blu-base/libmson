add_subdirectory(qhexview)
target_compile_definitions(qhexview-lib PRIVATE QHEXVIEW_LIBRARY)


set(ONHEXVIEWER_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        documentitem.cpp
        documentitem.h
        documentmodel.h
        documentmodel.cpp
        documentmodelfactory.h
        documentmodelfactory.cpp
)

add_executable(onhexviewer
    ${ONHEXVIEWER_SOURCES}
)

target_link_libraries(onhexviewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets qhexview-lib  libmson libmson_priv)

install(TARGETS onhexviewer DESTINATION ${CMAKE_INSTALL_BINDIR})
