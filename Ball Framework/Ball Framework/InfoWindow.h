#include "Game.h"
#include <optional>

namespace BallFramework
{

    class InfoWindow :
        public Game
    {
    public:
        InfoWindow(const std::string& title, uint16_t width, uint16_t height, TTF_Font* font, bool gameType,
            uint32_t flags = 0, uint16_t maxFPS = 0, uint16_t widthUnit = 10, uint16_t heightUnit = 10);

        void Start() override;
        void OnClose() override;
        void CheckCollision() override;
        void Update() override;

        void KeyPressed(const SDL_Keycode& key) override;
        void KeyReleased(const SDL_Keycode& key) override;

        void MousePressed(const SDL_MouseButtonEvent& mouse) override;
        void MouseReleased(const SDL_MouseButtonEvent& mouse) override;

        void Render(SDL_Renderer* renderer) override;

    public:
        std::string GetPlayer1Name() const;
        const std::string& GetPlayer2Name() const;

    private:

        std::string m_player1Name;
        std::optional<std::string> m_player2Name;

        SDL_Renderer* m_renderer;
        TTF_Font* m_font;

        uint16_t m_width;
        uint16_t m_height;

        bool m_gameType;

    };

}