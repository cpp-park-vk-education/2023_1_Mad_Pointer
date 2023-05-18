#pragma once
#include "../event/event_listener.h"
#include "../engine/engine.h"

class GameLoop : protected ecs::event::EventListenerBase {
public:

    //void OnPauseGame(const PauseGameEvent* event);
    //void OnResumeGame(const ResumeGameEvent* event);
    //void OnRestartGame(const RestartGameEvent* event);
    //void OnQuitGame(const QuitGameEvent* event);
    //void OnToggleFullscreen(const ToggleFullscreenEvent* event);

    //void OnCollisionBegin(const CollisionBeginEvent* event);

    //void OnStashFull(const StashFull* event);

private:

    //SDL_Window*					m_Window;
    int							m_WindowPosX;
    int							m_WindowPosY;
    int							m_WindowWidth;
    int							m_WindowHeight;
    bool						m_Fullscreen;
    const char*					m_GameTitle;
    float						m_DeltaTime;
    //GameContext					m_GameContext;
private:

    void InitializeECS() {}

    void InitializeSDL() {}

    void ProcessWindowEvent() {}

    void Terminate() {}

public:
    GameLoop(const char* name = "Game Name") {}

    ~GameLoop() {}

    void Initialize(int width, int height) {}

    void Run() {}

    //inline GameState	GetActiveGameState()	const { return (GameState)this->GetActiveState(); }
    //inline bool			IsInitialized()			const { return (this->GetActiveState() >  GameState::INITIALIZED); }
    //inline bool			IsRestarted()			const { return (this->GetActiveState() == GameState::RESTARTED); }
    //inline bool			IsStarted()				const { return (this->GetActiveState() == GameState::STARTED); }
    //inline bool			IsPaused()				const { return (this->GetActiveState() == GameState::PAUSED); }
    //inline bool			IsRunning()				const { return (this->GetActiveState() == GameState::RUNNING); }
    //inline bool			IsGameOver()			const { return (this->GetActiveState() == GameState::GAMEOVER); }
    //inline bool			IsTerminated()			const { return (this->GetActiveState() == GameState::TERMINATED); }



};


