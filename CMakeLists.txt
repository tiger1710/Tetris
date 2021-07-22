cmake_minimum_required(VERSION 3.0.0)
project(Tetris VERSION 0.1.0)

include(CTest)
enable_testing()

set(SRC_FILES
        src/blockStageControl.c
        src/keyCurControl.c
        src/process.c
        src/scoreLevelControl.c
        src/tetrisMain.c
)
add_executable(Tetris ${SRC_FILES})

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(Tetris ${CURSES_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
