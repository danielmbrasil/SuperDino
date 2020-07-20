//
// Created by Daniel M Brasil on 6/29/20.
//

#ifndef GameObject_H
#define GameObject_H

#include "IObject.h"
#include "Transform.h"
#include <SDL2/SDL.h>

#include <utility>

struct Properties {
public:
    Properties(std::string texID, float x, float y, int w, int h, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        X = x;
        Y = y;
        Width = w;
        Height = h;
        TextureID = std::move(texID);
        Flip = flip;
    }

    std::string TextureID;
    int Width, Height;
    float X, Y;
    SDL_RendererFlip Flip;
};

class GameObject : public IObject {
public:
    explicit GameObject(Properties *properties) : textureID(properties->TextureID),
                                                  width(properties->Width), height(properties->Height),
                                                  flip(properties->Flip) {
        transform = new Transform(properties->X, properties->Y);
        origin = new Vector2D((properties->X + (float) properties->Width / 2),
                              (properties->Y + (float) properties->Height / 2));
    }

    inline Vector2D *getOrigin() { return origin; }

    void draw() override = 0;

    void update(float delta) override = 0;

    void clean() override = 0;

protected:
    std::string textureID;
    Transform *transform;
    int width, height;
    SDL_RendererFlip flip;

    Vector2D *origin;
};


#endif //GameObject_H
