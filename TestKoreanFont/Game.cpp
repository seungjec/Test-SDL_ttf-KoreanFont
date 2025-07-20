#include "Game.h"
#include <stdio.h>
#include <string>

Game::Game()
{
    auto error = Initialize();
    if (error)
        SDL_Log("Initialize error code : %d", error);
}

Game::~Game()
{
    Finalize();
}

void Game::Run()
{
    if (m_error != 0)
        return;

    while (m_isRunning && m_error == 0)
    {
        HandleEvent();
        Update();
        Render();
    }
}

int Game::Initialize()
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    TTF_Init();
    m_window = SDL_CreateWindow(TITLE, WINDOW_W, WINDOW_H, 0);
    if (m_window == nullptr)
    {
        m_error = 1;
        return m_error;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (m_renderer == nullptr)
    {
        SDL_DestroyWindow(m_window);
        m_error = 2;
        return m_error;
    }

    m_font = TTF_OpenFont("assets\\nanum-handwriting-flower-scent.ttf", 48);
    if (m_font == nullptr)
    {
        SDL_DestroyWindow(m_window);
        SDL_DestroyRenderer(m_renderer);
        m_error = 3;
        return m_error;
    }

    return 0;
}

void Game::Finalize()
{
    if (m_font != nullptr)
    {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }

    if (m_renderer != nullptr)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window != nullptr)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    TTF_Quit();
    SDL_Quit();
}

void Game::HandleEvent()
{
    while (SDL_PollEvent(&m_event))
    {
        switch (m_event.type)
        {
        case SDL_EVENT_QUIT:
            m_isRunning = false;
            break;

        case SDL_EVENT_KEY_DOWN:
            switch (m_event.key.key)
            {
            case SDLK_ESCAPE:
                m_isRunning = false;
                break;
            }
            break;
        }
    }
}

void Game::Update()
{
    if (m_Print_On)
    {
        SDL_Log("[%s] %s\n", "SDL_Log", m_text.c_str());
        printf("[%s]  %s\n", "printf", m_text.c_str());

        m_Print_On = false;
    }
}

void Game::Render()
{
    SDL_Color fg{ 255, 255, 255, 255 };
    SDL_Color bg{ 0, 0, 0, 255 };

    SDL_Surface* textSurface = TTF_RenderText_LCD_Wrapped(m_font, m_text.c_str(), m_text.size(), fg, bg, 0);
    SDL_FRect rect{ 5, 50, (float)textSurface->w, (float)textSurface->h };
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    SDL_DestroySurface(textSurface);

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderTexture(m_renderer, texture, NULL, &rect);
    SDL_RenderPresent(m_renderer);

    SDL_DestroyTexture(texture);
}
