TEMPLATE = subdirs

SUBDIRS += \
    Client \
    Test

# cmake_minimum_required(VERSION 3.15)
# project(YourProject)

# set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

# find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

# # Исходные файлы
# set(SOURCES
#     main.cpp
#     configmanager.cpp
#     configmanager.h
# )

# add_executable(${PROJECT_NAME} ${SOURCES})

# target_link_libraries(${PROJECT_NAME} Qt::Widgets Qt::Core)

# # Копируем srv.json в каталог с исполняемым файлом
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/srv.json" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
