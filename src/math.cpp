//
//  math.cpp
//  
//
//  Created by Justin Miller on 11/27/15.
//
//

#include "math.h"

Vector2 Vector2::operator+(const Vector2& param) {
    Vector2 temp;
    temp.x = x + param.x;
    temp.y = y + param.y;
    return temp;
}

Vector2& Vector2::operator=(const Vector2& param) {
    y = param.y;
    x = param.x;
    return *this;
}