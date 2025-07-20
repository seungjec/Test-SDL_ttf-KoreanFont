/*
* SDL3 한글 출력 및 콘솔 한글 출력
*
* 1. 프로젝트 > 속성 > 구성 속성 > C/C++ > 명령줄 > /utf-8 추가
* 2. 윈도우 콘솔에서 한글 출력을 위한 설정 : SetConsoleOutputCP(CP_UTF8);
* 3. 도구 > 옵션 > 환경 > 문서 > 특정 인코딩을 사용하여 파일 저장 : 유니코드(서명 없는 UTF-8) - 코드 페이지 65001
*
* SDL_Log, printf 사용시 한글 출력
* SDL Window 및 Title에서 한글 출력
*
*/

#include "Game.h"
#include <Windows.h>

int main(int argc, char* argv[])
{
    // 윈도우 콘솔에서 한글 출력을 위해 인코딩을 UTF-8로 설정함
    SetConsoleOutputCP(CP_UTF8);

    Game game;
    game.Run();
    return 0;
}