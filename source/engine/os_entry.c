#if OS_WINDOWS

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
			window.width = LOWORD(lParam);
			window.height = HIWORD(lParam);
			glViewport(0, 0, window.width, window.height);
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

intern f64
win32_get_current_time() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER current_time_value;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&current_time_value);
    return (f64)current_time_value.QuadPart / frequency.QuadPart;
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
	window.should_close = false;
	window.title = str("Voyage");
	window.width = 640;
	window.height = 480;
	window.screen_width = GetSystemMetrics(SM_CXSCREEN);
	window.screen_height = GetSystemMetrics(SM_CYSCREEN);
	window.x = (window.screen_width - window.width) / 2;
	window.y = (window.screen_height - window.height) / 2;
	window.zoom = 0.1;
	window.clear_color = v3(0, 0, 0);

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

    window.handle = CreateWindowEx(0, wc.lpszClassName, window.title.data, WS_OVERLAPPEDWINDOW | WS_EX_TOPMOST, window.x, window.y, window.width, window.height, 0, 0, hInstance, NULL);
	assert(window.handle, "CreateWindowEx failed.");
	window.device = GetDC(window.handle);

	win32_load_opengl(nShowCmd);

	ShowWindow(window.handle, nShowCmd);
	ShowCursor(TRUE);

	static_arena = new_arena(MEGABYTES(STATIC_ARENA_SIZE));
	temp_arena = new_arena(MEGABYTES(TEMP_ARENA_SIZE));

	gfx_init();
	gfx.projection = mat_ortho2d(-1, 1, -1, 1, -1, 1);

	// Clearing screen, so when the VOYAGE_ENTRY_PROC takes too long, the screen isn't weirdly colored.
	glClearColor(window.clear_color.x, window.clear_color.y, window.clear_color.z, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFinish();

	VOYAGE_ENTRY_PROC();
	
	time.last = win32_get_current_time();
	MSG msg;

    while (!window.should_close) {
		arena_clear(&temp_arena);

		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			window.should_close = true;

		// time
		{
			time.now = win32_get_current_time();
			time.delta = (f64)(time.now - time.last);
			time.last = time.now;
			
			time.seconds_counter += time.delta;
			time.frame_count += 1;
			if (time.seconds_counter >= 1.0) {
				time.fps = time.frame_count;
				time.seconds_counter = 0.0;
				time.frame_count = 0;
			}
		}

		VOYAGE_UPDATE_PROC();

		// Rendering
		glClearColor(window.clear_color.x, window.clear_color.y, window.clear_color.z, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		
		VOYAGE_RENDER_PROC();

		glFinish();

		// End of frame
		memcpy(input.keys_old, input.keys, sizeof(bool) * 256);
		memcpy(&input.controller_old, &input.controller, sizeof(Controller_Profile));

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