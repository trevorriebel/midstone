#ifndef COIN_H
#define COIN_H
#include "Body.h"
class Coin : public Body {
public:

    Coin(Vec3 pos, Vec3 vel, Vec3 accel, float mass_);
    ~Coin();
    void setTexture(SDL_Texture* texture_) { texture = texture_; }
    SDL_Texture* getTexture() { return texture; }
    float getRadius() { return imageSizeWorldCoords.x / 2.0f; }
private:
    SDL_Texture* texture;
    double rotation;
};

#endif