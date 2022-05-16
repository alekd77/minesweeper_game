cmake_minimum_required(VERSION 3.1)

project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra)

if (UNIX)
    set ( CMAKE_MODULES_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})

endif(UNIX)

if (WIN32)
    set( SFML_STATIC_LIBRARIES TRUE )
    set ( SFML_DIR "D:/Studia/Programowanie/SFML/SFML-2.5.1/lib/cmake/SFML")

endif(WIN32)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

add_executable( MyApp main.cpp Minesweeper.h Minesweeper.cpp
                MSBoardTextView.h MSBoardTextView.cpp
                MSTextController.h MSTextController.cpp
                MSSFMLView.cpp MSSFMLView.h
                MSSFMLController.cpp MSSFMLController.h
                MSSFMLRendering.cpp MSSFMLRendering.h
                TextureManager.cpp TextureManager.h
        )

target_link_libraries (MyApp sfml-graphics sfml-audio)