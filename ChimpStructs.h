/*
    Copyright 2016 Jeffrey Thomas Piercy
  
    This file is part of Chimp Out!.

    Chimp Out! is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Chimp Out! is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

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
