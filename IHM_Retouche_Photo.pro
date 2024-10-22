QT       += core gui quickcontrols2

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    colorpickerwidget.cpp \
    dialog/rescaledialog.cpp \
    dialog/resizedialog.cpp \
    dialog/sizedialog.cpp \
    main.cpp \
    mainwindow.cpp \
    tools/editable.cpp \
    tools/editable/bucket.cpp \
    tools/editable/pixelEraiser.cpp \
    tools/editable/pixelpainter.cpp \
    tools/hand.cpp \
    tools/picker.cpp \
    tools/selectionable/color.cpp \
    tools/selectionable/ellipse.cpp \
    tools/selectionable/polygone.cpp \
    tools/selectionable/quad.cpp \
    tools/selectionable/rectangle.cpp \
    tools/selectionable/rectangleTriangle.cpp \
    tools/selectionable/triangle.cpp \
    tools/selectionnable.cpp \
    tools/tool.cpp \
    ui/effect/blackandwhite.cpp \
    ui/effect/contrast.cpp \
    ui/effect/effect.cpp \
    ui/files/treefileselector.cpp \
    ui/menu/displaymenulambda.cpp \
    ui/menu/filemenulambda.cpp \
    ui/menu/imagemenulambda.cpp \
    ui/menu/menubarmanager.cpp \
    ui/menu/selectionmenulambda.cpp \
    ui/toolbox/toolRegister.cpp \
    ui/view/imagearea.cpp \
    ui/view/multyimagemodifier.cpp \
    ui/view/repercussion/average.cpp \
    ui/view/repercussion/clamp.cpp \
    ui/view/repercussion/ignore.cpp \
    ui/view/selection.cpp \
    ui/view/viewmanager.cpp

HEADERS += \
    colorpickerwidget.h \
    dialog/rescaledialog.h \
    dialog/resizedialog.h \
    dialog/sizedialog.h \
    mainwindow.h \
    tools/editable.h \
    tools/editable/bucket.h \
    tools/editable/pixelEraiser.h \
    tools/editable/pixelpainter.h \
    tools/hand.h \
    tools/picker.h \
    tools/selectionable/color.h \
    tools/selectionable/ellipse.h \
    tools/selectionable/polygone.h \
    tools/selectionable/quad.h \
    tools/selectionable/rectangle.h \
    tools/selectionable/rectangleTriangle.h \
    tools/selectionable/triangle.h \
    tools/selectionnable.h \
    tools/tool.h \
    ui/effect/blackandwhite.h \
    ui/effect/contrast.h \
    ui/effect/effect.h \
    ui/files/fileselector.h \
    ui/files/treefileselector.h \
    ui/menu/displaymenulambda.h \
    ui/menu/filemenulambda.h \
    ui/menu/imagemenulambda.h \
    ui/menu/menubarmanager.h \
    ui/menu/selectionmenulambda.h \
    ui/toolbox/toolRegister.h \
    ui/view/imagearea.h \
    ui/view/multyimagemodifier.h \
    ui/view/repercussion/average.h \
    ui/view/repercussion/clamp.h \
    ui/view/repercussion/ignore.h \
    ui/view/repercussion/repercussion.h \
    ui/view/selection.h \
    ui/view/viewmanager.h

FORMS += \
    dialog/rescaledialog.ui \
    dialog/resizedialog.ui \
    dialog/sizedialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressource.qrc

DISTFILES += \
    ui/Nouveau document texte.txt \
    ui/Nouveau document texte.txt
