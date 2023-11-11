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
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -ltinyxml
OBJ_DIR = ./../bin

# Fuentes y cabeceras
SOURCES = \
	main.cpp \
	Core/Engine.cpp \
	Graphics/TextureManager.cpp \
	Characters/Player.cpp \
	Graphics/Animation.cpp \
	Inputs/Input.cpp \
	Timer/Timer.cpp \
	Map/MapParser.cpp \
	Map/Chunk.cpp \
	Camera/Camera.cpp \
	Graphics/Text.cpp \
	Collision/CollisionHandler.cpp \
	Assets/AssetsManager.cpp \

HEADERS = \
	Core/Engine.h \
	Graphics/TextureManager.h \
	Physics/Vector2D.h \
	Object/IObject.h \
	Object/GameObject.h \
	Characters/Character.h \
	Characters/Player.h \
	Graphics/Animation.h \
	Physics/RigidBody.h \
	Inputs/Input.h \
	Timer/Timer.h \
	Map/GameMap.h \
	Map/Layer.h \
	Map/Chunk.h \
	Physics/Point.h \
	Camera/Camera.h \
	Graphics/Text.h \
	Physics/Collider.h \
	Collision/CollisionHandler.h \
	Assets/AssetsManager.h \


# Objetos generados
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))

CFLAGS = $(CFLAGS_DEBUG)
# Definición de la variable de opciones de compilación
#release:
	#$(eval override CFLAGS := $(CFLAGS_RELEASE))

# Regla de construcción del ejecutable
$(TARGET): $(OBJECTS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(OBJ_DIR)/$(TARGET) $(LIBS)
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
