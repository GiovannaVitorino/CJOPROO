cmake_minimum_required(VERSION 3.16)

# Declara o projeto C++ e a versao minima do padrao usada pelo codigo.
project(SheetMasters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Coleta todos os .cpp da pasta src e cria o executavel principal.
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(SheetMasters ${SOURCES})
target_include_directories(SheetMasters PRIVATE include)

# ---- Raylib ----
# Tenta pkg-config primeiro (Linux/macOS com instalação padrão)
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(RAYLIB QUIET raylib)
endif()

if(RAYLIB_FOUND)
    # Usa flags encontradas pelo pkg-config quando raylib esta instalada no sistema.
    target_include_directories(SheetMasters PRIVATE ${RAYLIB_INCLUDE_DIRS})
    target_link_libraries(SheetMasters PRIVATE ${RAYLIB_LIBRARIES})
else()
    # Windows ou instalação local: ajuste RAYLIB_DIR conforme seu ambiente
    # Opção A: vcpkg
    find_package(raylib CONFIG QUIET)
    if(raylib_FOUND)
        # Usa o pacote raylib encontrado por gerenciadores como vcpkg.
        target_link_libraries(SheetMasters PRIVATE raylib)
    else()
        # Opção B: pasta local (raylib_local/ dentro do projeto)
        set(RAYLIB_LOCAL "${CMAKE_SOURCE_DIR}/raylib_local")
        target_include_directories(SheetMasters PRIVATE "${RAYLIB_LOCAL}/include")
        target_link_directories(SheetMasters PRIVATE "${RAYLIB_LOCAL}/lib")
        target_link_libraries(SheetMasters PRIVATE raylib)
        if(WIN32)
            # Bibliotecas nativas necessarias para raylib no Windows.
            target_link_libraries(SheetMasters PRIVATE opengl32 gdi32 winmm)
        elseif(UNIX AND NOT APPLE)
            # Bibliotecas nativas comuns para raylib no Linux.
            target_link_libraries(SheetMasters PRIVATE GL m pthread dl rt X11)
        elseif(APPLE)
            # Frameworks necessarios para raylib no macOS.
            target_link_libraries(SheetMasters PRIVATE
                "-framework OpenGL" "-framework Cocoa"
                "-framework IOKit"  "-framework CoreAudio"
                "-framework CoreVideo")
        endif()
    endif()
endif()

# Copia assets para pasta do executável
add_custom_command(TARGET SheetMasters POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:SheetMasters>/assets"
    COMMENT "Copiando assets...")
