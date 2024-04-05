#ifndef IOBJECT_H
#define IOBJECT_H


class IObject
{
public:
    virtual void draw() {
        toRender = false;
    };
    virtual void update( float dt )=0;
    virtual void debug()=0;
    inline bool isToRender() {
        return toRender;
    }

protected:
    bool toRender = false;
};

#endif // IOBJECT_H
