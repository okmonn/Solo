#include "../GameSource/Game/Game.h"

// �G���g���[�|�C���g
#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
#endif
{
	Game::Get().Run();

	return 0;
}