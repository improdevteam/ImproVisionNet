QT -= qt core gui

TARGET = impro_core

TEMPLATE = lib

VERSION = "1.0.0"

DESTDIR += $(IMPRO_HOME)/build/lib

DLLDESTDIR += $(IMPRO_HOME)/build/bin

DEFINES += IMPROAPI_EXPORTS

INCLUDEPATH += \
    $$PWD/include \
    $(OPENCV_HOME)/include \
    $(BOOST_HOME)

HEADERS += \
    include/impro/defines.hpp \
    include/impro/data.hpp \
    include/impro/application.hpp \
    include/impro/process.hpp \
    include/impro/processcreator.hpp \
    include/impro/private/applicationimpl.hpp \
    include/impro/data/image.hpp \
    include/impro/data/arraypoint2d.hpp \
    include/impro/data/arraypoint3d.hpp \
    include/impro/space.hpp \
    include/impro/node.hpp \
    include/impro/channel.hpp \
    include/impro/spacebuilder.hpp \
    include/impro/errors.hpp \
    include/impro/datatype.hpp \
    include/impro/channelobserver.hpp \
    include/impro/process/cameracontroller.hpp \
    include/impro/interface.hpp \
    include/impro/interfacecreator.hpp \
    include/impro/interface/camera.hpp \
    include/impro/data/imageacc.hpp \
    include/impro/data/imagepts.hpp \
    include/impro/data/imageptsbool.hpp \
    include/impro/data/imageaccpts.hpp \
    include/impro/data/arrayvec3d.hpp \
    include/impro/data/arrayvec3f.hpp \
    include/impro/data/arraypoint2f.hpp \
    include/impro/interface/triangulation.hpp \
    include/impro/interface/k201711.hpp \
    include/impro/interface/strainfield.hpp \
    include/impro/interface/field.hpp

SOURCES += \
    src/data/image.cpp \
    src/data/arraypoint2d.cpp \
    src/data/arraypoint3d.cpp \
    src/channel.cpp \
    src/spacebuilder.cpp \
    src/applicationimpl.cpp \
    src/space.cpp \
    src/node.cpp \
    src/datatype.cpp \
    src/interfacecreator.cpp \
    src/data/arraypoint2f.cpp \
    src/data/arrayvec3d.cpp \
    src/data/arrayvec3f.cpp \
    src/data/imageacc.cpp \
    src/data/imagepts.cpp \
    src/data/imageaccpts.cpp

win32 {
    # boost library
    LIBS += -L$(BOOST_HOME)/stage/lib \
            -llibboost_system-vc141-mt-x64-1_68 \
            -llibboost_filesystem-vc141-mt-x64-1_68 \
            -llibboost_thread-vc141-mt-x64-1_68

    # opencv library
    LIBS += -L$(OPENCV_HOME)/x64/vc15/lib \
            -lopencv_world343

}

unix {
    # boost library
    LIBS += -L$(BOOST_HOME)/stage/lib \
            -lboost_system \
            -lboost_filesystem \
            -lboost_thread

    # opencv library
    LIBS += -L$(OPENCV_HOME)/lib \
            -lopencv_core \
            -lopencv_imgcodecs \
            -lopencv_highgui \
            -lopencv_imgproc

    QMAKE_CXXFLAGS += -fPIC
    QMAKE_LFLAGS += -Wl,-rpath,/home/linaro/Projects/impro/Desktop/build/lib:/home/linaro/Libraries/boost_1_68_0/stage/lib:/home/linaro/Libraries/opencv-3.4.3/release/lib://home/linaro/Libraries/core-alljoyn/build/linux/arm/release/dist/cpp/lib

}
