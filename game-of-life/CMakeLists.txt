# Проверка версии CMake для корректной работы
cmake_minimum_required(VERSION 3.10)

# Задаем название проекта
project(GameOfLife)

# Определяем стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Поиск установленной библиотеки
find_package(SDL2 REQUIRED)

# Указываем исходные файлы
file(GLOB SOURCES "src/*.cpp")

# Создаем исполняемый файл
add_executable(GameOfLife ${SOURCES})

# Подключаем каталог с заголовочными файлами
include_directories(include)
include_directories(GameOfLife ${SDL2_INCLUDE_DIRS})

# Связываем библиотеку SDL2 с нашим проектом
target_link_libraries(GameOfLife ${SDL2_LIBRARIES})

# Добавляем файл SDL2.dll к исполняемому файлу для запуска приложения
add_custom_command(TARGET GameOfLife POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_LIBDIR}/SDL2.dll"
        $<TARGET_FILE_DIR:GameOfLife>)

# Устанавливаем подсистему для предотвращения открытия консольного окна
if(MSVC)
    set_target_properties(GameOfLife PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
else()
    set_target_properties(GameOfLife PROPERTIES LINK_FLAGS "-mwindows")
endif()

# Установка типа сборки по умолчанию
set(CMAKE_BUILD_TYPE Release)