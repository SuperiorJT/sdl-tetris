//
//  math.h
//
//
//  Created by Justin Miller on 11/27/15.
//
//

#ifndef ____utility__
#define ____utility__

#include <stdio.h>
#include <SDL_ttf.h>
#include <string>

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

SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
	SDL_Color color, int fontSize, SDL_Renderer *renderer);

#endif /* defined(____utility__) */
