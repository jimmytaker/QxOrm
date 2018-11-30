#################################################################################################
## File created by QxEntityEditor 1.2.3 (2018/11/30 09:04) : please, do NOT modify this file ! ##
#################################################################################################

include($$PWD/../../../QxOrm.pri)

TEMPLATE = lib
CONFIG += dll
DEFINES += _BUILDING_KPI
INCLUDEPATH += $$PWD/../../../include
DESTDIR = $$PWD/bin/

CONFIG(debug, debug|release) {
TARGET = KPId
} else {
TARGET = KPI
} # CONFIG(debug, debug|release)

LIBS += -L"$$PWD/../../../lib"

CONFIG(debug, debug|release) {
LIBS += -l"QxOrmd"
} else {
LIBS += -l"QxOrm"
} # CONFIG(debug, debug|release)

include($$PWD/KPI.gen.pri)

!contains(DEFINES, _QX_UNITY_BUILD) {
SOURCES += $$PWD/src/KPI_main.gen.cpp
} # !contains(DEFINES, _QX_UNITY_BUILD)
