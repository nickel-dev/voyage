#if OS_WINDOWS

global struct Os_Windows {
    string title;
    i32 width, height;
    i32 x, y;
	bool should_close;
    HWND handle;
	HDC device;
} window;

intern LRESULT WINAPI
window_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	u32 vk_code = (u32)wParam;

	switch (message)
	{
		case WM_QUIT:
		case WM_CLOSE:
		case WM_DESTROY:
			window.should_close = true;
			PostQuitMessage(0);
			break;
		
		case WM_SIZE:
			glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
			break;
		
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			if (vk_code == VK_ESCAPE)
				window.should_close = true;
			break;
		
		default:
			break;
	}
	
	return DefWindowProc(hwnd, message, wParam, lParam);
}

intern void
win32_load_opengl(i32 show_code) {
	// Pixel format for OpenGL context
	PIXELFORMATDESCRIPTOR pfd = {0};
	pfd.nSize      = sizeof(pfd);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	
	i32 pf = ChoosePixelFormat(window.device, &pfd);
	SetPixelFormat(window.device, pf, &pfd);
	DescribePixelFormat(window.device, pf, sizeof(pfd), &pfd);
	
	// Create and laod OpenGL
	HGLRC ctx = wglCreateContext(window.device);
	wglMakeCurrent(window.device, ctx);

	#define X(n, r, p) n = (GL_##n*)wglGetProcAddress(#n);
	#include "third_party/ogl_api_funcs.h"
	#undef X
}

extern int WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
	WNDCLASSEXA wc = {
		.cbClsExtra = 0,
		.cbSize = sizeof(wc),
		.cbWndExtra = 0,
		.hbrBackground = (HBRUSH)NULL,
		.hCursor = LoadCursorA(0, IDC_ARROW),
		.hIcon = LoadIconA(0, IDI_APPLICATION),
		.hIconSm = wc.hIcon,
		.hInstance = hInstance,
		.lpfnWndProc = window_proc,
		.lpszClassName = "Win32WindowsClass",
		.lpszMenuName = "Win32WindowClassMenu",
		.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC
	};

    assert(RegisterClassExA(&wc), "");

    window.handle = CreateWindowEx(0, wc.lpszClassName, "Title", WS_OVERLAPPEDWINDOW | WS_EX_TOPMOST, 0, 0, 1600, 900, 0, 0, hInstance, NULL);
	assert(window.handle, "CreateWindowEx failed.");
	window.device = GetDC(window.handle);

	win32_load_opengl(nShowCmd);

	ShowWindow(window.handle, nShowCmd);
	ShowCursor(TRUE);

    window.should_close = false;
	MSG msg;

	static_arena = new_arena(MEGABYTES(STATIC_ARENA_SIZE));
	temp_arena = new_arena(MEGABYTES(TEMP_ARENA_SIZE));

	gfx.projection = mat_ortho2d(-2, 2, -2, 2, -0.1, 1);

	VOYAGE_ENTRY_PROC();

	gfx_init();
    while (!window.should_close) {
		arena_clear(&temp_arena);

		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			window.should_close = true;
		
		VOYAGE_UPDATE_PROC();

		glClearColor(0.1, 0.1, 0.1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		VOYAGE_RENDER_PROC();
		
		glFinish();

		SwapBuffers(window.device);
		UpdateWindow(window.handle);
	}
	
	VOYAGE_EXIT_PROC();

	arena_free(&temp_arena);
	arena_free(&static_arena);

	return (int)msg.wParam;
}

// We use the /SUBSYSTEM:CONSOLE, so we can have console IO
int main(int argc, char** argv) {
	return wWinMain(GetModuleHandle(NULL), NULL, (LPWSTR)GetCommandLineA(), SW_SHOWNORMAL);
}

#else
#error No entry point for current OS defined
#endif