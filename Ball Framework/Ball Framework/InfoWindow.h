#include "Game.h"
#include <regex> 

namespace BallFramework
{

    class InfoWindow :
        public Game
    {
    public:
        InfoWindow(const std::string& title, uint16_t width, uint16_t height, TTF_Font* font, uint8_t playersNum,
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
        const std::vector<std::string>& GetPlayersNames() const;
        const bool& GetValidInput() const;

    private:
        void WriteText(const SDL_Keycode& key);

    private:
        std::string m_inputText;

        std::vector<std::string>m_playersNames;
        uint8_t m_playersNumber;

        const std::regex m_codeValidation;

        SDL_Color m_textColor = Colors::white;
        SDL_Renderer* m_renderer;

        SDL_Texture* m_textTexture;
        SDL_Texture* m_dialogTexture;

        TTF_Font* m_font;

        uint16_t m_width;
        uint16_t m_height;

        bool m_validInput;
        bool m_validName;

        class Dialog {

        public:
            std::string GetDialog();
            void OtherPlayer();

        private:
            int md_playerIndex = 1;
            std::string md_dialog1 = "Set Player";
            std::string md_currentPlayer = std::to_string(md_playerIndex);
            std::string md_dialog2 = "'s name:";
        } m_dialog;
    };

}