HEADERS       = glwidget.h \
                mainwindow.h
SOURCES       = glwidget.cpp \
                main.cpp \
                mainwindow.cpp
QT           += opengl

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/opengl/qcnlive
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS qcnlive.pro
#sources.path = $$[QT_INSTALL_EXAMPLES]/opengl/qcnlive
INSTALLS += target sources

#symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)