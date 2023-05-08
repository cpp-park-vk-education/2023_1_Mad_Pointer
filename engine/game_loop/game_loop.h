
namespace ecs {
    class Loop {
    private:
        double m_previous;
        double m_fpsTimer;
        double m_lag;
        int m_frames;
        int m_updates;
        int m_msPerUpdate;

        GameBase& m_game;

    public:
        Loop(GameBase& game, int msPerUpdate = 1000 / 120) :
                m_previous(ez::getCurrentTime()),
                m_fpsTimer(ez::getCurrentTime()),
                m_lag(0.0),
                m_frames(0),
                m_updates(0),
                m_msPerUpdate(msPerUpdate), // 1000 / 120 is used to represent 120ms delay
                m_game(game) {}

        // Commences the game loop.
        void begin()
        {
            while (m_game.isOpen()) {

                double current = ez::getCurrentTime();
                double elapsed = current - m_previous;
                m_previous = current;
                m_lag += elapsed;

                // Process input
                m_game.processInput();

                while (m_lag >= m_msPerUpdate) {
                    // Update game state
                    m_game.update();

                    m_lag -= m_msPerUpdate;
                    m_updates++;
                }

                // Render
                m_game.render(m_lag / m_msPerUpdate);
                m_frames++;

                // Update FPS counter
                if (ez::getCurrentTime() - m_fpsTimer > 1000) {
                    m_fpsTimer += 1000;

                    m_game.setFPS(m_frames);
                    m_game.setUPS(m_updates);

                    m_frames = 0;
                    m_updates = 0;
                }

            }
        }
    };
    class GameLoop {
    public:
        void run() {
            while (is_running) {

            }
        }

        void processInput() {

        }

        void update(double deltaTime) {

        }

        void render(double deltaTime) {

        }

    private:
        double m_timeStarted;
        bool is_running = false;
    };
}