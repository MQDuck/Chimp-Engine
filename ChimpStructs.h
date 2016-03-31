#ifndef CHIMPSTRUCTS_H
#define CHIMPSTRUCTS_H

#include <vector>

namespace chimp
{

struct Coordinate
{
    float x, y;
};

template<typename T>
struct Box
{
    T l, t, r, b;
    
    void scale(int scl)
    {
        l /= scl;
        r /= scl;
        t /= scl;
        b /= scl;
    }
    
    inline T getL() const { return l; }
    inline T getR() const { return r; }
    inline T getT() const { return t; }
    inline T getB() const { return b; }
};

typedef Box<int> IntBox;

} // namespace chimp

#endif // CHIMPSTRUCTS_H
