#include "Func.h"
#include <iostream>
using namespace func;

#define WINDOW_X 640
#define WINDOW_Y 480

// �G���g���[�|�C���g
#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
#endif
{
	func::SetWindowSize(WINDOW_X, WINDOW_Y);
	func::Init();
	
	ChangeView(Vec3f(0, 10, -15), Vec3f(0, 10, 0), Vec3f(0, 1, 0));


	UINT n = 0;
	func::LoadImg(n, "img/avicii.png");
	UINT m = 0;
	func::LoadImg(m, "img/sample3.png");
	UINT w = 0;
	LoadWave(w, "wave/sample2.wav");
	UINT q = 0;
	LoadPMD(q, "Model/�����~�N.pmd");

	float a = 0.f;
	float b = 0.f;

	while (func::CheckMsg() && CheckKey(INPUT_ESCAPE) != true)
	{
		func::Set();
		//Draw(m, 0, 0);
		DrawPMD(q);

		if (TriggerKey(INPUT_RETURN))
		{
			DeletePMD(q);
		}
		else if (TriggerKey(INPUT_SPACE))
		{
			StopWave(w);
		}
		func::Do();
	}

	return 0;
}