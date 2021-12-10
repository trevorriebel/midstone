#include "Scene4.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Randomizer.h"
#include <iostream>
#include "VMath.h"
#include <Windows.h>
using namespace MATH;

int score = 0; // Game score
int direction = 1;

Scene4::Scene4(SDL_Window* sdlWindow_){
	
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	
		// Timer
		gameObjects[0] = new Body(Vec3(0, 7.3f, 0.0f),
							    Vec3(0.0f, 0.0f, 0.0f), 
								Vec3(0.0f, 0.0f, 0.0f), 1.0f);

		// Coin
		gameObjects[1] = new Body(Vec3(0.0f, 5.0f, 0.0f),
								Vec3(0.0f, 0.0f, 0.0f),
								Vec3(0.0f, 0.0f, 0.0f), 1.0f);

		// Player
		gameObjects[2] = new Body(Vec3(0.0f, -3.0f, 0.0f),
								Vec3(0.0f, 0.0f, 0.0f),
								Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	
}

Scene4::~Scene4(){
	for(int i = 0; i < NUM_OBJECTS; ++i){
		delete gameObjects[i];
	}
	SDL_DestroyRenderer(renderer);
}

bool Scene4::OnCreate() {
	int w, h;
	float xAxis = 15.0f;
	float yAxis = 7.5f;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(-xAxis, xAxis, -yAxis, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	invProjectionMatrix = MMath::inverse(projectionMatrix);
	
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* coinImage = IMG_Load("Coin.gif");
	SDL_Texture* coinTexture = SDL_CreateTextureFromSurface(renderer, coinImage);
	SDL_Surface* redImage = IMG_Load("red.png");
	SDL_Texture* redTexture = SDL_CreateTextureFromSurface(renderer, redImage);
	SDL_Surface* guyImage = IMG_Load("guy.png");
	SDL_Texture* guyTexture = SDL_CreateTextureFromSurface(renderer, guyImage);
	if(coinTexture == nullptr) printf("%s\n",SDL_GetError());
	if(coinImage == nullptr){
		std::cerr << "Can't open the image" << std::endl;
		return false;
	} else {
		
		/// Do some tricks with the image coords
		Vec3 upperLeft(0.0f,0.0f,0.0f); 
		Vec3 lowerRight(static_cast<float>(coinImage->w), static_cast<float>(coinImage->h),0.0f);
		Vec3 ulWorld = invProjectionMatrix * upperLeft;
		Vec3 lrWorld = invProjectionMatrix * lowerRight;
		Vec3 worldCoordsFromScreenCoords = lrWorld - ulWorld;
		///float r = worldCoordsFromScreenCoords.x / 2.0f;
		
		for(int i = 0; i < NUM_OBJECTS; i++){
			gameObjects[0]->setTexture(redTexture);
			gameObjects[1]->setTexture(coinTexture);
			gameObjects[2]->setTexture(guyTexture);
			gameObjects[i]->setImageSizeWorldCoords(worldCoordsFromScreenCoords);
		}
		SDL_FreeSurface(coinImage);	
	}
	return true;
}

void Scene4::OnDestroy() {
	/// We really need to deal with the textures better, they are left dangling right now
	SDL_DestroyRenderer(renderer);
}

void Scene4::Update(const float deltaTime) {

	gameObjects[0]->setVel(Vec3(-2.0f, 0.0f, 0.0f));
	for(int i = 0; i < NUM_OBJECTS; i = i + 1){
		gameObjects[i]->Update(deltaTime);
	}
	Vec3 pos = gameObjects[1]->getPos();
	Vec3 playerPos = gameObjects[2]->getPos();
	float distance = VMath::distance(pos, playerPos);
	float radius = gameObjects[1]->getRadius();
	if (distance < radius) { // Coin grab
		gameObjects[1]->setPos(Vec3(r.rand(-10.f, 10.f), r.rand(-5.f, 5.f), 0.0f));
		gameObjects[0]->setPos(Vec3(0, 7.3f, 0.0f));
		score++;
		printf("Score = %d\n", score);
	}
}

void Scene4::HandleEvents(const SDL_Event& sdlEvent) {

	if (sdlEvent.type == SDL_KEYDOWN) { // Up, left, down, right movement
		switch (sdlEvent.key.keysym.scancode) {
		case SDL_SCANCODE_W: //Go up
			gameObjects[2]->ApplyForce(Vec3(0.0f, 10.0f, 0.0f));
			break;
		case SDL_SCANCODE_A: //Go left
			gameObjects[2]->ApplyForce(Vec3(-10.0f, 0.0f, 0.0f));
			direction = 2;
			break;
		case SDL_SCANCODE_S: //Go down
			gameObjects[2]->ApplyForce(Vec3(0.0f, -10.0f, 0.0f));
			break;
		case SDL_SCANCODE_D: //Go right
			gameObjects[2]->ApplyForce(Vec3(10.0f, 0.0f, 0.0f));
			direction = 1;
			break;
		}
	}
	else if (sdlEvent.type == SDL_KEYUP) { //Undo the forces
		switch (sdlEvent.key.keysym.scancode) {
		case SDL_SCANCODE_W:
			gameObjects[2]->SetAccel(Vec3(0.0f, -9.81f, 0.0f));
			gameObjects[2]->setVel(Vec3(0.0f, 0.0f, 0.0f));
			break;
		case SDL_SCANCODE_A:
			gameObjects[2]->SetAccel(Vec3(0.0f, -9.81f, 0.0f));
			gameObjects[2]->setVel(Vec3(0.0f, 0.0f, 0.0f));
			break;
		case SDL_SCANCODE_S:
			gameObjects[2]->SetAccel(Vec3(0.0f, -9.81f, 0.0f));
			gameObjects[2]->setVel(Vec3(0.0f, 0.0f, 0.0f));
			break;
		case SDL_SCANCODE_D:
			gameObjects[2]->SetAccel(Vec3(0.0f, -9.81f, 0.0f));
			gameObjects[2]->setVel(Vec3(0.0f, 0.0f, 0.0f));
			break;
		}
	}
}


void Scene4::Render() {
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_RenderClear(renderer);
	SDL_Rect square;
	Vec3 screenCoords;
	int w,h;
	
	for(int i = 0; i < NUM_OBJECTS; ++i){
		SDL_QueryTexture(gameObjects[i]->getTexture(), nullptr, nullptr, &w, &h);
		screenCoords = projectionMatrix * gameObjects[i]->getPos();
		square.x = static_cast<int>(screenCoords.x) - w/2;
		square.y = static_cast<int>(screenCoords.y) - h/2;
		square.w = w;
		square.h = h;

		//SDL_RenderCopyEx(renderer, gameObjects[i]->getTexture(), nullptr, &square, gameObjects[i]->getRotation(), nullptr, SDL_FLIP_NONE);
		
		if (direction == 1) {
			SDL_RenderCopyEx(renderer, gameObjects[i]->getTexture(), nullptr, &square, gameObjects[i]->getRotation(), nullptr, SDL_FLIP_NONE);
		}
		else if (direction == 2 && i == 2){
			SDL_RenderCopyEx(renderer, gameObjects[i]->getTexture(), nullptr, &square, gameObjects[i]->getRotation(), nullptr, SDL_FLIP_HORIZONTAL);

		}
		else {
			SDL_RenderCopyEx(renderer, gameObjects[i]->getTexture(), nullptr, &square, gameObjects[i]->getRotation(), nullptr, SDL_FLIP_NONE);

		}
	}
	SDL_RenderPresent(renderer);
}