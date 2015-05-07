#ifndef LOCALITY_H
#define LOCALITY_H
#include "point.h"
#include "color.h"
#include "stdlib.h"

class Locality
{
public:
    int type, selectedSize;
    bool isFilled;
    point *start;
    point *end;

};

#endif // LOCALITY_H
