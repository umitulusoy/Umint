#ifndef POINT_H
#define POINT_H


class point
{
public:
    point();
    ~point();

    void setX(float);
    void setY(float);
    void setZ(float);

    float getX();
    float getY();
    float getZ();
private:
    float x,y,z;
};

#endif // POINT_H
