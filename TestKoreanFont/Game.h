#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>

class Game
{
public:
    Game();
    ~Game();
    void Run();

private:
    int Initialize();
    void Finalize();
    void HandleEvent();
    void Update();
    void Render();

    const int WINDOW_W = 1400;
    const int WINDOW_H = 800;
    const char* TITLE = "SDL3 한글 출력";

    int m_error{};
    SDL_Window* m_window{};
    SDL_Renderer* m_renderer{};
    TTF_Font* m_font{};
    SDL_Event m_event{};

    bool m_isRunning = true;
    size_t m_count{};

    bool m_Print_On = true;
    std::string m_text = 
R"(나눔손글씨 꽃내음 폰트를 사용해봤습니다.
폰트가 정말 예쁘네요.

SDL3에서 한글을 표시하려면 다음과 같은 설정이 필요합니다.
- 컴파일 옵션에 /utf-8 추가
- 콘솔에 한글을 보려면 SetConsoleOutputCP(CP_UTF8);
- 유니코드(서명 없는 UTF-8)를 사용하여 파일 저장)";

};