#ifndef BALL_H
#define BALL_H
#include "Body.h"
class Ball : public Body {
public:

    Ball(Vec3 pos, Vec3 vel, Vec3 accel, float mass_);
    ~Ball();
    void setTexture(SDL_Texture* texture_) { texture = texture_; }
    SDL_Texture* getTexture() { return texture; }
    float getRadius() { return imageSizeWorldCoords.x / 2.0f; }
private:
    SDL_Texture* texture;
    double rotation;
};

#endif