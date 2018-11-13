#include <seed/directx11>
#include <seed/window>

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Window window;
	DirectX11 graphics;

	window.Initalize("test window", float2(1280.f, 720.f));
	graphics.initialize(window.getHwnd<void*>(), window.getSize());

	graphics.createRenderTarget(RenderTargetID::Default, DescFormat::BackBuffer, window.getSize());
	graphics.createDepthStencil(DepthStencilID::Default, window.getSize());
	graphics.createViewPort(ViewPortID::Default, window.getSize());

	while (window.Run())
	{
		graphics.clearRenderTarget({ RenderTargetID::Default }, color(.2f, .4f, .8f, 1.f));
		graphics.clearDepthStencil({ DepthStencilID::Default });
		graphics.setRenderTargetAndDepthStencil({ RenderTargetID::Default }, DepthStencilID::Default);
		graphics.setViewPort({ ViewPortID::Default });

		graphics.present();
	}

	return 0;
}