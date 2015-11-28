//
//  math.h
//  
//
//  Created by Justin Miller on 11/27/15.
//
//

#ifndef ____math__
#define ____math__

#include <stdio.h>

class Vector2 {
    
public:
    double x;
    double y;
    
    Vector2() {};
    Vector2(double x, double y) : x(x), y(y) {};
    Vector2 operator + (const Vector2&);
    Vector2& operator = (const Vector2&);
    ~Vector2() {};
    
};

#endif /* defined(____math__) */
