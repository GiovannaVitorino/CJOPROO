# =============================================================
#  SheetMasters — Makefile universal
#  Windows (MinGW): mingw32-make
#  Linux / macOS:   make
# =============================================================

CXX      ?= g++
TARGET   = SheetMasters
SRC_DIR  = src
INC_DIR  = include

# Lista fontes e transforma cada .cpp em um .o correspondente dentro de build/.
SRCS     = $(wildcard $(SRC_DIR)/*.cpp)
OBJS     = $(SRCS:$(SRC_DIR)/%.cpp=build/%.o)

# Flags de compilacao e linkagem compartilhadas entre plataformas.
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I$(INC_DIR)
LDFLAGS  =

# ------ Detecção de plataforma ------
ifeq ($(OS),Windows_NT)
    # Windows com MinGW
    RAYLIB_DIR  ?= C:/raylib
    # Se existir o compilador empacotado da raylib, usa ele como CXX.
    ifneq ($(wildcard $(RAYLIB_DIR)/w64devkit/bin/g++.exe),)
        CXX = $(RAYLIB_DIR)/w64devkit/bin/g++.exe -B$(RAYLIB_DIR)/w64devkit/bin/
    endif
    # Escolhe paths de include/lib conforme o layout encontrado da raylib.
    ifneq ($(wildcard $(RAYLIB_DIR)/raylib/src/raylib.h),)
        RAYLIB_INC = $(RAYLIB_DIR)/raylib/src
        RAYLIB_LIB = $(RAYLIB_DIR)/raylib/src
    else ifneq ($(wildcard $(RAYLIB_DIR)/include/raylib.h),)
        RAYLIB_INC = $(RAYLIB_DIR)/include
        RAYLIB_LIB = $(RAYLIB_DIR)/lib
    else
        RAYLIB_INC = $(RAYLIB_DIR)/w64devkit/include
        RAYLIB_LIB = $(RAYLIB_DIR)/w64devkit/lib
    endif
    CXXFLAGS    += -I$(RAYLIB_INC)
    LDFLAGS     += -L$(RAYLIB_LIB) -lraylib \
                   -lopengl32 -lgdi32 -lwinmm \
                   -static -lpthread
    TARGET_EXE   = $(TARGET).exe
    MKDIR        = build
    RM           = del /Q build\*.o $(TARGET_EXE) 2>nul || exit 0
else
    # Em sistemas Unix, detecta macOS ou Linux para ajustar bibliotecas nativas.
    UNAME := $(shell uname -s)
    ifeq ($(UNAME),Darwin)
        # macOS (Homebrew)
        CXXFLAGS += -I/opt/homebrew/include
        LDFLAGS  += -L/opt/homebrew/lib -lraylib \
                    -framework OpenGL -framework Cocoa \
                    -framework IOKit -framework CoreAudio \
                    -framework CoreVideo
    else
        # Linux — tenta pkg-config, senão usa pasta local
        ifneq ($(shell pkg-config --exists raylib 2>/dev/null && echo y),y)
            RAYLIB_LOCAL = raylib_local
            CXXFLAGS    += -I$(RAYLIB_LOCAL)/include
            LDFLAGS     += -L$(RAYLIB_LOCAL)/lib
        else
            CXXFLAGS    += $(shell pkg-config --cflags raylib)
        endif
        LDFLAGS += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    endif
    TARGET_EXE = $(TARGET)
    MKDIR      = build
    RM         = rm -f build/*.o $(TARGET_EXE)
endif

# ------ Regras ------
.PHONY: all clean run

# Compila tudo e mostra uma mensagem simples de sucesso.
all: $(MKDIR) $(TARGET_EXE)
	@echo "=== Build OK: $(TARGET_EXE) ==="

# Garante que a pasta build exista antes de compilar objetos.
$(MKDIR):
ifeq ($(OS),Windows_NT)
	if not exist build mkdir build
else
	mkdir -p build
endif

# Linka todos os objetos no executavel final.
$(TARGET_EXE): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Compila cada arquivo .cpp em um objeto .o.
build/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove artefatos de build gerados localmente.
clean:
	$(RM)

# Compila e executa o jogo.
run: all
	./$(TARGET_EXE)
