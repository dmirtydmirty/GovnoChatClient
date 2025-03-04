cmake_minimum_required(VERSION 3.25)

# Указываем проект и его версию
project(JsonTests VERSION 1.0 LANGUAGES CXX)

# Указываем, что будем использовать Qt
find_package(Qt6 REQUIRED COMPONENTS Core Test)

# Устанавливаем флаги компиляции
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем пути к заголовочным файлам
include_directories(
    ../Client/Protocol/Include/
)

set(MOC_HEADERS
    ../Client/Protocol/Include/imessage.h
    ../Client/Protocol/Include/packet.h
    ../Client/Protocol/Include/serverstatusmessage.h
    ../Client/Protocol/Include/useridnotification.h
    ../Client/Protocol/Include/usermessage.h
)

qt_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

add_executable(JsonTests ${SOURCES} ${MOC_SOURCES})

# Указываем зависимости от Qt
target_link_libraries(JsonTests PRIVATE Qt6::Core Qt6::Test)

# Если нужно добавить дополнительные флаги компиляции
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Wextra)
endif()


