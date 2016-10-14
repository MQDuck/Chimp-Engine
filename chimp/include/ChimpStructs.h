/*
    Copyright 2016 Jeffrey Thomas Piercy
  
    This file is part of Chimp Engine.

    Chimp Engine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Chimp Engine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Chimp Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    T l, r, t, b;
};

typedef Box<int> IntBox;
typedef Box<bool> BoolBox;

} // namespace chimp

#endif // CHIMPSTRUCTS_H
