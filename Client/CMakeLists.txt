cmake_minimum_required(VERSION 3.25)

project(Client)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Network)
qt_standard_project_setup()

# Исходные файлы
set(SOURCES
    GUI/Source/chatwidget.cpp
    GUI/Source/loadingwidget.cpp
    GUI/Source/mainwindow.cpp
    GUI/Source/settingswidget.cpp
    Main/Source/client.cpp
    Main/Source/main.cpp
    Protocol/Source/imessage.cpp
    Protocol/Source/packet.cpp
    Tcp/Source/tcpclient.cpp
)

set(INCLUDES
    GUI/Include/chatwidget.h
    GUI/Include/loadingwidget.h
    GUI/Include/mainwindow.h
    GUI/Include/settingswidget.h
    Main/Include/client.h
    Protocol/Include/imessage.h
    Protocol/Include/packet.h
    Protocol/Include/protocol.h
    Protocol/Include/serverstatusmessage.h
    Protocol/Include/useridnotification.h
    Protocol/Include/usermessage.h
    Tcp/Include/tcpclient.h
)

set(INCLUDE_PATH
    GUI/Include/
    Main/Include/
    Protocol/Include/
    Tcp/Include/
)

qt_add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCES} ${INCLUDES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core Qt6::Network)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_PATH})


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/Client/Config/srv.json" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)
