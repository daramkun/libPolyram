#ifndef __POLYRAM_H__
#define __POLYRAM_H__

/* ==============================================================================================
*
*   libPolyram
*                          Copyright (C) 2015 Daramkun(Jin Jae-yeon)
*
*  -- The MIT License --
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
*  and associated documentation files (the "Software"), to deal in the Software without
*  restriction, including without limitation the rights to use, copy, modify, merge, publish, 
*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
*  Software is furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all copies or 
*  substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
============================================================================================== */

#include <iostream>
#include <exception>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <string>

#if ( defined ( _WINDOWS ) || defined ( _WIN32 ) || defined ( _WIN64 ) || defined ( WIN32 ) || defined ( WIN64 ) )
#	include <Windows.h>
#	include <wincodec.h>
#	include <atlconv.h>
#	pragma comment ( lib, "windowscodecs.lib" )
#	if WINAPI_FAMILY_PARTITION( WINAPI_PARTITION_DESKTOP ) || !defined ( WINAPI_FAMILY_DESKTOP_APP )
#		define PRPlatformMicrosoftWindowsNT		1
#		define PRPlatformMicrosoftWindowsRT		0
#		pragma comment ( lib, "winmm.lib" )
#	elif WINAPI_FAMILY_PARTITION ( WINAPI_FAMILY_PC_APP )
#		define PRPlatformMicrosoftWindowsNT		0
#		define PRPlatformMicrosoftWindowsRT		1
#		include <wrl.h>
#		include <wrl/client.h>
#	endif
#else
#	define PRPlatformMicrosoftWindowsNT			0
#	define PRPlatformMicrosoftWindowsRT			0
#endif
#if defined ( EMSCRIPTEN )
#	include <emscripten/emscripten.h>
#	include <emscripten/html5.h>
#	define PRPlatformWeb						1
#else
#	define PRPlatformWeb						0
#endif
#if defined ( __APPLE__ )
#	include <TargetConditionals.h>
#	define PRPlatformAppleOSX					TARGET_OS_MAC && !( TARGET_OS_IOS || TARGET_OS_SIMULATOR )
#	define PRPlatformAppleiOS					TARGET_OS_IOS || TARGET_OS_SIMULATOR
#	import <Foundation/Foundation.h>
#	include <sys/time.h>
#	if ( PRPlatformAppleOSX )
#		import <Cocoa/Cocoa.h>
#	else
#		import <UIKit/UIKit.h>
#	endif
#else
#	define PRPlatformAppleOSX					0
#	define PRPlatformAppleiOS					0
#endif
#if defined ( __ANDROID__ )
#	include <jni.h>
#	include <sys/time.h>
#	include <android/api-level.h>
#	include <android/native_activity.h>
#	include <android/native_window.h>
#	include <android/input.h>
#	include <android/window.h>
#	include <android/configuration.h>
#	include <android/asset_manager.h>
#	include <android/obb.h>
#	include <android/looper.h>
#	include <android/keycodes.h>
#	include <android/sensor.h>
#	include <android/storage_manager.h>
#	include <android/log.h>
#	include "android_native_app_glue/android_native_app_glue.h"

struct engine {
	struct android_app* app;

	ASensorManager* sensorManager;
	const ASensor* accelerometerSensor;
	ASensorEventQueue* sensorEventQueue;

	int animating;
	int32_t width;
	int32_t height;

	void * state;
};

#	define PRPlatformGoogleAndroid				1
#else
#	define PRPlatformGoogleAndroid				0
#endif
#if ( defined ( __unix__ ) || defined ( __linux__ ) ) && !defined ( __ANDROID__ )
#	include <sys/time.h>
#	include <X11/X.h>
#	include <X11/Xlib.h>
#	define PRPlatformUNIX						1
#else
#	define PRPlatformUNIX						0
#endif
#define PRPlatformMicrosoftWindowsFamily		( PRPlatformMicrosoftWindowsNT || PRPlatformMicrosoftWindowsRT )
#define PRPlatformAppleFamily					( PRPlatformAppleOSX || PRPlatformAppleiOS )
#define PRPlatformUNIXFamily					( PRPlatformUNIX || PRPlatformGoogleAndroid )
#define PRPlatformDesktops						( PRPlatformMicrosoftWindowsNT || PRPlatformAppleOSX || PRPlatformUNIX )
#define PRPlatformMobiles						( PRPlatformMicrosoftWindowsRT || PRPlatformAppleiOS || PRPlatformGoogleAndroid )

#if defined ( POLYRAM_D3D9 )
#	if ( !PRPlatformMicrosoftWindowsNT )
#		error Direct3D9 is for Windows NT only in this framework.
#	endif
#	include <d3d9.h>
#	pragma comment ( lib, "d3d9.lib" )
#endif
#if defined ( POLYRAM_D3D11 )
#	if ( !PRPlatformMicrosoftWindowsFamily )
#		error Direct3D11 is for Windows Family only.
#	endif
#	include <d3dcommon.h>
#	include <d3d11.h>
#	include <dxgi.h>
#	if defined ( NTDDI_WIN8)
#		include <d3d11_1.h>
#	endif
#	if defined ( NTDDI_WINBLUE )
#		include <d3d11_2.h>
#		include <dxgi1_2.h>
#	endif
#	if defined ( NTDDI_WIN10 )
#		include <d3d11_3.h>
#		include <dxgi1_3.h>
#	endif
#	pragma comment ( lib, "d3d11.lib" )
#	pragma comment ( lib, "dxgi.lib" )
#	pragma comment ( lib, "dxguid.lib" )
#endif
#if defined ( POLYRAM_D3D12 )
#	if ( !PRPlatformMicrosoftWindowsFamily )
#		error Direct3D12 is for Windows Family only.
#	endif
#	if !defined ( NTDDI_WIN10 )
#		error You cannot build for Direct3D 12 because your build target is not Windows 10 or higher.
#	endif
#	include <d3dcommon.h>
#	include <d3d12.h>
#	include <dxgi.h>
#	include <dxgi1_4.h>
#	pragma comment ( lib, "d3d12.lib" )
#	pragma comment ( lib, "dxgi.lib" )
#	pragma comment ( lib, "dxguid.lib" )
#endif
#if defined ( POLYRAM_OPENGL )
#	if PRPlatformDesktops && !defined ( GLEW_STATIC )
#		define GLEW_STATIC
#		if PRPlatformMicrosoftWindowsNT && defined ( POLYRAM_DLL_MODE )
#			undef GLEW_STATIC
#		endif
#	endif
#	if PRPlatformMicrosoftWindowsNT
#		include <GL/glew.h>
#		include <gl/gl.h>
#		include <gl/glu.h>
#		pragma comment ( lib, "OpenGL32.lib" )
#		pragma comment ( lib, "GLU32.lib" )
#	elif PRPlatformMicrosoftWindowsRT
#		error You cannot use OpenGL in Windows RT.
#	elif PRPlatformAppleOSX
#		include "./GL/glew.h"
#		import <OpenGL/OpenGL.h>
#	elif PRPlatformAppleiOS
#		import <OpenGLES/EAGL.h>
#		import <OpenGLES/EAGLDrawable.h>
#		import <OpenGLES/gltypes.h>
#		import <OpenGLES/ES1/gl.h>
#		import <OpenGLES/ES1/glext.h>
#		import <OpenGLES/ES2/gl.h>
#		import <OpenGLES/ES2/glext.h>
#		import <OpenGLES/ES3/gl.h>
#		import <OpenGLES/ES3/glext.h>
#		import <GLKit/GLKit.h>
#	elif PRPlatformUNIX
#		include <GL/glew.h>
#		include <GL/gl.h>
#		include <GL/glx.h>
#	elif PRPlatformGoogleAndroid
#		include <EGL/egl.h>
#		include <EGL/eglext.h>
#		include <EGL/eglplatform.h>
#		include <GLES2/gl2.h>
#		include <GLES2/gl2ext.h>
#		include <GLES2/gl2platform.h>
#	endif
#endif
#if defined ( POLYRAM_METAL )
#	if PRPlatformAppleFamily
#		import <Metal/Metal.h>
#	else
#		error You cannot use Metal API from this platform.
#	endif
#endif
#if defined ( POLYRAM_VULKAN )
/*
#	include <vulkan/vulkan.h>
#	include <vulkan/vk_sdk_platform.h>
#	if PRPlatformMicrosoftWindowsNT
#		pragma comment ( lib, "vulkan-1.lib" )
#	endif
*/
#endif

#if defined ( POLYRAM_DLL_MODE )
#	if LIBPOLYRAM_EXPORTS
#		define POLYRAMDECLSPEC	__declspec ( dllexport )
#	else
#		define POLYRAMDECLSPEC	__declspec ( dllimport )
#	endif
#else
#	define POLYRAMDECLSPEC
#endif

enum PRKeys {
	PRKeys_Unknown,
	PRKeys_Up, PRKeys_Down, PRKeys_Left, PRKeys_Right,
	PRKeys_Return, PRKeys_Space, PRKeys_Backspace, PRKeys_Tab, PRKeys_Escape, PRKeys_CapsLock,
	PRKeys_F1, PRKeys_F2, PRKeys_F3, PRKeys_F4, PRKeys_F5, PRKeys_F6, PRKeys_F7, PRKeys_F8, PRKeys_F9, PRKeys_F10, PRKeys_F11, PRKeys_F12,
	PRKeys_0, PRKeys_1, PRKeys_2, PRKeys_3, PRKeys_4, PRKeys_5, PRKeys_6, PRKeys_7, PRKeys_8, PRKeys_9,
	PRKeys_A, PRKeys_B, PRKeys_C, PRKeys_D, PRKeys_E, PRKeys_F, PRKeys_G, PRKeys_H, PRKeys_I, PRKeys_J, PRKeys_K, PRKeys_L, PRKeys_M,
	PRKeys_N, PRKeys_O, PRKeys_P, PRKeys_Q, PRKeys_R, PRKeys_S, PRKeys_T, PRKeys_U, PRKeys_V, PRKeys_W, PRKeys_X, PRKeys_Y, PRKeys_Z,
	PRKeys_Grave, PRKeys_Subtract, PRKeys_Equals, PRKeys_Backslash, PRKeys_LeftBracket, PRKeys_RightBracket, PRKeys_Semicolon,
	PRKeys_Quotation, PRKeys_Comma, PRKeys_Period, PRKeys_Slash,
	PRKeys_Insert, PRKeys_Delete, PRKeys_Home, PRKeys_End, PRKeys_PageUp, PRKeys_PageDown,
	PRKeys_LeftCtrl, PRKeys_LeftAlt, PRKeys_LeftShift, PRKeys_LeftWin,
	PRKeys_RightCtrl, PRKeys_RightAlt, PRKeys_RightShift, PRKeys_RightWin,
};

enum PRMouseButton { PRMouseButton_None = 0, PRMouseButton_Left = 1, PRMouseButton_Right = 2, PRMouseButton_Middle = 4, };

class POLYRAMDECLSPEC PRGame {
public:
	PRGame ();
	virtual ~PRGame ();

	virtual void onInitialize ();
	virtual void onDestroy ();
	virtual void onUpdate ( double dt );
	virtual void onDraw ( double dt );

	virtual void onKeyDown ( PRKeys key );
	virtual void onKeyUp ( PRKeys key );

	virtual void onMouseDown ( PRMouseButton button, int x, int y );
	virtual void onMouseUp ( PRMouseButton button, int x, int y );
	virtual void onMouseMove ( PRMouseButton button, int x, int y );
	virtual void onMouseWheel ( int wheelX, int wheelY );

	virtual void onTouchDown ( int pid, int x, int y );
	virtual void onTouchUp ( int pid, int x, int y );
	virtual void onTouchMove ( int pid, int x, int y );

	virtual void onActivated ();
	virtual void onDeactivated ();
	virtual void onResized ();

	virtual void onAccelerometer ( float x, float y, float z );
};

enum PRRendererType {
	PRRendererType_Unknown,
	PRRendererType_Direct3D9,
	PRRendererType_Direct3D11,
	PRRendererType_Direct3D12,
	PRRendererType_OpenGL1,
	PRRendererType_OpenGL2,
	PRRendererType_OpenGL3,
	PRRendererType_OpenGL4,
	PRRendererType_OpenGLES1,
	PRRendererType_OpenGLES2,
	PRRendererType_OpenGLES3,
	PRRendererType_WebGL1,
	PRRendererType_Vulkan1,
	PRRendererType_Metal1,
};

struct POLYRAMDECLSPEC PRVersion {
	int major, minor;
	PRVersion ( std::string & versionString );
	PRVersion ( int major, int minor = 0 );
};

class POLYRAMDECLSPEC PRGraphicsContext { public: virtual ~PRGraphicsContext (); };

class POLYRAMDECLSPEC PRApplication {
public:
	PRApplication ( PRGame * game, PRRendererType rendererType, int width, int height, std::string & title
#if PRPlatformGoogleAndroid
		, struct android_app * state
#endif
	);
	~PRApplication ();

public:
	PRGame * getScene ();
	PRGraphicsContext * getGraphicsContext ();
	void setGraphicsContext ( PRGraphicsContext * graphicsContext );
	void getClientSize ( int * width, int * height );

	bool setCursorPosition ( int x, int y );
	bool setCursorVisible ( bool visible );

	void run ();
	void exit ();

public:
	static PRApplication * sharedApplication ();

private:
	PRGame * m_game;
	PRGraphicsContext * m_graphicsContext;
#if PRPlatformMicrosoftWindowsRT || PRPlatformGoogleAndroid
	PRRendererType m_rendererType;
#endif

public:
#if PRPlatformMicrosoftWindowsNT
	HWND m_hWnd;
#elif PRPlatformMicrosoftWindowsRT
	Windows::UI::Core::CoreWindow^ window;
#elif PRPlatformAppleOSX
	NSWindow * window;
#elif PRPlatformUNIX
	Display * display;
	XVisualInfo * visualInfo;
	Colormap colorMap;
	Window window;
	unsigned width, height;
#elif PRPlatformGoogleAndroid
	struct engine engine;
#endif
};

#if defined ( POLYRAM_D3D9 )
class POLYRAMDECLSPEC PRGraphicsContext_Direct3D9 : public PRGraphicsContext {
public:
	PRGraphicsContext_Direct3D9 ( PRApplication * app );
	~PRGraphicsContext_Direct3D9 ();

public:
	IDirect3DDevice9 * d3dDevice;
};
#endif
#if defined ( POLYRAM_D3D11 )
class POLYRAMDECLSPEC PRGraphicsContext_Direct3D11 : public PRGraphicsContext {
public:
	PRGraphicsContext_Direct3D11 ( PRApplication * app );
	~PRGraphicsContext_Direct3D11 ();

public:
#if PRPlatformMicrosoftWindowsRT
	IDXGISwapChain1* dxgiSwapChain;
#else
	IDXGISwapChain* dxgiSwapChain;
#endif
	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* immediateContext;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
};
#endif
#if defined ( POLYRAM_D3D12 )
class POLYRAMDECLSPEC PRGraphicsContext_Direct3D12 : public PRGraphicsContext {
public:
	PRGraphicsContext_Direct3D12 ( PRApplication * app );
	~PRGraphicsContext_Direct3D12 ();

public:
	void Synchronization ();

public:
#ifdef _DEBUG
	ID3D12Debug * debugLayer;
#else
	void * d3d12_debugLayer_dummy;
#endif
	IDXGISwapChain3* dxgiSwapChain;
	ID3D12Device* d3dDevice;
	ID3D12CommandQueue* commandQueue;
	ID3D12DescriptorHeap* descriptorHeap;
	unsigned descriptorHandleIncrementSize;
	ID3D12Resource* renderTargets [ 2 ];
	unsigned frameIndex;
	ID3D12CommandAllocator* commandAllocator;
	ID3D12RootSignature* rootSignature;
	ID3D12Fence* fence;
	HANDLE fenceEvent;
	unsigned fenceValue;
};
#endif
#if defined ( POLYRAM_OPENGL )
class POLYRAMDECLSPEC PRGraphicsContext_OpenGL : public PRGraphicsContext {
public:
	PRGraphicsContext_OpenGL ( PRApplication * app, PRRendererType rendererType );
	~PRGraphicsContext_OpenGL ();

public:
	void makeCurrent ();
	void swapBuffers ();

public:
#if PRPlatformMicrosoftWindowsNT
	HDC hDC;
	HGLRC glContext;
#elif PRPlatformAppleOSX
	NSOpenGLContext * glContext;
#elif PRPlatformAppleiOS
	EAGLContext * glContext;
#elif PRPlatformUNIX
	GLXContext glContext;
#elif PRPlatformGoogleAndroid
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
#endif
};
#endif
#if defined ( POLYRAM_METAL )
class POLYRAMDECLSPEC PRGraphicsContext_Metal : public PRGraphicsContext {
public:
	PRGraphicsContext_Metal ( PRApplication * app );
	~PRGraphicsContext_Metal ();

public:
	id<MTLDevice> device;
	id<MTLLibrary> library;
	id<MTLCommandQueue> commandQueue;
	id<MTLCommandBuffer> commandBuffer;
};
#endif
#if defined ( POLYRAM_VULKAN )
/*class PRGraphicsContext_Vulkan : public PRGraphicsContext {
public:
	PRGraphicsContext_Vulkan ( PRApplication * app );
	~PRGraphicsContext_Vulkan ();

public:
	VkInstance instance;
	VkDevice device;
	VkQueue queue;

	VkSwapchainKHR swapChain;
};*/
#endif

#define GETGRAPHICSCONTEXT(x) auto graphicsContext = static_cast<x*> ( PRApplication::sharedApplication ()->getGraphicsContext () )

struct PRVector2;
struct PRVector3;
struct PRVector4;
struct PRQuaternion;
struct PRMatrix;

struct POLYRAMDECLSPEC PRVector2 {
public:
	float x, y;

public:
	PRVector2 ();
	PRVector2 ( float v );
	PRVector2 ( float x, float y );

public:
	void lengthSquared ( float * result );
	void length ( float * result );
	void normalize ( PRVector2 * result );

	float lengthSquared ();
	float length ();
	PRVector2 normalize ();

public:
	static void lengthSquared ( const PRVector2 * v, float * result );
	static void length ( const PRVector2 * v, float * result );
	static void normalize ( const PRVector2 * v, PRVector2 * result );

	static float lengthSquared ( const PRVector2 & v );
	static float length ( const PRVector2 & v );
	static PRVector2 normalize ( const PRVector2 & v );

public:
	static void add ( const PRVector2 * v1, const PRVector2 * v2, PRVector2 * result );
	static void subtract ( const PRVector2 * v1, const PRVector2 * v2, PRVector2 * result );
	static void negate ( const PRVector2 * v1, PRVector2 * result );
	static void multiply ( const PRVector2 * v1, const PRVector2 * v2, PRVector2 * result );
	static void multiply ( const PRVector2 * v1, float v2, PRVector2 * result );
	static void multiply ( float v1, const PRVector2 * v2, PRVector2 * result );
	static void divide ( const PRVector2 * v1, const PRVector2 * v2, PRVector2 * result );
	static void divide ( const PRVector2 * v1, float v2, PRVector2 * result );

	static void dot ( const PRVector2 * v1, const PRVector2 * v2, float * result );
	static void dot ( const PRVector2 * v1, float v2, float * result );
	static void cross ( const PRVector2 * v1, const PRVector2 * v2, PRVector2 * result );

	static PRVector2 add ( const PRVector2 & v1, const PRVector2 & v2 );
	static PRVector2 subtract ( const PRVector2 & v1, const PRVector2 & v2 );
	static PRVector2 negate ( const PRVector2 & v1 );
	static PRVector2 multiply ( const PRVector2 & v1, const PRVector2 & v2 );
	static PRVector2 multiply ( const PRVector2 & v1, float v2 );
	static PRVector2 multiply ( float v1, const PRVector2 & v2 );
	static PRVector2 divide ( const PRVector2 & v1, const PRVector2 & v2 );
	static PRVector2 divide ( const PRVector2 & v1, float v2 );

	static float dot ( const PRVector2 & v1, const PRVector2 & v2 );
	static float dot ( const PRVector2 & v1, float v2 );
	static PRVector2 cross ( const PRVector2 & v1, const PRVector2 & v2 );

public:
	static void transform ( const PRVector2 * pos, const PRMatrix * mat, PRVector2 * result );
	static void transformNormal ( const PRVector2 * nor, const PRMatrix * mat, PRVector2 * result );

	static PRVector2 transform ( const PRVector2 & pos, const PRMatrix & mat );
	static PRVector2 transformNormal ( const PRVector2 & nor, const PRMatrix & mat );
};

POLYRAMDECLSPEC PRVector2 operator+ ( const PRVector2 & v1, const PRVector2 & v2 );
POLYRAMDECLSPEC PRVector2 operator- ( const PRVector2 & v1, const PRVector2 & v2 );
POLYRAMDECLSPEC PRVector2 operator- ( const PRVector2 & v1 );
POLYRAMDECLSPEC PRVector2 operator* ( const PRVector2 & v1, const PRVector2 & v2 );
POLYRAMDECLSPEC PRVector2 operator* ( const PRVector2 & v1, float v2 );
POLYRAMDECLSPEC PRVector2 operator* ( float v1, const PRVector2 & v2 );
POLYRAMDECLSPEC PRVector2 operator/ ( const PRVector2 & v1, const PRVector2 & v2 );
POLYRAMDECLSPEC PRVector2 operator/ ( const PRVector2 & v1, float v2 );
POLYRAMDECLSPEC bool operator== ( const PRVector2 & v1, const PRVector2 & v2 );

struct POLYRAMDECLSPEC PRVector3 {
public:
	float x, y, z;

public:
	PRVector3 ();
	PRVector3 ( float v );
	PRVector3 ( float x, float y, float z );
	PRVector3 ( const PRVector2 & v, float z );

public:
	void lengthSquared ( float * result );
	void length ( float * result );
	void normalize ( PRVector3 * result );

	float lengthSquared ();
	float length ();
	PRVector3 normalize ();

public:
	static void lengthSquared ( const PRVector3 * v, float * result );
	static void length ( const PRVector3 * v, float * result );
	static void normalize ( const PRVector3 * v, PRVector3 * result );

	static float lengthSquared ( const PRVector3 & v );
	static float length ( const PRVector3 & v );
	static PRVector3 normalize ( const PRVector3 & v );

public:
	static void add ( const PRVector3 * v1, const PRVector3 * v2, PRVector3 * result );
	static void subtract ( const PRVector3 * v1, const PRVector3 * v2, PRVector3 * result );
	static void negate ( const PRVector3 * v1, PRVector3 * result );
	static void multiply ( const PRVector3 * v1, const PRVector3 * v2, PRVector3 * result );
	static void multiply ( const PRVector3 * v1, float v2, PRVector3 * result );
	static void multiply ( float v1, const PRVector3 * v2, PRVector3 * result );
	static void divide ( const PRVector3 * v1, const PRVector3 * v2, PRVector3 * result );
	static void divide ( const PRVector3 * v1, float v2, PRVector3 * result );

	static void dot ( const PRVector3 * v1, const PRVector3 * v2, float * result );
	static void dot ( const PRVector3 * v1, float v2, float * result );
	static void cross ( const PRVector3 * v1, const PRVector3 * v2, PRVector3 * result );

	static PRVector3 add ( const PRVector3 & v1, const PRVector3 & v2 );
	static PRVector3 subtract ( const PRVector3 & v1, const PRVector3 & v2 );
	static PRVector3 negate ( const PRVector3 & v1 );
	static PRVector3 multiply ( const PRVector3 & v1, const PRVector3 & v2 );
	static PRVector3 multiply ( const PRVector3 & v1, float v2 );
	static PRVector3 multiply ( float v1, const PRVector3 & v2 );
	static PRVector3 divide ( const PRVector3 & v1, const PRVector3 & v2 );
	static PRVector3 divide ( const PRVector3 & v1, float v2 );

	static float dot ( const PRVector3 & v1, const PRVector3 & v2 );
	static float dot ( const PRVector3 & v1, float v2 );
	static PRVector3 cross ( const PRVector3 & v1, const PRVector3 & v2 );

public:
	static void transform ( const PRVector2 * pos, const PRMatrix * mat, PRVector3 * result );
	static void transform ( const PRVector3 * pos, const PRMatrix * mat, PRVector3 * result );
	static void transform ( const PRVector3 * pos, const PRQuaternion * q, PRVector3 * result );
	static void transformNormal ( const PRVector2 * nor, const PRMatrix * mat, PRVector3 * result );
	static void transformNormal ( const PRVector3 * nor, const PRMatrix * mat, PRVector3 * result );

	static PRVector3 transform ( const PRVector2 & pos, const PRMatrix & mat );
	static PRVector3 transform ( const PRVector3 & pos, const PRMatrix & mat );
	static PRVector3 transform ( const PRVector3 & pos, const PRQuaternion & q );
	static PRVector3 transformNormal ( const PRVector2 & nor, const PRMatrix & mat );
	static PRVector3 transformNormal ( const PRVector3 & nor, const PRMatrix & mat );
};

POLYRAMDECLSPEC PRVector3 operator+ ( const PRVector3 & v1, const PRVector3 & v2 );
POLYRAMDECLSPEC PRVector3 operator- ( const PRVector3 & v1, const PRVector3 & v2 );
POLYRAMDECLSPEC PRVector3 operator- ( const PRVector3 & v1 );
POLYRAMDECLSPEC PRVector3 operator* ( const PRVector3 & v1, const PRVector3 & v2 );
POLYRAMDECLSPEC PRVector3 operator* ( const PRVector3 & v1, float v2 );
POLYRAMDECLSPEC PRVector3 operator* ( float v1, const PRVector3 & v2 );
POLYRAMDECLSPEC PRVector3 operator/ ( const PRVector3 & v1, const PRVector3 & v2 );
POLYRAMDECLSPEC PRVector3 operator/ ( const PRVector3 & v1, float v2 );
POLYRAMDECLSPEC bool operator== ( const PRVector3 & v1, const PRVector3 & v2 );

struct POLYRAMDECLSPEC PRVector4 {
public:
	float x, y, z, w;

public:
	PRVector4 ();
	PRVector4 ( float v );
	PRVector4 ( float x, float y, float z, float w );
	PRVector4 ( const PRVector2 & v, float z, float w );
	PRVector4 ( const PRVector3 & v, float w );
	PRVector4 ( const PRQuaternion & q );

public:
	void lengthSquared ( float * result );
	void length ( float * result );
	void normalize ( PRVector4 * result );

	float lengthSquared ();
	float length ();
	PRVector4 normalize ();

public:
	static void lengthSquared ( const PRVector4 * v, float * result );
	static void length ( const PRVector4 * v, float * result );
	static void normalize ( const PRVector4 * v, PRVector4 * result );

	static float lengthSquared ( const PRVector4 & v );
	static float length ( const PRVector4 & v );
	static PRVector4 normalize ( const PRVector4 & v );

public:
	static void add ( const PRVector4 * v1, const PRVector4 * v2, PRVector4 * result );
	static void subtract ( const PRVector4 * v1, const PRVector4 * v2, PRVector4 * result );
	static void negate ( const PRVector4 * v1, PRVector4 * result );
	static void multiply ( const PRVector4 * v1, const PRVector4 * v2, PRVector4 * result );
	static void multiply ( const PRVector4 * v1, float v2, PRVector4 * result );
	static void multiply ( float v1, const PRVector4 * v2, PRVector4 * result );
	static void divide ( const PRVector4 * v1, const PRVector4 * v2, PRVector4 * result );
	static void divide ( const PRVector4 * v1, float v2, PRVector4 * result );

	static void dot ( const PRVector4 * v1, const PRVector4 * v2, float * result );
	static void dot ( const PRVector4 * v1, float v2, float * result );

	static PRVector4 add ( const PRVector4 & v1, const PRVector4 & v2 );
	static PRVector4 subtract ( const PRVector4 & v1, const PRVector4 & v2 );
	static PRVector4 negate ( const PRVector4 & v1 );
	static PRVector4 multiply ( const PRVector4 & v1, const PRVector4 & v2 );
	static PRVector4 multiply ( const PRVector4 & v1, float v2 );
	static PRVector4 multiply ( float v1, const PRVector4 & v2 );
	static PRVector4 divide ( const PRVector4 & v1, const PRVector4 & v2 );
	static PRVector4 divide ( const PRVector4 & v1, float v2 );

	static float dot ( const PRVector4 & v1, const PRVector4 & v2 );
	static float dot ( const PRVector4 & v1, float v2 );

public:
	static void transform ( const PRVector2 * pos, const PRMatrix * mat, PRVector4 * result );
	static void transform ( const PRVector3 * pos, const PRMatrix * mat, PRVector4 * result );
	static void transform ( const PRVector4 * pos, const PRMatrix * mat, PRVector4 * result );

	static PRVector4 transform ( const PRVector2 & pos, const PRMatrix & mat );
	static PRVector4 transform ( const PRVector3 & pos, const PRMatrix & mat );
	static PRVector4 transform ( const PRVector4 & pos, const PRMatrix & mat );
};

POLYRAMDECLSPEC PRVector4 operator+ ( const PRVector4 & v1, const PRVector4 & v2 );
POLYRAMDECLSPEC PRVector4 operator- ( const PRVector4 & v1, const PRVector4 & v2 );
POLYRAMDECLSPEC PRVector4 operator- ( const PRVector4 & v1 );
POLYRAMDECLSPEC PRVector4 operator* ( const PRVector4 & v1, const PRVector4 & v2 );
POLYRAMDECLSPEC PRVector4 operator* ( const PRVector4 & v1, float v2 );
POLYRAMDECLSPEC PRVector4 operator* ( float v1, const PRVector4 & v2 );
POLYRAMDECLSPEC PRVector4 operator/ ( const PRVector4 & v1, const PRVector4 & v2 );
POLYRAMDECLSPEC PRVector4 operator/ ( const PRVector4 & v1, float v2 );
POLYRAMDECLSPEC bool operator== ( const PRVector4 & v1, const PRVector4 & v2 );

struct POLYRAMDECLSPEC PRQuaternion {
public:
	float x, y, z, w;

public:
	PRQuaternion ();
	PRQuaternion ( float v );
	PRQuaternion ( float x, float y, float z, float w );
	PRQuaternion ( const PRVector2 & v, float z, float w );
	PRQuaternion ( const PRVector3 & v, float w );
	PRQuaternion ( const PRVector4 & v );
	PRQuaternion ( float yaw, float pitch, float roll );
	PRQuaternion ( const PRMatrix & m );

public:
	void lengthSquared ( float * result );
	void length ( float * result );
	void normalize ( PRQuaternion * result );
	void invert ( PRQuaternion * result );

	float lengthSquared ();
	float length ();
	PRQuaternion normalize ();
	PRQuaternion invert ();

public:
	static void lengthSquared ( const PRQuaternion * v, float * result );
	static void length ( const PRQuaternion * v, float * result );
	static void normalize ( const PRQuaternion * v, PRQuaternion * result );
	static void invert ( const PRQuaternion * v, PRQuaternion * result );

	static float lengthSquared ( const PRQuaternion & v );
	static float length ( const PRQuaternion & v );
	static PRQuaternion normalize ( const PRQuaternion & v );
	static PRQuaternion invert ( const PRQuaternion & v );

public:
	static void add ( const PRQuaternion * v1, const PRQuaternion * v2, PRQuaternion * result );
	static void subtract ( const PRQuaternion * v1, const PRQuaternion * v2, PRQuaternion * result );
	static void negate ( const PRQuaternion * v1, PRQuaternion * result );
	static void multiply ( const PRQuaternion * v1, const PRQuaternion * v2, PRQuaternion * result );
	static void multiply ( const PRQuaternion * v1, float v2, PRQuaternion * result );
	static void multiply ( float v1, const PRQuaternion * v2, PRQuaternion * result );
	static void divide ( const PRQuaternion * v1, const PRQuaternion * v2, PRQuaternion * result );
	static void divide ( const PRQuaternion * v1, float v2, PRQuaternion * result );

	static void dot ( const PRQuaternion * v1, const PRQuaternion * v2, float * result );
	static void dot ( const PRQuaternion * v1, float v2, float * result );

	static PRQuaternion add ( const PRQuaternion & v1, const PRQuaternion & v2 );
	static PRQuaternion subtract ( const PRQuaternion & v1, const PRQuaternion & v2 );
	static PRQuaternion negate ( const PRQuaternion & v1 );
	static PRQuaternion multiply ( const PRQuaternion & v1, const PRQuaternion & v2 );
	static PRQuaternion multiply ( const PRQuaternion & v1, float v2 );
	static PRQuaternion multiply ( float v1, const PRQuaternion & v2 );
	static PRQuaternion divide ( const PRQuaternion & v1, const PRQuaternion & v2 );
	static PRQuaternion divide ( const PRQuaternion & v1, float v2 );

	static float dot ( const PRQuaternion & v1, const PRQuaternion & v2 );
	static float dot ( const PRQuaternion & v1, float v2 );
};

POLYRAMDECLSPEC PRQuaternion operator+ ( const PRQuaternion & v1, const PRQuaternion & v2 );
POLYRAMDECLSPEC PRQuaternion operator- ( const PRQuaternion & v1, const PRQuaternion & v2 );
POLYRAMDECLSPEC PRQuaternion operator- ( const PRQuaternion & v1 );
POLYRAMDECLSPEC PRQuaternion operator* ( const PRQuaternion & v1, const PRQuaternion & v2 );
POLYRAMDECLSPEC PRQuaternion operator* ( const PRQuaternion & v1, float v2 );
POLYRAMDECLSPEC PRQuaternion operator* ( float v1, const PRQuaternion & v2 );
POLYRAMDECLSPEC PRQuaternion operator/ ( const PRQuaternion & v1, const PRQuaternion & v2 );
POLYRAMDECLSPEC PRQuaternion operator/ ( const PRQuaternion & v1, float v2 );
POLYRAMDECLSPEC bool operator== ( const PRQuaternion & v1, const PRQuaternion & v2 );

struct POLYRAMDECLSPEC PRMatrix {
public:
	float _11, _12, _13, _14,
		_21, _22, _23, _24,
		_31, _32, _33, _34,
		_41, _42, _43, _44;

public:
	PRMatrix ();
	PRMatrix ( float v );
	PRMatrix ( float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44 );
	PRMatrix ( PRVector4 & c1, PRVector4 & c2, PRVector4 & c3, PRVector4 & c4 );
	PRMatrix ( PRQuaternion & q );

public:
	void invert ( PRMatrix * result );
	void transpose ( PRMatrix * result );
	void determinant ( float * result );

	PRMatrix invert ();
	PRMatrix transpose ();
	float determinant ();

public:
	static void invert ( const PRMatrix * m, PRMatrix * result );
	static PRMatrix invert ( const PRMatrix & m );
	static void transpose ( const PRMatrix * m, PRMatrix * result );
	static PRMatrix transpose ( const PRMatrix & m );
	static void determinant ( const PRMatrix * m, float * result );
	static float determinant ( const PRMatrix & m );

public:
	static void add ( const PRMatrix * v1, const PRMatrix * v2, PRMatrix * result );
	static void subtract ( const PRMatrix * v1, const PRMatrix * v2, PRMatrix * result );
	static void negate ( const PRMatrix * v1, PRMatrix * result );
	static void multiply ( const PRMatrix * v1, const PRMatrix * v2, PRMatrix * result );
	static void multiply ( const PRMatrix * v1, float v2, PRMatrix * result );
	static void multiply ( float v1, const PRMatrix * v2, PRMatrix * result );
	static void divide ( const PRMatrix * v1, const PRMatrix * v2, PRMatrix * result );
	static void divide ( const PRMatrix * v1, float v2, PRMatrix * result );

	static PRMatrix add ( const PRMatrix & v1, const PRMatrix & v2 );
	static PRMatrix subtract ( const PRMatrix & v1, const PRMatrix & v2 );
	static PRMatrix negate ( const PRMatrix & v1 );
	static PRMatrix multiply ( const PRMatrix & v1, const PRMatrix & v2 );
	static PRMatrix multiply ( const PRMatrix & v1, float v2 );
	static PRMatrix multiply ( float v1, const PRMatrix & v2 );
	static PRMatrix divide ( const PRMatrix & v1, const PRMatrix & v2 );
	static PRMatrix divide ( const PRMatrix & v1, float v2 );

public:
	static void createTranslate ( const PRVector3 * v, PRMatrix * result );
	static void createScale ( const PRVector3 * v, PRMatrix * result );
	static void createRotationX ( float r, PRMatrix * result );
	static void createRotationY ( float r, PRMatrix * result );
	static void createRotationZ ( float r, PRMatrix * result );

	static PRMatrix createTranslate ( const PRVector3 & v );
	static PRMatrix createScale ( const PRVector3 & v );
	static PRMatrix createRotationX ( float r );
	static PRMatrix createRotationY ( float r );
	static PRMatrix createRotationZ ( float r );

public:
	static void createLookAtLH ( const PRVector3 * position, const PRVector3 * target, const PRVector3 * upVector, PRMatrix * result );
	static void createLookAtRH ( const PRVector3 * position, const PRVector3 * target, const PRVector3 * upVector, PRMatrix * result );

	static PRMatrix createLookAtLH ( const PRVector3 & position, const PRVector3 & target, const PRVector3 & upVector );
	static PRMatrix createLookAtRH ( const PRVector3 & position, const PRVector3 & target, const PRVector3 & upVector );

public:
	static void createOrthographicLH ( float w, float h, float zn, float zf, PRMatrix * result );
	static void createOrthographicRH ( float w, float h, float zn, float zf, PRMatrix * result );
	static void createOrthographicOffCenterLH ( float l, float r, float b, float t, float zn, float zf, PRMatrix * result );
	static void createOrthographicOffCenterRH ( float l, float r, float b, float t, float zn, float zf, PRMatrix * result );
	static void createPerspectiveLH ( float w, float h, float zn, float zf, PRMatrix * result );
	static void createPerspectiveRH ( float w, float h, float zn, float zf, PRMatrix * result );
	static void createPerspectiveOffCenterLH ( float l, float r, float b, float t, float zn, float zf, PRMatrix * result );
	static void createPerspectiveOffCenterRH ( float l, float r, float b, float t, float zn, float zf, PRMatrix * result );
	static void createPerspectiveFieldOfViewLH ( float fov, float aspect, float zn, float zf, PRMatrix * result );
	static void createPerspectiveFieldOfViewRH ( float fov, float aspect, float zn, float zf, PRMatrix * result );

	static PRMatrix createOrthographicLH ( float w, float h, float zn, float zf );
	static PRMatrix createOrthographicRH ( float w, float h, float zn, float zf );
	static PRMatrix createOrthographicOffCenterLH ( float l, float r, float b, float t, float zn, float zf );
	static PRMatrix createOrthographicOffCenterRH ( float l, float r, float b, float t, float zn, float zf );
	static PRMatrix createPerspectiveLH ( float w, float h, float zn, float zf );
	static PRMatrix createPerspectiveRH ( float w, float h, float zn, float zf );
	static PRMatrix createPerspectiveOffCenterLH ( float l, float r, float b, float t, float zn, float zf );
	static PRMatrix createPerspectiveOffCenterRH ( float l, float r, float b, float t, float zn, float zf );
	static PRMatrix createPerspectiveFieldOfViewLH ( float fov, float aspect, float zn, float zf );
	static PRMatrix createPerspectiveFieldOfViewRH ( float fov, float aspect, float zn, float zf );

public:
	static void createBillboard ( const PRVector3 * objPos, const PRVector3 * camPos, const PRVector3 * camUpVec,
		const PRVector3 * camForwardVec, PRMatrix * result );
};

POLYRAMDECLSPEC PRMatrix operator+ ( const PRMatrix & v1, const PRMatrix & v2 );
POLYRAMDECLSPEC PRMatrix operator- ( const PRMatrix & v1, const PRMatrix & v2 );
POLYRAMDECLSPEC PRMatrix operator- ( const PRMatrix & v1 );
POLYRAMDECLSPEC PRMatrix operator* ( const PRMatrix & v1, const PRMatrix & v2 );
POLYRAMDECLSPEC PRMatrix operator* ( const PRMatrix & v1, float v2 );
POLYRAMDECLSPEC PRMatrix operator* ( float v1, const PRMatrix & v2 );
POLYRAMDECLSPEC PRMatrix operator/ ( const PRMatrix & v1, const PRMatrix & v2 );
POLYRAMDECLSPEC PRMatrix operator/ ( const PRMatrix & v1, float v2 );
POLYRAMDECLSPEC bool operator== ( const PRMatrix & v1, const PRMatrix & v2 );

class POLYRAMDECLSPEC PRImageLoader {
public:
	PRImageLoader ( std::string & filename );
	~PRImageLoader ();

public:
	unsigned getWidth ();
	unsigned getHeight ();

	const void* getData ();

private:
	void * m_data;
	unsigned m_width, m_height;
};

class POLYRAMDECLSPEC PRDataLoader {
public:
	PRDataLoader ( std::string & filename );
	~PRDataLoader ();

public:
	const void* getData ();
	unsigned getDataSize ();

private:
	void * m_data;
	unsigned m_dataSize;
};

enum PRModelType { PRModelType_Box, PRModelType_Rectangle, PRModelType_Sphere, PRModelType_Circle, PRModelType_Grid, PRModelType_Guide, };

enum {
	PRModelProperty_Position = 0,
	PRModelProperty_Normal = 1 << 0,
	PRModelProperty_TexCoord = 1 << 1,
	PRModelProperty_Diffuse = 1 << 2,
};
typedef int PRModelProperty;

enum PRModelTexCoord { PRModelTexCoord_UV, PRModelTexCoord_ST };

class POLYRAMDECLSPEC PRModelGenerator {
public:
	PRModelGenerator ( PRModelType modelType, PRModelProperty properties,
		PRModelTexCoord tcs = PRModelTexCoord_UV, const PRVector3 * scale = nullptr );
	// This constructor only support OBJ file format with XYZ, Normal, UV and Triangle faces format.
	PRModelGenerator ( std::string & filename,
		PRModelTexCoord tcs = PRModelTexCoord_UV, const PRVector3 * scale = nullptr );
	~PRModelGenerator ();

public:
	PRModelProperty getProperties ();
	const void* getData ();
	unsigned getDataSize ();

private:
	PRModelProperty m_properties;
	void * m_data;
	unsigned m_dataSize;
};

#define SAFE_RELEASE(x)			if ( x ) x->Release (); x = nullptr;
#define SAFE_DELETE(x)			if ( x ) delete x; x = nullptr;
#define SAFE_DELETE_ARRAY(x)	if ( x ) delete [] ( char * ) x; x = nullptr;

#define PR_Epsilon				1.19209290E-07F
#define PR_NaN					NAN;
#define PR_PositiveInfinite		HUGE_VALF
#define PR_NegativeInfinite		-HUGE_VALF
#define PR_PI					3.1415926536f
#define PR_PIover2				1.5707963268f
#define PR_PIover4				0.7853981634f
#define PR_2PI					6.2831853072f
#define PR_E					2.7182818285f
#define PR_Log10E				0.4342944819f
#define PR_Log2E				1.4426950409f

#define PRMin( x, y )			( ( x > y ) ? y : x )
#define PRMax( x, y )			( ( x > y ) ? x : y )
#define PRPow2( x )				( x * x )
#define PRPow3( x )				( x * x * x )
#define PRToDegree( x )			( x * 180 / PR_PI )
#define PRToRadian( x )			( x * PR_PI / 180 )

#define PRIsEquals( v1, v2 )	( ( v1 == v2 ) ? ( true ) : ( fabs ( v1 - v2 ) < PR_Epsilon ) )
POLYRAMDECLSPEC PRVector3 PRCalculateNormal ( const PRVector3 & v1, const PRVector3 & v2, const PRVector3 & v3 );

POLYRAMDECLSPEC double PRGetCurrentSecond ();
POLYRAMDECLSPEC void PRPrintLog ( const char * format, ... );

#if PRPlatformMicrosoftWindowsNT
#	define MAIN_FUNC_ATTR 
#	define MAIN_FUNC_RTTP int
#	define MAIN_FUNC_NAME WINAPI WinMain
#	define MAIN_FUNC_ARGS HINSTANCE, HINSTANCE, LPSTR lpszCmdLine, int
#elif PRPlatformMicrosoftWindowsRT
#	define MAIN_FUNC_ATTR [Platform::MTAThread]
#	define MAIN_FUNC_RTTP int
#	define MAIN_FUNC_NAME main
#	define MAIN_FUNC_ARGS Platform::Array<Platform::String^>^ args
#elif PRPlatformAppleFamily || PRPlatformUNIX
#	define MAIN_FUNC_ATTR 
#	define MAIN_FUNC_RTTP int
#	define MAIN_FUNC_NAME main
#	define MAIN_FUNC_ARGS int argc, char ** argv
#elif PRPlatformGoogleAndroid
#	define MAIN_FUNC_ATTR
#	define MAIN_FUNC_RTTP void
#	define MAIN_FUNC_NAME android_main
#	define MAIN_FUNC_ARGS struct android_app* state
#endif

#endif