#ifndef IOBJECT_H
#define IOBJECT_H


class IObject
{
public:
    virtual void draw()=0;
    virtual void update( float dt )=0;
};

#endif // IOBJECT_H
