QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mapcontrolpoint.cpp \
    mapiconbutton.cpp \
    mapitem.cpp \
    maplinekp.cpp \
    mapscene.cpp \
    mapview.cpp \
    poliline.cpp \
    stylehelper.cpp \
    widget.cpp

HEADERS += \
    defines.h \
    mapcontrolpoint.h \
    mapiconbutton.h \
    mapitem.h \
    maplinekp.h \
    mapscene.h \
    mapview.h \
    poliline.h \
    stylehelper.h \
    widget.h

FORMS += \
    mapiconbutton.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourses.qrc

DISTFILES += \
    resourses/cursors/bw_large_move_cursor.png \
    resourses/cursors/bw_large_point_cursor.png \
    resourses/cursors/bw_large_ruler_cursor.png \
    resourses/cursors/bw_move_cursor.png \
    resourses/cursors/bw_point_cursor.png \
    resourses/cursors/bw_ruler_cursor.png \
    resourses/cursors/cross-blue.png \
    resourses/cursors/cross-cursor-blue-2.png \
    resourses/cursors/cross-cursor-blue-3.png \
    resourses/cursors/cross-cursor-green-2.png \
    resourses/cursors/cross-cursor-green-3.png \
    resourses/cursors/cross-cursor-red-2.png \
    resourses/cursors/cross-cursor-red.png \
    resourses/cursors/cross-green.png \
    resourses/cursors/rb_large_move_cursor.png \
    resourses/cursors/rb_large_point_cursor.png \
    resourses/cursors/rb_large_ruler_cursor.png \
    resourses/cursors/rb_move_cursor.png \
    resourses/cursors/rb_point_cursor.png \
    resourses/cursors/rb_ruler_cursor.png \
    resourses/cursors/rw_large_move_cursor.png \
    resourses/cursors/rw_large_point_cursor.png \
    resourses/cursors/rw_large_ruler_cursor.png \
    resourses/cursors/rw_move_cursor.png \
    resourses/cursors/rw_point_cursor.png \
    resourses/cursors/rw_ruler_cursor.png
