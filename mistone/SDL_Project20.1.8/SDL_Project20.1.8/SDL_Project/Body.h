#ifndef BODY_H
#define BODY_H

#include "Vector.h"
#include <SDL_image.h>
using namespace MATH;

class Body {
protected:
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
	SDL_Surface* image;
	Vec3 imageSizeWorldCoords;
	SDL_Texture* texture;
	double rotation;
	float radius;
	bool caught;

public:
	Body();
	Body(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_);

	~Body();
	void Update(float deltaTime);
	void HandleEvents(const SDL_Event& sdlEvent);
	void ApplyForce(Vec3 force_);
	float getRadius() { return radius; }
	Vec3 getPos() { return pos; }
	void setPos(Vec3 pos_) { pos = pos_; }


	bool BallCaptured() { return caught; }
	void Captured() { caught = true; }
	void letGo() { caught = false; }
	void SetAccel(const Vec3& accel_) {
		accel = accel_;
	}


	void setImage(SDL_Surface* image_) { image = image_; }
	SDL_Surface* getImage() { return image; }
	void setImageSizeWorldCoords(Vec3 imageSizeWorldCoords_) {
		imageSizeWorldCoords = imageSizeWorldCoords_;
	}
	Vec3 getImageSizeWorldCoords() { return imageSizeWorldCoords; }
	void setVel(Vec3 vel_) { vel = vel_; }
	double getRotation() { return rotation; }
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	SDL_Texture* getTexture() { return texture; }
};

#endif

