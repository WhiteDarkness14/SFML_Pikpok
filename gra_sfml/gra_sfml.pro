TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
SOURCES += \
        boss_sprite.cpp \
        character_sprite.cpp \
        collision.cpp \
        general.cpp \
        main.cpp \
        map_sprite.cpp \
        my_text.cpp \
        obstacle_sprite.cpp
INCLUDEPATH += "C:/Users/48884/Documents/Studia/Semestr 2/PSIO/SFML-2.5.1/include"
LIBS += -L"C:/Users/48884/Documents/Studia/Semestr 2/PSIO/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    boss_sprite.h \
    character_sprite.h \
    collision.h \
    general.h \
    map_sprite.h \
    my_text.h \
    obstacle_sprite.h

