#include <array>
#include <cstdint>

class Chunk {
public:
    static const int CHUNK_SIZE = 16; // Tamaño del chunk (ejemplo: 16x16 tiles)
    
    Chunk(int x, int y);
    ~Chunk();
    
    // Métodos para agregar, eliminar y obtener elementos en el chunk (por ejemplo, bloques).
    inline void addTile( const int8_t x, const int8_t y, const int tileID){
        this->tiles[x][y] = tileID;
    }

    inline void removeTile( const int8_t x, const int8_t y ){
        this->tiles[x][y] = 0;
    }

    inline int getTile( const int8_t x, const int8_t y ) const{
        return this->tiles[x][y];
    };
    
    // Método para renderizar el chunk.
    void render();
    
private:
    int chunkX; // Posición X del chunk en el mundo.
    int chunkY; // Posición Y del chunk en el mundo.
    
    // Almacenar información de los elementos en el chunk (puede ser una matriz o una estructura más eficiente).
    std::array<std::array<int,8>,8> tiles; // Matriz de identificadores de tiles.
};
