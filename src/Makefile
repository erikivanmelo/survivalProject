# Nombre del ejecutable
TARGET = survivalProject

# Compilador
CC = g++

# Opciones de compilación
CFLAGS = -std=c++17 -I/usr/local/include

# Rutas a las bibliotecas
LDFLAGS = -L/usr/local/lib
LIBS = -lSDL2 -lSDL2_image -ltinyxml
OBJ_DIR = ./../bin

# Fuentes y cabeceras
SOURCES = \
	main.cpp \
	Core/Engine.cpp \
	Graphics/TextureManager.cpp \
	Characters/Player.cpp \
	Animation/Animation.cpp \
	Inputs/Input.cpp \
	Timer/Timer.cpp \

HEADERS = \
	Core/Engine.h \
	Graphics/TextureManager.h \
	Physics/Vector2D.h \
	Physics/Transform.h \
	Object/IObject.h \
	Object/GameObject.h \
	Characters/Character.h \
	Characters/Player.h \
	Animation/Animation.h \
	Physics/RigidBody.h \
	Inputs/Input.h \
	Timer/Timer.h \

# Objetos generados
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))

# Regla de construcción del ejecutable
$(TARGET): $(OBJECTS)
	mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(OBJ_DIR)/$(TARGET) $(LIBS)

# Regla de compilación de archivos fuente
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
