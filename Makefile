# Nombre del ejecutable
TARGET = survivalProject
USE_VALGRIND = 0

# Compilador
CC = g++

# Opciones de compilación para el modo "release"
CFLAGS_RELEASE = -std=c++17 -I/usr/local/include -O2 -s

# Opciones de compilación para el modo "debug"
CFLAGS_DEBUG = -std=c++17 -I/usr/local/include -O0 -g

# Rutas a las bibliotecas
LDFLAGS = -L/usr/local/lib
LIBS = -lSDL3 -ltinyxml
OBJ_DIR = ./obj

# Fuentes y cabeceras
SOURCES = \
	src/Graphics/TextureManager.cpp \
	src/main.cpp \
	src/Core/Engine.cpp \
	src/Object/GameObject.cpp \
	src/Characters/Character.cpp \
	src/Characters/Player.cpp \
	src/Graphics/Animation.cpp \
	src/Inputs/Input.cpp \
	src/Map/GameMap.cpp \
	src/Map/MapParser.cpp \
	src/Map/Chunk.cpp \
	src/Camera/Camera.cpp \
	src/Physics/Collider.cpp \
	src/Physics/CollisionHandler.cpp \
	src/Assets/AssetsManager.cpp \

HEADERS = \
	src/Graphics/TextureManager.h \
	src/Physics/Vector2D.h \
	src/Core/Engine.h \
	src/Object/IObject.h \
	src/Object/GameObject.h \
	src/Characters/Character.h \
	src/Characters/Player.h \
	src/Graphics/Animation.h \
	src/Physics/RigidBody.h \
	src/Inputs/Input.h \
	src/Timer/Timer.h \
	src/Map/GameMap.h \
	src/Map/Chunk.h \
	src/Physics/Point.h \
	src/Camera/Camera.h \
	src/Physics/Collider.h \
	src/Physics/CollisionHandler.h \
	src/Assets/AssetsManager.h \


# Objetos generados
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))

CFLAGS = $(CFLAGS_DEBUG)
# Definición de la variable de opciones de compilación
#release:
	#$(eval override CFLAGS := $(CFLAGS_RELEASE))

# Regla de construcción del ejecutable
$(TARGET): $(OBJECTS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS)
ifeq ($(USE_VALGRIND), 1)
	valgrind --show-leak-kinds=definite $(OBJ_DIR)/$(TARGET) 2> valgind.txt
endif

$(OBJ_DIR)/%.o: %.cpp $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para generar las dependencias automáticamente
depend: .depend

.depend: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -MM $(SOURCES) > .depend

include .depend

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET) .depend

# Regla por defecto
all: $(TARGET)

.PHONY: all clean depend
