TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
SOURCES += \
        boy_sprite.cpp \
        collision.cpp \
        main.cpp \
        map_sprite.cpp \
        obstacle_sprite.cpp
INCLUDEPATH += "C:/Users/48884/Documents/Studia/Semestr 2/PSIO/SFML-2.5.1/include"
LIBS += -L"C:/Users/48884/Documents/Studia/Semestr 2/PSIO/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    boy_sprite.h \
    collision.h \
    map_sprite.h \
    obstacle_sprite.h

