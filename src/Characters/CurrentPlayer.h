#include "Player.h"
class CurrentPlayer : public Player{

public:
    static inline CurrentPlayer *get(){
        return instance;
    }

    static inline CurrentPlayer *init(Vector2D position = 0){
        return instance = new CurrentPlayer(position);
    }

    static inline void clear() {
        delete instance;
    }

    void draw() override;
    void update(float dt) override;
    void debug() override;

private:
    static CurrentPlayer *instance;
    CurrentPlayer(Vector2D position = 0) : 
        Player(position),
        mousePosition(0)
    {}
    void input();    
    Vector2D mousePosition;
};
