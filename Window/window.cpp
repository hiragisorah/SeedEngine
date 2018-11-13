#include "window.hpp"

#define WIN32_LEAD_AND_MEAN
#include <Windows.h>
#include <unordered_map>

//static std::unordered_map<unsigned int, bool> _key_map;

static LRESULT __stdcall WndProc(HWND hwnd, UINT i_msg, WPARAM w_param, LPARAM l_param)
{
	switch (i_msg)
	{
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_ACTIVATEAPP:
	case WM_KEYDOWN:
		//_key_map[w_param] = true;
		break;
	case WM_KEYUP:
		//_key_map[w_param] = false;
		break;
	case WM_SYSKEYUP: break;
	default:
		return DefWindowProc(hwnd, i_msg, w_param, l_param);
	}
	return 0;
}

class seed::Window::Impl
{
public:
	Impl(void)
		: caption_("Window Title")
		, size_(math::float2(1280, 720))
		, hwnd_(nullptr)
		, hinstance_(nullptr)
	{}

public:
	const bool Initalize(const std::string & caption, const math::float2 & size)
	{
		caption_ = caption;
		size_ = size;

		{// ハンドル取得
			hinstance_ = GetModuleHandleA(nullptr);
		}

		{// ウィンドウクラスの登録
			WNDCLASSEX  wc;
			memset(&wc, 0, sizeof(wc));
			wc.cbSize = sizeof(wc);
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = WndProc;
			wc.hInstance = hinstance_;
			wc.hIcon = LoadIconA(nullptr, IDI_APPLICATION);
			wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
			wc.lpszClassName = getCaption().c_str();
			wc.hIconSm = LoadIconA(nullptr, IDI_APPLICATION);
			RegisterClassExA(&wc);
		}

		{// ウィンドウの大きさの再調整、中央配置計算
			RECT rc;
			rc.left = 0;
			rc.top = 0;
			rc.right = static_cast<long>(size_.x);
			rc.bottom = static_cast<long>(size_.y);

			AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, false, 0);

			int w = rc.right - rc.left;
			int h = rc.bottom - rc.top;

			RECT rc_desk;
			GetWindowRect(GetDesktopWindow(), &rc_desk);

			int x = rc_desk.right / 2 - w / 2;
			int y = rc_desk.bottom / 2 - h / 2;

			{// ウィンドウの生成、表示
				hwnd_ = CreateWindowExA(0, getCaption().c_str(), getCaption().c_str(), WS_OVERLAPPEDWINDOW,
					x, y, w, h, 0, 0, hinstance_, 0);

				ShowWindow(hwnd_, SW_SHOW);
			}
		}

		return true;
	}
	const bool Run(void)
	{
		return MessageLoop();
	}
	const bool Finalize(void)
	{
		return true;
	}

private:
	std::string caption_;
	math::float2 size_;
	HWND hwnd_;
	HINSTANCE hinstance_;

public:
	const math::float2 & getSize(void)
	{
		return size_;
	}
	const std::string & getCaption(void)
	{
		return caption_;
	}
	void * const getHwnd(void)
	{
		return hwnd_;
	}

private:
	const bool MessageLoop(void)
	{
		MSG msg = { 0 };
		memset(&msg, 0, sizeof(msg));

		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
			if (msg.message == WM_QUIT) return false;
		}
		return true;
	}
};

seed::Window::Window(void)
	: impl_(std::make_unique<Window::Impl>())
{
}

seed::Window::~Window(void)
{

}

const bool seed::Window::Initalize(const std::string & caption, const math::float2 & size)
{
	return impl_->Initalize(caption, size);
}

const bool seed::Window::Run(void)
{
	return impl_->Run();
}

const bool seed::Window::Finalize(void)
{
	return impl_->Finalize();
}

const std::string & seed::Window::getCaption(void)
{
	return impl_->getCaption();
}

const seed::math::float2 & seed::Window::getSize(void)
{
	return impl_->getSize();
}

void * const seed::Window::getHwnd(void)
{
	return impl_->getHwnd();
}
