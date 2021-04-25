/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.h
Purpose: Header file for Engine Module
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#include <chrono>
#include "GameStateManager.h"
#include "Input.h"
#include "Window.h"
#include "Logger.h"
#include "TextureManager.h"


class Engine {
public:
	static Engine& Instance() { static Engine instance; return instance; }
	static Logger& GetLogger() { return Instance().logger; };
	static Input& GetInput() { return Instance().input; }
	static Window& GetWindow() { return Instance().window; }
	static GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }
	static TextureManager& GetTextureManager() { return Instance().textureManager; }
	
	void Init(std::string windowName);
	void Shutdown();
	void Update();
	bool HasGameEnded();
private:
	Engine();
	~Engine();

	std::chrono::system_clock::time_point lastTick;
	std::chrono::system_clock::time_point fpsCalcTime;
	int frameCount;

	Logger logger;
	TextureManager textureManager;
	GameStateManager gameStateManager;
	Input input;
	Window window;

	static constexpr double Target_FPS = 30.0;    
	static constexpr int FPS_IntervalSec = 5;
	static constexpr int FPS_IntervalFrameCount = static_cast<int>(FPS_IntervalSec* Target_FPS);
};