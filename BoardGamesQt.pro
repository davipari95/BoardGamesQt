QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    classes/mdisubwindows/rules_viewer.cpp \
    classes/mdisubwindows/tictactoe/tictactoe_local_game_mdisubwindow.cpp \
    classes/mdisubwindows/tictactoe/tictactoe_local_game_settings_mdisubwindow.cpp \
    classes/objects/custom_components/qgridlabel.cpp \
    classes/objects/gridposition.cpp \
    classes/objects/tictactoe/board.cpp \
    classes/objects/tictactoe/match.cpp \
    classes/utils/u_frames.cpp \
    classes/utils/u_locale.cpp \
    classes/utils/u_messageboxes.cpp \
    classes/virtuals/cloneable.cpp \
    classes/virtuals/equatable.cpp \
    classes/virtuals/to_stringable.cpp \
    main.cpp \
    main_window.cpp \
    variables/v_styles.cpp

HEADERS += \
    classes/mdisubwindows/rules_viewer.h \
    classes/mdisubwindows/tictactoe/tictactoe_local_game_mdisubwindow.h \
    classes/mdisubwindows/tictactoe/tictactoe_local_game_settings_mdisubwindow.h \
    classes/objects/custom_components/qgridlabel.h \
    classes/objects/gridposition.h \
    classes/objects/tictactoe/board.h \
    classes/objects/tictactoe/match.h \
    classes/utils/u_frames.h \
    classes/utils/u_locale.h \
    classes/utils/u_messageboxes.h \
    classes/virtuals/cloneable.h \
    classes/virtuals/equatable.h \
    classes/virtuals/to_stringable.h \
    enums/tictactoe/tictactoe_players_enum.h \
    main_window.h \
    variables/v_styles.h \
    variables/v_widget.h

FORMS += \
    classes/mdisubwindows/rules_viewer.ui \
    classes/mdisubwindows/tictactoe/tictactoe_local_game_mdisubwindow.ui \
    classes/mdisubwindows/tictactoe/tictactoe_local_game_settings_mdisubwindow.ui \
    main_window.ui

TRANSLATIONS += \
    BoardGamesQt_it_IT.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
