#include "Body.h"
#include "MMath.h"
#include "VMath.h"

Body::Body() {
	pos.x = 2.3f;
	pos.y = 12.5f;
	pos.z = 0.0f;

	vel.x = 4.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;

	accel.x = 0.0f;
	accel.y = 0.0f;
	accel.z = 0.0f;

	mass = 1.0f;
	rotation = 0.0;
	image = nullptr;
}

Body::Body(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_) {
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;

	accel.x = accel_.x;
	accel.y = accel_.y;
	accel.z = accel_.z;

	mass = mass_;
	image = nullptr;
	rotation = 0.0;
    radius = 1.2f;
}

Body::~Body() {

}

void Body::ApplyForce(Vec3 force_) {
	accel.x = force_.x / mass;
	accel.y = force_.y / mass;
	accel.z = force_.z / mass;
}

//void Body::HandleEvents(const SDL_Event& sdlEvent) {
//	if (sdlEvent.type == SDL_KEYDOWN) {
//		switch (sdlEvent.key.keysym.scancode) {
//		case SDL_SCANCODE_RETURN:
//			ApplyForce(Vec3(100.0f, 0.0f, 0.0f));
//			break;
//
//		case SDL_SCANCODE_UP:
//			ApplyForce(Vec3(0.0f, 2.0f, 0.0f));
//			break;
//
//		default:
//			break;
//		}
//
//	} else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_RETURN) {
//		ApplyForce(Vec3(0.0f, 0.0f, 0.0f));
//
//	} else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN || sdlEvent.button.button == SDL_BUTTON_LEFT) {
//		printf("LEFT MOUSE!!! x= %d y= %d\n", sdlEvent.motion.x, sdlEvent.motion.y);
//
//	} else if (sdlEvent.type == SDL_MOUSEMOTION) {
//		printf("Mouse in motion x= %d y= %d\n", sdlEvent.motion.x, sdlEvent.motion.y);
//	}
//}

void Body::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE) {
		printf("Mousedown!\n");
	}
	else if (sdlEvent.type == SDL_MOUSEMOTION) {
		printf("Mousemotion! %d\n", sdlEvent.motion.x, sdlEvent.motion.y);
	}
	else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
		//printf("left mouse!  %d\n", sdlEvent.motion.x, sdlEvent.motion.y, 0.0f);
	}
	else if (sdlEvent.type == SDL_KEYDOWN) {
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE) {


			Vec3 dir(1.0f, 0.0f, 0.0f);
			Vec3 origPos(0.0f, 2.3f, 0.0f);
			Matrix4 rot = MMath::rotate(27.0f, Vec3(0.0f, 0.0f, 1.0f));
			dir = rot * dir * 2.0f;
			float mag = VMath::mag(dir);
			dir.print();
			printf("%f\n", mag);
			pos = origPos;
			vel = dir;
		}



		//Matrix4 tr = MMath::translate(2.5f, 2.3f, 0.0f);
		//Matrix4 rot = MMath::rotate(30.0f, Vec3(0.0f, 0.0f, 1.0f));
		//pos = rot * tr * pos;
		////pos = MMath::translate(2.5f, 15.0f, 0.0f) * pos; //read it right to the left

	}
	else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN && sdlEvent.button.clicks == SDL_BUTTON_LEFT) {

	}
	else if (sdlEvent.type == SDL_MOUSEMOTION) {

	}
}

void Body::Update(float deltaTime) {

	pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
	vel += accel * deltaTime;

	//rotation += (360.0f * vel.x * deltaTime) / (2.0f * M_PI * imageSizeWorldCoords.x / 2.0f);


	if (pos.y - imageSizeWorldCoords.y < -6.4f) { /// Floor
		vel.y *= -1.0f;
	}

	if (pos.x < -14.3f) { /// Left wall
		vel.x *= -1.0f;
	}

	if (pos.x + imageSizeWorldCoords.x > 15.0f) { ///Right wall
		vel.x *= -1.0f;
	}

	if (pos.y > 6.5) {
		vel.y *= -1.0f;
	}

}
