#ifndef CHIMPSTRUCTS_H
#define CHIMPSTRUCTS_H

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
};

} // namespace chimp

#endif // CHIMPSTRUCTS_H
