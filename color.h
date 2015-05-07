#ifndef COLOR_H
#define COLOR_H


class Color
{
public:
    Color();
    ~Color();

    void setR(int);
    void setG(int);
    void setB(int);
    void setA(int);

    int getR();
    int getB();
    int getG();
    int getA();

private:
    int red, green, blue, alpha;
};

#endif // COLOR_H
