cmake_minimum_required(VERSION 3.10.0)
project(VocabularyTrainer VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED Widgets)

set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/Dictionary.cpp
    src/AddWordsWindow.cpp
)

set(HEADERS
    include/MainWindow.h
    include/Dictionary.h
    include/AddWordsWindow.h
)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(VocabularyTrainer ${SOURCES} ${HEADERS})

target_link_libraries(VocabularyTrainer Qt6::Widgets)