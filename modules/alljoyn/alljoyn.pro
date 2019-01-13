QT       -= qt core gui

TARGET = impro_alljoyn

TEMPLATE = lib

VERSION = "1.0.0"

DESTDIR += $(IMPRO_HOME)/build/lib

DLLDESTDIR += $(IMPRO_HOME)/build/bin

DEFINES += IMPROAPI_EXPORTS

INCLUDEPATH += \
    $$PWD/include \
    $(IMPRO_HOME)/build/inc \
    $(OPENCV_HOME)/include \
    $(BOOST_HOME) \
    $(AJ_DIST)/cpp/inc

HEADERS += \
    include/impro/alljoynspacebuilder.hpp \
    include/impro/process/alljoyncameracontrollercreator.hpp \
    include/impro/private/alljoynutil.hpp \
    include/impro/private/alljoynspace.hpp \
    include/impro/private/alljoynlocalnode.hpp \
    include/impro/private/alljoynremotenode.hpp \
    include/impro/private/alljoynremoteobject.hpp \
    include/impro/private/alljoynremotelistener.hpp \
    include/impro/private/alljoynlocallistener.hpp \
    include/impro/private/alljoynlocalobject.hpp \
    include/impro/private/alljoynremotechannel.hpp \
    include/impro/private/alljoynlocalchannel.hpp \
    include/impro/private/process/alljoyncameracontroller.hpp \
    include/impro/private/interface/alljoyncamera.hpp \
    include/impro/interface/alljoyncameracreator.hpp \
    include/impro/private/interface/alljoyntracking.hpp \
    include/impro/interface/alljoyntrackingcreator.hpp \
    include/impro/interface/alljoyntriangulationcreator.hpp \
    include/impro/private/interface/alljoyntriangulation.hpp \
    include/impro/interface/alljoynk201711creator.hpp \
    include/impro/private/interface/alljoynk201711.hpp \
    include/impro/interface/alljoynfieldcreator.hpp \
    include/impro/private/interface/alljoynfield.hpp


SOURCES += \
    src/alljoynspace.cpp \
    src/alljoynspacebuilder.cpp \
    src/alljoynlocalnode.cpp \
    src/alljoynutil.cpp \
    src/alljoynremotenode.cpp \
    src/alljoynremotelistener.cpp \
    src/alljoynlocallistener.cpp \
    src/alljoynlocalobject.cpp \
    src/alljoynremoteobject.cpp \
    src/alljoynremotechannel.cpp \
    src/alljoynlocalchannel.cpp \
    src/process/alljoyncameracontrollercreator.cpp \
    src/process/alljoyncameracontroller.cpp \
    src/interface/alljoynremotecamera.cpp \
    src/interface/alljoynremotecameracreator.cpp \
    src/interface/alljoynremotetrackingcreator.cpp \
    src/interface/alljoynremotetracking.cpp \
    src/interface/alljoynremotetriangulationcreator.cpp \
    src/interface/alljoynremotetriangulation.cpp \
    src/interface/alljoynremotek201711.cpp \
    src/interface/alljoynremotek201711creator.cpp \
    src/interface/alljoynremotefieldcreator.cpp \
    src/interface/alljoynremotefield.cpp

win32 {
    # impro core library
    LIBS += -L$(IMPRO_HOME)/build/lib \
            -limpro_core1

    # boost library
    LIBS += -L$(BOOST_HOME)/stage/lib \
            -llibboost_thread-vc141-mt-x64-1_68 \
            -llibboost_timer-vc141-mt-x64-1_68

    # opencv library
    LIBS += -L$(OPENCV_HOME)/x64/vc15/lib \
            -lopencv_world343


    # alljoyn library
    DEFINES += QCC_OS_GROUP_WINDOWS ROUTER UNICODE NDEBUG _MBCS

    LIBS += -L$(AJ_DIST)/cpp/lib \
            -lws2_32 \
            -lSecur32 \
            -lcrypt32 \
            -lBcrypt \
            -lNcrypt \
            -liphlpapi \
            -lkernel32 \
            -luser32 \
            -lgdi32 \
            -lwinspool \
            -lcomdlg32 \
            -ladvapi32 \
            -lshell32 \
            -lole32 \
            -loleaut32 \
            -luuid\
            -lodbc32 \
            -lodbccp32 \
            -lmsajapi \
            -lajrouter \
            -lalljoyn
}

# old version
#win32 {
#    # impro core library
#    LIBS += -L$(IMPRO_HOME)/build/lib \
#            -limpro_core1

#    # opencv library
#    LIBS += -L$(OPENCV_HOME)/build/x64/vc12/lib \
#            -lopencv_world310

#    # boost library
#    LIBS += -L$(BOOST_HOME)/lib64-msvc-12.0 \
#            -llibboost_thread-vc120-mt-1_61 \
#            -llibboost_timer-vc120-mt-1_61

#    # alljoyn library
#    DEFINES += QCC_OS_GROUP_WINDOWS UNICODE NDEBUG WIN32 _WINDOWS _USRDLL _MBCS

#    LIBS += -L$(AJ_DIST)/cpp/lib \
#            -lalljoyn \
#            -lajrouter \
#            -lws2_32 \
#            -lSecur32 \
#            -lcrypt32 \
#            -lBcrypt \
#            -lNcrypt \
#            -liphlpapi
#}


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

    # alljoyn library
    DEFINES += QCC_OS_LINUX QCC_OS_GROUP_POSIX
    LIBS += -L$(AJ_DIST)/cpp/lib/ \
            -lalljoyn

    QMAKE_LFLAGS += -Wl,-rpath,/home/linaro/Projects/impro/Desktop/build/lib:/home/linaro/Libraries/boost_1_68_0/stage/lib:/home/linaro/Libraries/opencv-3.4.3/release/lib://home/linaro/Libraries/core-alljoyn/build/linux/arm/release/dist/cpp/lib

}

