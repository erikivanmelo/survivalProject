#include "../Physics/Vector2D.h"

class Debug{

public:
    inline static Debug *get(){ return instance = (instance == nullptr)? new Debug() : instance; }
    

private:

    Debug(){
    
    }
    ~Debug(){}

    inline static void clean(){ delete instance; }
    static Debug *instance;

    Vector2D *playerCoordenate;
    Vector2D *camerCoordenate;


};
