#include <SDL.h>

class Game {

public:
    void OnQuitGame(const QuitGameEvent* event);
    void OnCollisionBegin(const CollisionBeginEvent* event);
private:
    SDL_Window*	m_Window;

    int	m_WindowPosX;
    int	m_WindowPosY;

    int	m_WindowWidth;
    int	m_WindowHeight;

    bool m_Fullscreen;

    const char* m_GameTitle;

    FPS	m_FPS;
    float	m_DeltaTime;

    GameContext	m_GameContext;
    ECS::SystemWorkStateMask m_Ingame_SystemWSM;
    ECS::SystemWorkStateMask m_NotIngame_SystemWSM;
private:

    void InitializeECS();
    void InitializeSDL();
    void ProcessWindowEvent();
    void Terminate();

public:
    Game(const char* name = "The Floors");
    ~Game();

    void Initialize(int width, int height);

    void Run();

    inline GameState GetActiveGameState() const { return (GameState)this->GetActiveState(); }
    inline bool	IsInitialized()	const { return (this->GetActiveState() >  GameState::INITIALIZED); }
    inline bool	IsStarted()	const { return (this->GetActiveState() == GameState::STARTED); }
    inline bool	IsRunning()	const { return (this->GetActiveState() == GameState::RUNNING); }
    inline bool	IsGameOver() const { return (this->GetActiveState() == GameState::GAMEOVER); }
    inline bool	IsTerminated() const { return (this->GetActiveState() == GameState::TERMINATED); }

};
