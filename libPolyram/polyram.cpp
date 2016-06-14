#define _CRT_SECURE_NO_WARNINGS
#include "polyram.h"
#include <stdarg.h>
#include <regex>

PRGame::PRGame () { }
PRGame::~PRGame () { }
void PRGame::onInitialize () { }
void PRGame::onDestroy () { }
void PRGame::onUpdate ( double dt ) { }
void PRGame::onDraw ( double dt ) { }
void PRGame::onKeyDown ( PRKeys key ) { }
void PRGame::onKeyUp ( PRKeys key ) { }
void PRGame::onMouseDown ( PRMouseButton button, int x, int y ) { }
void PRGame::onMouseUp ( PRMouseButton button, int x, int y ) { }
void PRGame::onMouseMove ( PRMouseButton button, int x, int y ) { }
void PRGame::onMouseWheel ( int wheelX, int wheelY ) { }
void PRGame::onTouchDown ( int pid, int x, int y ) { }
void PRGame::onTouchUp ( int pid, int x, int y ) { }
void PRGame::onTouchMove ( int pid, int x, int y ) { }
void PRGame::onActivated () { }
void PRGame::onDeactivated () { }
void PRGame::onResized () { }
void PRGame::onAccelerometer ( float x, float y, float z ) { }

PRVersion::PRVersion ( std::string & versionString ) {
	std::smatch match;
	std::regex versionChecker ( "([0-9]+)[.]*([0-9]*)(.*)" );
	if ( std::regex_match ( versionString, match, versionChecker ) ) {
		major = atoi ( ( *( ++match.begin () ) ).str ().c_str () );
		if ( match.size () > 2 )
			minor = atoi ( ( *( ++++match.begin () ) ).str ().c_str () );
	}
}
PRVersion::PRVersion ( int _major, int _minor ) { major = _major; minor = _minor; }

PRGraphicsContext::~PRGraphicsContext () { }

PRApplication * g_sharedApplication;

PRKeys keyValueConvertTo ( int key ) {
#if !PRPlatformMicrosoftWindowsRT
	switch ( key )
#else
	switch ( ( Windows::System::VirtualKey ) key )
#endif
	{
#if PRPlatformMicrosoftWindowsNT
	case VK_UP: return PRKeys_Up; case VK_DOWN: return PRKeys_Down; case VK_LEFT: return PRKeys_Left; case VK_RIGHT: return PRKeys_Right;
	case VK_RETURN: return PRKeys_Return; case VK_SPACE: return PRKeys_Space; case VK_BACK: return PRKeys_Backspace;
	case VK_TAB: return PRKeys_Tab; case VK_ESCAPE: return PRKeys_Escape; case VK_CAPITAL: return PRKeys_CapsLock;
	case VK_F1: return PRKeys_F1; case VK_F2: return PRKeys_F2; case VK_F3: return PRKeys_F3; case VK_F4: return PRKeys_F4;
	case VK_F5: return PRKeys_F5; case VK_F6: return PRKeys_F6; case VK_F7: return PRKeys_F7; case VK_F8: return PRKeys_F8;
	case VK_F9: return PRKeys_F9; case VK_F10: return PRKeys_F10; case VK_F11: return PRKeys_F11; case VK_F12: return PRKeys_F12;
	case '0': return PRKeys_0; case '1': return PRKeys_1; case '2': return PRKeys_2; case '3': return PRKeys_3; case '4': return PRKeys_4;
	case '5': return PRKeys_5; case '6': return PRKeys_6; case '7': return PRKeys_7; case '8': return PRKeys_8; case '9': return PRKeys_9;
	case 'A': return PRKeys_A; case 'B': return PRKeys_B; case 'C': return PRKeys_C; case 'D': return PRKeys_D; case 'E': return PRKeys_E;
	case 'F': return PRKeys_F; case 'G': return PRKeys_G; case 'H': return PRKeys_H; case 'I': return PRKeys_I; case 'J': return PRKeys_J;
	case 'K': return PRKeys_K; case 'L': return PRKeys_L; case 'M': return PRKeys_M; case 'N': return PRKeys_N; case 'O': return PRKeys_O;
	case 'P': return PRKeys_P; case 'Q': return PRKeys_Q; case 'R': return PRKeys_R; case 'S': return PRKeys_S; case 'T': return PRKeys_T;
	case 'U': return PRKeys_U; case 'V': return PRKeys_V; case 'W': return PRKeys_W; case 'X': return PRKeys_X; case 'Y': return PRKeys_Y;
	case 'Z': return PRKeys_Z;
	case VK_OEM_3: return PRKeys_Grave; case VK_OEM_MINUS: return PRKeys_Subtract; case VK_OEM_PLUS: return PRKeys_Equals;
	case VK_OEM_5: return PRKeys_Backslash; case VK_OEM_4: return PRKeys_LeftBracket; case VK_OEM_6: return PRKeys_RightBracket;
	case VK_OEM_1: return PRKeys_Semicolon; case VK_OEM_7: return PRKeys_Quotation;
	case VK_OEM_COMMA: return PRKeys_Comma; case VK_OEM_PERIOD: return PRKeys_Period; case VK_OEM_2: return PRKeys_Slash;
	case VK_INSERT: return PRKeys_Insert; case VK_DELETE: return PRKeys_Delete; case VK_HOME: return PRKeys_Home; case VK_END: return PRKeys_End;
	case VK_PRIOR: return PRKeys_PageUp; case VK_NEXT: return PRKeys_PageDown;
	case VK_CONTROL: return GetKeyState ( VK_LCONTROL ) ? PRKeys_LeftCtrl : PRKeys_RightCtrl;
	case VK_MENU: return GetKeyState ( VK_LMENU ) ? PRKeys_LeftAlt : PRKeys_RightAlt;
	case VK_SHIFT: return GetKeyState ( VK_LSHIFT ) ? PRKeys_LeftShift : PRKeys_RightShift;
	case VK_LWIN: return PRKeys_LeftWin; case VK_RWIN: return PRKeys_RightWin;
	default: return PRKeys_Unknown;
#elif PRPlatformMicrosoftWindowsRT
		using namespace Windows::System;
	case VirtualKey::Left: return PRKeys_Left; case VirtualKey::Right: return PRKeys_Right;
	case VirtualKey::Up: return PRKeys_Up; case VirtualKey::Down: return PRKeys_Down;
	case VirtualKey::A: return PRKeys_A; case VirtualKey::B: return PRKeys_B; case VirtualKey::C: return PRKeys_C; case VirtualKey::D: return PRKeys_D;
	case VirtualKey::E: return PRKeys_E; case VirtualKey::F: return PRKeys_F; case VirtualKey::G: return PRKeys_G; case VirtualKey::H: return PRKeys_H;
	case VirtualKey::I: return PRKeys_I; case VirtualKey::J: return PRKeys_J; case VirtualKey::K: return PRKeys_K; case VirtualKey::L: return PRKeys_L;
	case VirtualKey::M: return PRKeys_M; case VirtualKey::N: return PRKeys_N; case VirtualKey::O: return PRKeys_O; case VirtualKey::P: return PRKeys_P;
	case VirtualKey::Q: return PRKeys_Q; case VirtualKey::R: return PRKeys_R; case VirtualKey::S: return PRKeys_S; case VirtualKey::T: return PRKeys_T;
	case VirtualKey::U: return PRKeys_U; case VirtualKey::V: return PRKeys_V; case VirtualKey::W: return PRKeys_W; case VirtualKey::X: return PRKeys_X;
	case VirtualKey::Y: return PRKeys_Y; case VirtualKey::Z: return PRKeys_Z;
	case VirtualKey::F1: return PRKeys_F1; case VirtualKey::F2: return PRKeys_F2; case VirtualKey::F3: return PRKeys_F3;
	case VirtualKey::F4: return PRKeys_F4; case VirtualKey::F5: return PRKeys_F5; case VirtualKey::F6: return PRKeys_F6;
	case VirtualKey::F7: return PRKeys_F7; case VirtualKey::F8: return PRKeys_F8; case VirtualKey::F9: return PRKeys_F9;
	case VirtualKey::F10: return PRKeys_F10; case VirtualKey::F11: return PRKeys_F11; case VirtualKey::F12: return PRKeys_F12;
	case VirtualKey::Number0: return PRKeys_0; case VirtualKey::Number1: return PRKeys_1; case VirtualKey::Number2: return PRKeys_2;
	case VirtualKey::Number3: return PRKeys_3; case VirtualKey::Number4: return PRKeys_4; case VirtualKey::Number5: return PRKeys_5;
	case VirtualKey::Number6: return PRKeys_6; case VirtualKey::Number7: return PRKeys_7; case VirtualKey::Number8: return PRKeys_8;
	case VirtualKey::Number9: return PRKeys_9;
	case VirtualKey::Back: return PRKeys_Backspace; case VirtualKey::Enter: return PRKeys_Return; case VirtualKey::Tab: return PRKeys_Tab;
	case VirtualKey::CapitalLock: return PRKeys_CapsLock; case VirtualKey::Escape: return PRKeys_Escape; case VirtualKey::Space: return PRKeys_Space;
	case VirtualKey::LeftControl: return PRKeys_LeftCtrl; case VirtualKey::RightControl: return PRKeys_RightCtrl;
	case VirtualKey::LeftMenu: return PRKeys_LeftAlt; case VirtualKey::RightMenu: return PRKeys_RightAlt;
	case VirtualKey::LeftShift: return PRKeys_LeftShift; case VirtualKey::RightShift: return PRKeys_RightShift;
	case VirtualKey::LeftWindows: return PRKeys_LeftWin; case VirtualKey::RightWindows: return PRKeys_RightWin;
	case VirtualKey::Insert: return PRKeys_Insert; case VirtualKey::Delete: return PRKeys_Delete; case VirtualKey::Home: return PRKeys_Home;
	case VirtualKey::End: return PRKeys_End; case VirtualKey::PageUp: return PRKeys_PageUp; case VirtualKey::PageDown: return PRKeys_PageDown;
	default:
		if ( key == 219 ) return PRKeys_LeftBracket; if ( key == 221 ) return PRKeys_RightBracket;
		if ( key == 220 ) return PRKeys_Backslash; if ( key == 191 ) return PRKeys_Slash;
		if ( key == 188 ) return PRKeys_Comma; if ( key == 190 ) return PRKeys_Period;
		if ( key == 189 ) return PRKeys_Subtract; if ( key == 187 ) return PRKeys_Equals;
		if ( key == 186 ) return PRKeys_Semicolon; if ( key == 192 ) return PRKeys_Grave;
		if ( key == 222 ) return PRKeys_Quotation;
		break;
#elif PRPlatformAppleFamily
	case 0x7E: return PRKeys_Up; case 0x7D: return PRKeys_Down; case 0x7B: return PRKeys_Left; case 0x7C: return PRKeys_Right;
	case 0x24: return PRKeys_Return; case 0x31: return PRKeys_Space; case 0x33: return PRKeys_Backspace;
	case 0x30: return PRKeys_Tab; case 0x35: return PRKeys_Escape;
	case 0x7A: return PRKeys_F1; case 0x78: return PRKeys_F2; case 0x63: return PRKeys_F3; case 0x76: return PRKeys_F4;
	case 0x60: return PRKeys_F5; case 0x61: return PRKeys_F6; case 0x62: return PRKeys_F7; case 0x64: return PRKeys_F8;
	case 0x65: return PRKeys_F9; case 0x6D: return PRKeys_F10; case 0x67: return PRKeys_F11; case 0x6F: return PRKeys_F12;
	case 0x1D: return PRKeys_0; case 0x12: return PRKeys_1; case 0x13: return PRKeys_2; case 0x14: return PRKeys_3; case 0x15: return PRKeys_4;
	case 0x17: return PRKeys_5; case 0x16: return PRKeys_6; case 0x1A: return PRKeys_7; case 0x1C: return PRKeys_8; case 0x19: return PRKeys_9;
	case 0x00: return PRKeys_A; case 0x0B: return PRKeys_B; case 0x08: return PRKeys_C; case 0x02: return PRKeys_D; case 0x0E: return PRKeys_E;
	case 0x03: return PRKeys_F; case 0x05: return PRKeys_G; case 0x04: return PRKeys_H; case 0x22: return PRKeys_I; case 0x26: return PRKeys_J;
	case 0x28: return PRKeys_K; case 0x25: return PRKeys_L; case 0x2E: return PRKeys_M; case 0x2D: return PRKeys_N; case 0x1F: return PRKeys_O;
	case 0x23: return PRKeys_P; case 0x0C: return PRKeys_Q; case 0x0F: return PRKeys_R; case 0x01: return PRKeys_S; case 0x11: return PRKeys_T;
	case 0x20: return PRKeys_U; case 0x09: return PRKeys_V; case 0x0D: return PRKeys_W; case 0x07: return PRKeys_X; case 0x10: return PRKeys_Y;
	case 0x06: return PRKeys_Z;
	case 0x32: return PRKeys_Grave; case 0x1B: return PRKeys_Subtract; case 0x18: return PRKeys_Equals;
	case 0x2A: return PRKeys_Backslash; case 0x21: return PRKeys_LeftBracket; case 0x1E: return PRKeys_RightBracket;
	case 0x29: return PRKeys_Semicolon; case 0x27: return PRKeys_Quotation;
	case 0x2B: return PRKeys_Comma; case 0x2F: return PRKeys_Period; case 0x2C: return PRKeys_Slash;
	case 0x72: return PRKeys_Insert; case 0x75: return PRKeys_Delete; case 0x73: return PRKeys_Home; case 0x77: return PRKeys_End;
	case 0x74: return PRKeys_PageUp; case 0x79: return PRKeys_PageDown;
	case 0x3B: return PRKeys_LeftCtrl; case 0x3E: return PRKeys_RightCtrl;
	case 0x3A: return PRKeys_LeftAlt; case 0x3D: return PRKeys_RightAlt;
	case 0x38: return PRKeys_LeftShift; case 0x3C: return PRKeys_RightShift;
	case 0x37: return PRKeys_LeftWin; case 0x36: return PRKeys_RightWin;
	default: return PRKeys_Unknown;
#elif PRPlatformUNIX
	case XK_Up: return PRKeys_Up; case XK_Down: return PRKeys_Down; case XK_Left: return PRKeys_Left; case XK_Right: return PRKeys_Right;
	case XK_Return: return PRKeys_Return; case XK_space: return PRKeys_Space; case XK_BackSpace: return PRKeys_Backspace;
	case XK_Tab: return PRKeys_Tab; case XK_Escape: return PRKeys_Escape;
	case XK_F1: return PRKeys_F1; case XK_F2: return PRKeys_F2; case XK_F3: return PRKeys_F3; case XK_F4: return PRKeys_F4;
	case XK_F5: return PRKeys_F5; case XK_F6: return PRKeys_F6; case XK_F7: return PRKeys_F7; case XK_F8: return PRKeys_F8;
	case XK_F9: return PRKeys_F9; case XK_F10: return PRKeys_F10; case XK_F11: return PRKeys_F11; case XK_F12: return PRKeys_F12;
	case XK_0: return PRKeys_0; case XK_1: return PRKeys_1; case XK_2: return PRKeys_2; case XK_3: return PRKeys_3; case XK_4: return PRKeys_4;
	case XK_5: return PRKeys_5; case XK_6: return PRKeys_6; case XK_7: return PRKeys_7; case XK_8: return PRKeys_8; case XK_9: return PRKeys_9;
	case XK_A: return PRKeys_A; case XK_B: return PRKeys_B; case XK_C: return PRKeys_C; case XK_D: return PRKeys_D; case XK_E: return PRKeys_E;
	case XK_F: return PRKeys_F; case XK_G: return PRKeys_G; case XK_H: return PRKeys_H; case XK_I: return PRKeys_I; case XK_J: return PRKeys_J;
	case XK_K: return PRKeys_K; case XK_L: return PRKeys_L; case XK_M: return PRKeys_M; case XK_N: return PRKeys_N; case XK_O: return PRKeys_O;
	case XK_P: return PRKeys_P; case XK_Q: return PRKeys_Q; case XK_R: return PRKeys_R; case XK_S: return PRKeys_S; case XK_T: return PRKeys_T;
	case XK_U: return PRKeys_U; case XK_V: return PRKeys_V; case XK_W: return PRKeys_W; case XK_X: return PRKeys_X; case XK_Y: return PRKeys_Y;
	case XK_Z: return PRKeys_Z;
	case XK_grave: return PRKeys_Grave; case XK_minus: return PRKeys_Subtract; case XK_equal: return PRKeys_Equals;
	case XK_backslash: return PRKeys_Backslash; case XK_bracketleft: return PRKeys_LeftBracket; case XK_bracketright: return PRKeys_RightBracket;
	case XK_semicolon: return PRKeys_Semicolon; case XK_apostrophe: return PRKeys_Quotation;
	case XK_comma: return PRKeys_Comma; case XK_period: return PRKeys_Period; case XK_slash: return PRKeys_Slash;
	case XK_Insert: return PRKeys_Insert; case XK_Delete: return PRKeys_Delete; case XK_Home: return PRKeys_Home; case XK_End: return PRKeys_End;
	case XK_Page_Up: return PRKeys_PageUp; case XK_Page_Down: return PRKeys_PageDown;
	case XK_Control_L: return PRKeys_LeftCtrl; case XK_Control_R: return PRKeys_RightCtrl;
	case XK_Alt_L: return PRKeys_LeftAlt; case XK_Alt_R: return PRKeys_RightAlt;
	case XK_Shift_L: return PRKeys_LeftShift; case XK_Shift_R: return PRKeys_RightShift;
	case XK_Super_L: return PRKeys_LeftWin; case XK_Super_R: return PRKeys_RightWin;
	default: PRKeys_Unknown;
#elif PRPlatformGoogleAndroid
	case AKEYCODE_DPAD_UP: return PRKeys_Up; case AKEYCODE_DPAD_DOWN: return PRKeys_Down; case AKEYCODE_DPAD_LEFT: return PRKeys_Left; case AKEYCODE_DPAD_RIGHT: return PRKeys_Right;
	case AKEYCODE_ENTER: return PRKeys_Return; case AKEYCODE_SPACE: return PRKeys_Space; case AKEYCODE_BACK: return PRKeys_Backspace;
	case AKEYCODE_TAB: return PRKeys_Tab; case AKEYCODE_ESCAPE: return PRKeys_Escape;
	case AKEYCODE_F1: return PRKeys_F1; case AKEYCODE_F2: return PRKeys_F2; case AKEYCODE_F3: return PRKeys_F3; case AKEYCODE_F4: return PRKeys_F4;
	case AKEYCODE_F5: return PRKeys_F5; case AKEYCODE_F6: return PRKeys_F6; case AKEYCODE_F7: return PRKeys_F7; case AKEYCODE_F8: return PRKeys_F8;
	case AKEYCODE_F9: return PRKeys_F9; case AKEYCODE_F10: return PRKeys_F10; case AKEYCODE_F11: return PRKeys_F11; case AKEYCODE_F12: return PRKeys_F12;
	case AKEYCODE_0: return PRKeys_0; case AKEYCODE_1: return PRKeys_1; case AKEYCODE_2: return PRKeys_2; case AKEYCODE_3: return PRKeys_3; case AKEYCODE_4: return PRKeys_4;
	case AKEYCODE_5: return PRKeys_5; case AKEYCODE_6: return PRKeys_6; case AKEYCODE_7: return PRKeys_7; case AKEYCODE_8: return PRKeys_8; case AKEYCODE_9: return PRKeys_9;
	case AKEYCODE_A: return PRKeys_A; case AKEYCODE_B: return PRKeys_B; case AKEYCODE_C: return PRKeys_C; case AKEYCODE_D: return PRKeys_D; case AKEYCODE_E: return PRKeys_E;
	case AKEYCODE_F: return PRKeys_F; case AKEYCODE_G: return PRKeys_G; case AKEYCODE_H: return PRKeys_H; case AKEYCODE_I: return PRKeys_I; case AKEYCODE_J: return PRKeys_J;
	case AKEYCODE_K: return PRKeys_K; case AKEYCODE_L: return PRKeys_L; case AKEYCODE_M: return PRKeys_M; case AKEYCODE_N: return PRKeys_N; case AKEYCODE_O: return PRKeys_O;
	case AKEYCODE_P: return PRKeys_P; case AKEYCODE_Q: return PRKeys_Q; case AKEYCODE_R: return PRKeys_R; case AKEYCODE_S: return PRKeys_S; case AKEYCODE_T: return PRKeys_T;
	case AKEYCODE_U: return PRKeys_U; case AKEYCODE_V: return PRKeys_V; case AKEYCODE_W: return PRKeys_W; case AKEYCODE_X: return PRKeys_X; case AKEYCODE_Y: return PRKeys_Y;
	case AKEYCODE_Z: return PRKeys_Z;
	case AKEYCODE_GRAVE: return PRKeys_Grave; case AKEYCODE_MINUS: return PRKeys_Subtract; case AKEYCODE_EQUALS: return PRKeys_Equals;
	case AKEYCODE_BACKSLASH: return PRKeys_Backslash; case AKEYCODE_LEFT_BRACKET: return PRKeys_LeftBracket; case AKEYCODE_RIGHT_BRACKET: return PRKeys_RightBracket;
	case AKEYCODE_SEMICOLON: return PRKeys_Semicolon; case AKEYCODE_APOSTROPHE: return PRKeys_Quotation;
	case AKEYCODE_COMMA: return PRKeys_Comma; case AKEYCODE_PERIOD: return PRKeys_Period; case AKEYCODE_SLASH: return PRKeys_Slash;
	case AKEYCODE_PAGE_UP: return PRKeys_PageUp; case AKEYCODE_PAGE_DOWN: return PRKeys_PageDown; case AKEYCODE_MOVE_HOME: return PRKeys_Home; case AKEYCODE_MOVE_END: return PRKeys_End;
	case AKEYCODE_CTRL_LEFT: return PRKeys_LeftCtrl; case AKEYCODE_CTRL_RIGHT: return PRKeys_RightCtrl;
	case AKEYCODE_ALT_LEFT: return PRKeys_LeftAlt; case AKEYCODE_ALT_RIGHT: return PRKeys_RightAlt;
	case AKEYCODE_SHIFT_LEFT: return PRKeys_LeftShift; case AKEYCODE_SHIFT_RIGHT: return PRKeys_RightShift;
	case AKEYCODE_META_LEFT: return PRKeys_LeftWin; case AKEYCODE_META_RIGHT: return PRKeys_RightWin;
	default: return PRKeys_Unknown;
#endif
	}
	return PRKeys_Unknown;
}

#if PRPlatformMicrosoftWindowsNT
int g_MouseButton;
#elif PRPlatformMicrosoftWindowsRT
namespace polyram {
	ref class PRWinRTFramework sealed : public Windows::ApplicationModel::Core::IFrameworkView {
	private:
		PRRendererType rendererType;

		bool m_windowClosed;
		bool m_windowVisible;

	internal:
		PRWinRTFramework ( PRRendererType rendererType ) {
			this->rendererType = rendererType;

			m_windowClosed = false;
			m_windowVisible = false;
		}

	public:
		virtual void Initialize ( Windows::ApplicationModel::Core::CoreApplicationView ^ appView ) {
			using namespace Windows::Foundation;
			using namespace Windows::ApplicationModel::Core;
			using namespace Windows::ApplicationModel::Activation;
			appView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^> ( this, &PRWinRTFramework::OnActivated );
		}

		virtual void SetWindow ( Windows::UI::Core::CoreWindow ^ window ) {
			PRApplication::sharedApplication ()->window = window;

			using namespace Windows::Foundation;
			using namespace Windows::UI::Core;
			window->VisibilityChanged += ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^> ( this, &PRWinRTFramework::OnVisibilityChanged );
			window->Closed += ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^> ( this, &PRWinRTFramework::OnWindowClosed );
			window->SizeChanged += ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^> ( this, &PRWinRTFramework::OnResized );
			window->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^> ( this, &PRWinRTFramework::OnKeyDown );
			window->KeyUp += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^> ( this, &PRWinRTFramework::OnKeyUp );
			window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^> ( this, &PRWinRTFramework::OnPointerPressed );
			window->PointerReleased += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^> ( this, &PRWinRTFramework::OnPointerReleased );
			window->PointerMoved += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^> ( this, &PRWinRTFramework::OnPointerMoved );
			window->PointerWheelChanged += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^> ( this, &PRWinRTFramework::OnPointerWheel );
		}

		virtual void Load ( Platform::String ^ entryPoint ) { }

		virtual void Run () {
			switch ( rendererType ) {
			case PRRendererType_Direct3D11:
				PRApplication::sharedApplication ()->setGraphicsContext ( new PRGraphicsContext_Direct3D11 ( PRApplication::sharedApplication () ) );
				break;
			case PRRendererType_Direct3D12:
				PRApplication::sharedApplication ()->setGraphicsContext ( new PRGraphicsContext_Direct3D12 ( PRApplication::sharedApplication () ) );
				break;
			default:
				throw std::runtime_error ( "Cannot use this renderer version in this platform." );
			}

			PRApplication::sharedApplication ()->getScene ()->onInitialize ();

			double elapsedTime, lastTime = PRGetCurrentSecond (), currentTime, calcFps = 0;
			while ( !m_windowClosed ) {
				if ( m_windowVisible ) {
					elapsedTime = ( currentTime = PRGetCurrentSecond () ) - lastTime;
					lastTime = currentTime;

					if ( PRApplication::sharedApplication ()->getScene () != nullptr ) {
						PRApplication::sharedApplication ()->getScene ()->onUpdate ( elapsedTime );
						PRApplication::sharedApplication ()->getScene ()->onDraw ( elapsedTime );
					}
				}

				PRApplication::sharedApplication ()->window->Dispatcher->ProcessEvents ( Windows::UI::Core::CoreProcessEventsOption::ProcessAllIfPresent );
			}
		}

		virtual void Uninitialize () { auto game = PRApplication::sharedApplication ()->getScene (); if ( game ) game->onDestroy (); }

	private:
		void OnActivated ( Windows::ApplicationModel::Core::CoreApplicationView^ CoreAppView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ Args ) {
			Windows::UI::Core::CoreWindow^ window = Windows::UI::Core::CoreWindow::GetForCurrentThread ();
			window->Activate ();
			m_windowClosed = false;
		}

	private:
		void OnVisibilityChanged ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ e ) { m_windowVisible = true; }
		void OnWindowClosed ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ e ) { m_windowClosed = true; }
		void OnResized ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ e )
		{
			if ( PRApplication::sharedApplication ()->getScene () ) PRApplication::sharedApplication ()->getScene ()->onResized ();
		}
		void OnKeyDown ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ e ) {
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onKeyDown ( keyValueConvertTo ( ( int ) e->VirtualKey ) );
		}
		void OnKeyUp ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ e ) {
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onKeyUp ( keyValueConvertTo ( ( int ) e->VirtualKey ) );
		}
		void OnPointerPressed ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e ) {
			if ( PRApplication::sharedApplication ()->getScene () ) {
				int mouseButton;
				if ( e->CurrentPoint->Properties->IsLeftButtonPressed ) mouseButton |= PRMouseButton_Left;
				else if ( e->CurrentPoint->Properties->IsRightButtonPressed ) mouseButton |= PRMouseButton_Right;
				else if ( e->CurrentPoint->Properties->IsMiddleButtonPressed ) mouseButton |= PRMouseButton_Middle;
				PRApplication::sharedApplication ()->getScene ()->onMouseDown ( ( PRMouseButton ) mouseButton,
					( int ) e->CurrentPoint->Position.X, ( int ) e->CurrentPoint->Position.Y );
			}
		}
		void OnPointerReleased ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e ) {
			if ( PRApplication::sharedApplication ()->getScene () ) {
				int mouseButton;
				if ( !e->CurrentPoint->Properties->IsLeftButtonPressed ) mouseButton |= PRMouseButton_Left;
				else if ( !e->CurrentPoint->Properties->IsRightButtonPressed ) mouseButton |= PRMouseButton_Right;
				else if ( !e->CurrentPoint->Properties->IsMiddleButtonPressed ) mouseButton |= PRMouseButton_Middle;
				PRApplication::sharedApplication ()->getScene ()->onMouseUp ( ( PRMouseButton ) mouseButton,
					( int ) e->CurrentPoint->Position.X, ( int ) e->CurrentPoint->Position.Y );
			}
		}
		void OnPointerMoved ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e ) {
			if ( PRApplication::sharedApplication ()->getScene () ) {
				int mouseButton = PRMouseButton_None;
				if ( e->CurrentPoint->Properties->IsLeftButtonPressed ) mouseButton |= PRMouseButton_Left;
				else if ( e->CurrentPoint->Properties->IsRightButtonPressed ) mouseButton |= PRMouseButton_Right;
				else if ( e->CurrentPoint->Properties->IsMiddleButtonPressed ) mouseButton |= PRMouseButton_Middle;
				PRApplication::sharedApplication ()->getScene ()->onMouseMove ( ( PRMouseButton ) mouseButton,
					( int ) e->CurrentPoint->Position.X, ( int ) e->CurrentPoint->Position.Y );
			}
		}

		void OnPointerWheel ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e ) {
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseWheel ( 0, e->CurrentPoint->Properties->MouseWheelDelta );
		}
	};

	ref class PRWinRTFrameworkView sealed : public Windows::ApplicationModel::Core::IFrameworkViewSource {
	private: PRRendererType rendererType;
	internal: PRWinRTFrameworkView ( PRRendererType rendererType ) { this->rendererType = rendererType; }
	public: virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView () { return ref new PRWinRTFramework ( rendererType ); }
	};
}
#elif PRPlatformAppleOSX
#define WINDOW_STYLE NSMiniaturizableWindowMask | NSClosableWindowMask | NSTitledWindowMask
int g_MouseButton;
int g_MouseX, g_MouseY;
#elif PRPlatformUNIX
int g_MouseButton;
int g_MouseX, g_MouseY;
#endif

PRApplication::PRApplication ( PRGame * game, PRRendererType rendererType, int width, int height, std::string & title
#if PRPlatformGoogleAndroid
	, struct android_app * state
#endif
) : m_game ( game ), m_graphicsContext ( nullptr ) {
	g_sharedApplication = this;
#if PRPlatformMicrosoftWindowsNT
	WNDCLASS wndClass = { 0, };
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hInstance = GetModuleHandle ( nullptr );
	wndClass.hIcon = LoadIcon ( nullptr, IDI_APPLICATION );
	wndClass.hCursor = LoadCursor ( nullptr, IDC_ARROW );
	wndClass.lpfnWndProc = static_cast<WNDPROC> ( [] ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) -> LRESULT {
		switch ( uMsg ) {
		case WM_KEYDOWN:
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onKeyDown ( keyValueConvertTo ( ( int ) wParam ) );
			break;
		case WM_KEYUP:
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onKeyUp ( keyValueConvertTo ( ( int ) wParam ) );
			break;

		case WM_LBUTTONDOWN:
			g_MouseButton |= PRMouseButton_Left;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseDown ( PRMouseButton_Left, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_RBUTTONDOWN:
			g_MouseButton |= PRMouseButton_Right;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseDown ( PRMouseButton_Right, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_MBUTTONDOWN:
			g_MouseButton |= PRMouseButton_Middle;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseDown ( PRMouseButton_Middle, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_LBUTTONUP:
			g_MouseButton &= PRMouseButton_Left;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseUp ( PRMouseButton_Left, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_RBUTTONUP:
			g_MouseButton &= PRMouseButton_Right;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseUp ( PRMouseButton_Right, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_MBUTTONUP:
			g_MouseButton &= PRMouseButton_Middle;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseUp ( PRMouseButton_Middle, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_MOUSEMOVE:
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseMove ( ( PRMouseButton ) g_MouseButton, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_MOUSEWHEEL:
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseWheel ( 0, ( int ) GET_WHEEL_DELTA_WPARAM ( wParam ) / WHEEL_DELTA );
			break;
		case WM_MOUSEHWHEEL:
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseWheel ( ( int ) GET_WHEEL_DELTA_WPARAM ( wParam ) / WHEEL_DELTA, 0 );
			break;

		case WM_ACTIVATE:
			if ( PRApplication::sharedApplication ()->getScene () ) {
				if ( wParam != WA_INACTIVE ) PRApplication::sharedApplication ()->getScene ()->onActivated ();
				else PRApplication::sharedApplication ()->getScene ()->onDeactivated ();
			}
			break;
		case WM_SIZE:
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onResized ();
			break;
		default: return DefWindowProc ( hWnd, uMsg, wParam, lParam );
		}
		return 0;
	} );
	wndClass.lpszClassName = TEXT ( "libPolyram" );
	if ( RegisterClass ( &wndClass ) == 0 )
		throw std::runtime_error ( "Failed register window class." );

	RECT adjust = { 0, 0, width, height };
	AdjustWindowRect ( &adjust, WS_OVERLAPPEDWINDOW, FALSE );
	int _width = adjust.right - adjust.left, _height = adjust.bottom - adjust.top;
	int x = GetSystemMetrics ( SM_CXSCREEN ) / 2 - _width / 2, y = GetSystemMetrics ( SM_CYSCREEN ) / 2 - _height / 2;

	USES_CONVERSION;

	m_hWnd = CreateWindow ( TEXT ( "libPolyram" ), A2W ( title.c_str () ),
		WS_OVERLAPPEDWINDOW, x, y, _width, _height, nullptr, nullptr, wndClass.hInstance, nullptr );
	if ( m_hWnd == 0 )
		throw std::runtime_error ( "Failed create window." );

	switch ( rendererType ) {
	case PRRendererType_Direct3D9: m_graphicsContext = new PRGraphicsContext_Direct3D9 ( this ); break;
	case PRRendererType_Direct3D11: m_graphicsContext = new PRGraphicsContext_Direct3D11 ( this ); break;
	case PRRendererType_Direct3D12: m_graphicsContext = new PRGraphicsContext_Direct3D12 ( this ); break;
	case PRRendererType_OpenGL1:
	case PRRendererType_OpenGL2:
	case PRRendererType_OpenGL3:
	case PRRendererType_OpenGL4: m_graphicsContext = new PRGraphicsContext_OpenGL ( this, rendererType ); break;
	//case PRRendererType_Vulkan1: m_graphicsContext = new PRGraphicsContext_Vulkan ( this ); break;
	default: throw std::runtime_error ( "Illegal Graphics Renderer." );
	}
#elif PRPlatformMicrosoftWindowsRT
	m_rendererType = rendererType;
#elif PRPlatformAppleOSX
	window = [ [ NSWindow alloc ] initWithContentRect:CGRectMake ( 0, 0, width, height ) styleMask : WINDOW_STYLE backing : NSBackingStoreBuffered defer : NO ];
	if ( window == nil )
		throw std::runtime_error ( "Failed create NSWindow." );
	window.title = [ NSString stringWithUTF8String : title ];
	[window center];
	[window makeKeyAndOrderFront : window];

	NSView * view = window.contentView;
	if ( view == nil )
		throw std::runtime_error ( "Failed to retrieve content view for window." );

	NSView * renegaderView = [ [ NSView alloc ] initWithFrame:CGRectMake ( 0, 0, width, height ) ];
	if ( renegaderView == nil )
		throw std::runtime_error ( "Failed create NSView." );
	window.contentView = renegaderView;
	view = nil;

	[window makeKeyWindow];

	switch ( rendererType ) {
	case PRRendererType_OpenGL1:
	case PRRendererType_OpenGL2:
	case PRRendererType_OpenGL3:
	case PRRendererType_OpenGL4: m_graphicsContext = new PRGraphicsContext_OpenGL ( this, rendererType ); break;
	case PRRendererType_Metal: m_graphicsContext = new PRGraphicsContext_Metal ( this ); break;
	default: throw std::runtime_error ( "Illegal Graphics Renderer." );
	}
#elif PRPlatformUNIX
	display = XOpenDisplay ( nullptr );
	if ( display == nullptr )
		throw std::runtime_error ( "Cannot connect to X server." );

	Window root = DefaultRootWindow ( display );

	GLint attr [] = {
		GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_STENCIL_SIZE, 8, GLX_DOUBLEBUFFER, true, GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR, None
	};
	visualInfo = glXChooseVisual ( display, 0, attr );
	if ( visualInfo == nullptr )
		throw std::runtime_error ( "No appropriate visual found." );

	colorMap = XCreateColormap ( display, root, visualInfo->visual, AllocNone );

	XSetWindowAttributes setWindowAttr = { 0, };
	setWindowAttr.colormap = colorMap;
	setWindowAttr.background_pixmap = None;
	setWindowAttr.border_pixel = 0;
	setWindowAttr.event_mask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask;

	window = XCreateWindow ( display, root, 0, 0, this->width = width, this->height = height, 0, visualInfo->depth, InputOutput,
		visualInfo->visual, CWColormap | CWEventMask, &setWindowAttr );
	if ( !window )
		throw std::runtime_error ( "Failed create window." );

	Atom wmDelete = XInternAtom ( display, "WM_DELETE_WINDOW", true );
	XSetWMProtocols ( display, window, &wmDelete, 1 );

	XStoreName ( display, window, "libPolyram" );
	XMapWindow ( display, window );

	switch ( rendererType ) {
	case PRRendererType_OpenGL1:
	case PRRendererType_OpenGL2:
	case PRRendererType_OpenGL3:
	case PRRendererType_OpenGL4: m_graphicsContext = new PRGraphicsContext_OpenGL ( this, rendererType ); break;
	default: throw std::runtime_error ( "Illegal Graphics Renderer." );
	}
#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid
	m_rendererType = rendererType;
	memset ( &this->engine, 0, sizeof ( this->engine ) );
	state->userData = &engine;
	state->onAppCmd = [] ( struct android_app* app, int32_t cmd ) {
		struct engine* engine = ( struct engine* )app->userData;
		switch ( cmd ) {
		case APP_CMD_SAVE_STATE:
			break;
		case APP_CMD_INIT_WINDOW:
			if ( engine->app->window != nullptr )
			{
				switch ( PRApplication::sharedApplication ()->m_rendererType ) {
				case PRRendererType_OpenGLES1:
				case PRRendererType_OpenGLES2:
				case PRRendererType_OpenGLES3:
					PRApplication::sharedApplication ()->m_graphicsContext =
						new PRGraphicsContext_OpenGL ( PRApplication::sharedApplication (), PRApplication::sharedApplication ()->m_rendererType );
					break;
				default: throw std::runtime_error ( "Illegal Graphics Renderer." );
				}
			}
			break;
		case APP_CMD_TERM_WINDOW:
			SAFE_DELETE ( PRApplication::sharedApplication ()->m_graphicsContext );
			break;
		case APP_CMD_GAINED_FOCUS:
			if ( PRApplication::sharedApplication ()->engine.accelerometerSensor != nullptr ) {
				ASensorEventQueue_enableSensor ( PRApplication::sharedApplication ()->engine.sensorEventQueue,
					PRApplication::sharedApplication ()->engine.accelerometerSensor );
				ASensorEventQueue_setEventRate ( PRApplication::sharedApplication ()->engine.sensorEventQueue,
					PRApplication::sharedApplication ()->engine.accelerometerSensor, ( 1000L / 60 ) * 1000 );
			}
			break;
		}
	};
	state->onInputEvent = [] ( struct android_app* app, AInputEvent* event ) -> int32_t {
		PRGame * scene = PRApplication::sharedApplication ()->getScene ();
		switch ( AInputEvent_getType ( event ) ) {
		case AINPUT_EVENT_TYPE_KEY:
			if ( scene ) {
				int32_t action = AKeyEvent_getAction ( event );
				int32_t keyCode = AKeyEvent_getKeyCode ( event );
				if ( action == AKEY_EVENT_ACTION_DOWN )
					scene->onKeyDown ( keyValueConvertTo ( keyCode ) );
				else if ( action == AKEY_EVENT_ACTION_UP )
					scene->onKeyUp ( keyValueConvertTo ( keyCode ) );
			}
			else return 0;
			return 1;
		case AINPUT_EVENT_TYPE_MOTION:
			if ( scene ) {
				int32_t action = AMotionEvent_getAction ( event );
				int32_t maskedAction = action & AMOTION_EVENT_ACTION_MASK;
				int32_t pind = ( action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK ) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
				int32_t pid = AMotionEvent_getPointerId ( event, pind );

				switch ( maskedAction ) {
				case AMOTION_EVENT_ACTION_DOWN:
					scene->onTouchDown ( pid, AMotionEvent_getX ( event, pind ), AMotionEvent_getY ( event, pind ) );
					break;
				case AMOTION_EVENT_ACTION_POINTER_DOWN:
					scene->onTouchDown ( pid, AMotionEvent_getX ( event, pind ), AMotionEvent_getY ( event, pind ) );
					break;
				case AMOTION_EVENT_ACTION_UP:
					scene->onTouchUp ( pid, AMotionEvent_getX ( event, pind ), AMotionEvent_getY ( event, pind ) );
					break;
				case AMOTION_EVENT_ACTION_POINTER_UP:
					scene->onTouchUp ( pid, AMotionEvent_getX ( event, pind ), AMotionEvent_getY ( event, pind ) );
					break;
				case AMOTION_EVENT_ACTION_MOVE:
					for ( int i = 0; i < AMotionEvent_getPointerCount ( event ); ++i ) {
						int32_t pid = AMotionEvent_getPointerId ( event, i );
						scene->onTouchMove ( pid, AMotionEvent_getX ( event, i ), AMotionEvent_getY ( event, i ) );
					}
					break;
				}
			}
			return 1;
		}
		return 0;
	};
	this->engine.app = state;

	this->engine.sensorManager = ASensorManager_getInstance ();
	this->engine.accelerometerSensor = ASensorManager_getDefaultSensor ( engine.sensorManager, ASENSOR_TYPE_ACCELEROMETER );
	this->engine.sensorEventQueue = ASensorManager_createEventQueue ( engine.sensorManager, state->looper, LOOPER_ID_USER, NULL, NULL );

	if ( state->savedState != NULL )
		engine.state = state->savedState;
#elif PRPlatformWeb

#endif
}

PRApplication::~PRApplication () {
	SAFE_DELETE ( m_graphicsContext );
#if PRPlatformMicrosoftWindowsNT
	DestroyWindow ( m_hWnd );
#elif PRPlatformMicrosoftWindowsRT

#elif PRPlatformAppleOSX
	window = nil;
#elif PRPlatformUNIX
	XDestroyWindow ( display, window );
	XFreeColormap ( display, colorMap );
	XCloseDisplay ( display );
#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid

#elif PRPlatformWeb

#endif
}

PRGame * PRApplication::getScene () { return m_game; }
PRGraphicsContext * PRApplication::getGraphicsContext () { return m_graphicsContext; }
void PRApplication::setGraphicsContext ( PRGraphicsContext * graphicsContext ) { m_graphicsContext = graphicsContext; }

void PRApplication::getClientSize ( int * width, int * height ) {
#if PRPlatformMicrosoftWindowsNT
	RECT rect;
	GetClientRect ( m_hWnd, &rect );
	if ( width ) *width = rect.right - rect.left;
	if ( height ) *height = rect.bottom - rect.top;
#elif PRPlatformMicrosoftWindowsRT
	if ( width ) *width = ( unsigned ) window->Bounds.Width;
	if ( height ) *height = ( unsigned ) window->Bounds.Height;
#elif PRPlatformAppleOSX
	if ( width ) *width = window.contentView.frame.size.width;
	if ( height ) *height = window.contentView.frame.size.height;
#elif PRPlatformUNIX
	if ( width ) *width = this->width;
	if ( height ) *height = this->height;
#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid
	if ( width ) *width = engine.width;
	if ( height ) *height = engine.height;
#elif PRPlatformWeb

#endif
}

bool PRApplication::setCursorPosition ( int x, int y ) {
#if PRPlatformMicrosoftWindowsNT
	POINT pos;
	ClientToScreen ( m_hWnd, &pos );
	SetCursorPos ( pos.x, pos.y );
	return true;
#elif PRPlatformMicrosoftWindowsRT

#elif PRPlatformAppleOSX
	CGDirectDisplayID displayID = ( CGDirectDisplayID ) [ [ [ [ NSScreen mainScreen ] deviceDescription ] objectForKey:@"NSScreenNumber"] intValue ];
	CGDisplayMoveCursorToPoint ( displayID, [ window convertRectToScreen : CGRectMake ( x, y, 0, 0 ) ].origin );
	return true;
#elif PRPlatformUNIX
	XMoveWindow ( display, window, x, y );
	XFlush ( display );
	return true;
#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid

#elif PRPlatformWeb

#endif
	return false;
}

bool PRApplication::setCursorVisible ( bool visible )
{
#if PRPlatformMicrosoftWindowsNT
	ShowCursor ( visible );
	return true;
#elif PRPlatformMicrosoftWindowsRT
	window->PointerCursor = visible ? ref new Windows::UI::Core::CoreCursor ( Windows::UI::Core::CoreCursorType::Arrow, 1 ) : nullptr;
	return true;
#elif PRPlatformAppleOSX
	if ( !visible ) [ NSCursor hide ];
	else [ NSCursor unhide ];
	return true;
#elif PRPlatformUNIX

#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid

#elif PRPlatformWeb

#endif
	return false;
}

void PRApplication::run () {
#if !PRPlatformMicrosoftWindowsRT
	double elapsedTime, lastTime = PRGetCurrentSecond (), currentTime;
#endif

#if PRPlatformMicrosoftWindowsNT
	ShowWindow ( m_hWnd, SW_SHOW );
	UpdateWindow ( m_hWnd );

	if ( m_game ) m_game->onInitialize ();

	MSG msg;
	while ( IsWindow ( m_hWnd ) ) {
		if ( PeekMessage ( &msg, NULL, 0, 0, PM_NOREMOVE ) ) {
			if ( !GetMessage ( &msg, NULL, 0, 0 ) )break;
			TranslateMessage ( &msg );
			DispatchMessage ( &msg );
		}
		else {
			elapsedTime = ( currentTime = PRGetCurrentSecond () ) - lastTime;
			lastTime = currentTime;

			if ( m_game != nullptr ) {
				m_game->onUpdate ( elapsedTime );
				m_game->onDraw ( elapsedTime );
			}

			Sleep ( 1 );
		}
	}
#elif PRPlatformMicrosoftWindowsRT
	Windows::ApplicationModel::Core::CoreApplication::Run ( ref new polyram::PRWinRTFrameworkView ( m_rendererType ) );
#elif PRPlatformAppleOSX
	window.isVisible = visible;

	if ( m_game ) m_game->onInitialize ();

	while ( window.isVisible ) {
		NSEvent * event = [ [ NSApplication sharedApplication ] nextEventMatchingMask:NSAnyEventMask untilDate : nil inMode : NSDefaultRunLoopMode dequeue : YES ];
		switch ( event.type ) {
		case NSKeyDown:
			if ( LqLauncher::getInstance ()->getScene () )
				LqLauncher::getInstance ()->getScene ()->onKeyDown ( keyValueConvertTo ( ( int ) event.keyCode ) );
			break;
		case NSKeyUp:
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onKeyUp ( keyValueConvertTo ( ( int ) event.keyCode ) );
			break;

		case NSLeftMouseDown:
			g_MouseButton |= PRMouseButton_Left;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseDown ( PRMouseButton_Left, g_MouseX, g_MouseY );
			break;
		case NSLeftMouseUp:
			g_MouseButton &= PRMouseButton_Left;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseUp ( PRMouseButton_Left, g_MouseX, g_MouseY );
			break;
		case NSRightMouseDown:
			g_MouseButton |= PRMouseButton_Right;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseDown ( PRMouseButton_Right, g_MouseX, g_MouseY );
			break;
		case NSRightMouseUp:
			g_MouseButton &= PRMouseButton_Right;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseUp ( PRMouseButton_Right, g_MouseX, g_MouseY );
			break;
		case NSOtherMouseDown:
			g_MouseButton |= PRMouseButton_Middle;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseDown ( PRMouseButton_Middle, g_MouseX, g_MouseY );
			break;
		case NSOtherMouseUp:
			g_MouseButton &= PRMouseButton_Middle;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseUp ( PRMouseButton_Middle, g_MouseX, g_MouseY );
			break;

		case NSMouseMoved:
			g_MouseX = ( int ) event.locationInWindow.x; g_MouseY = ( int ) event.locationInWindow.y;
			if ( PRApplication::sharedApplication ()->getScene () )
				PRApplication::sharedApplication ()->getScene ()->onMouseMove ( ( PRMouseButton ) g_MouseButton, g_MouseX, g_MouseY );
			break;

		default: break;
		}
		[ [ NSApplication sharedApplication ] sendEvent:event ];

		elapsedTime = ( currentTime = PRGetCurrentSecond () ) - lastTime;
		lastTime = currentTime;

		if ( m_game != nullptr ) {
			m_game->onUpdate ( elapsedTime );
			m_game->onDraw ( elapsedTime );
		}
	}
#elif PRPlatformUNIX
	if ( m_game ) m_game->onInitialize ();

	XEvent xev;
	bool loopflag = true;
	while ( loopflag ) {
		if ( XPending ( display ) ) {
			XNextEvent ( display, &xev );

			switch ( xev.type ) {
			case KeyPress:
				if ( PRApplication::sharedApplication ()->getScene () )
					PRApplication::sharedApplication ()->getScene ()->onKeyDown ( keyValueConvertTo ( xev.xkey.keycode ) );
				break;
			case KeyRelease:
				if ( PRApplication::sharedApplication ()->getScene () )
					PRApplication::sharedApplication ()->getScene ()->onKeyUp ( keyValueConvertTo ( xev.xkey.keycode ) );
				break;

			case ButtonPress:
				PRMouseButton button;
				switch ( xev.xbutton.window ) {
				case Button1: button = PRMouseButton_Left; break;
				case Button2: button = PRMouseButton_Right; break;
				case Button3: button = PRMouseButton_Middle; break;
				}

				g_MouseButton |= button;
				if ( PRApplication::sharedApplication ()->getScene () )
					PRApplication::sharedApplication ()->getScene ()->onMouseDown ( button, g_MouseX, g_MouseY );
				break;
			case ButtonRelease: {
				PRMouseButton button;
				switch ( xev.xbutton.window ) {
				case Button1: button = PRMouseButton_Left; break;
				case Button2: button = PRMouseButton_Right; break;
				case Button3: button = PRMouseButton_Middle; break;
				}

				g_MouseButton |= button;
				if ( PRApplication::sharedApplication ()->getScene () )
					PRApplication::sharedApplication ()->getScene ()->onMouseUp ( button, g_MouseX, g_MouseY );
			}
								break;
			case MotionNotify:
				g_MouseX = xev.xmotion.x; g_MouseY = xev.xmotion.x;
				if ( PRApplication::sharedApplication ()->getScene () )
					PRApplication::sharedApplication ()->getScene ()->onMouseMove ( ( PRMouseButton ) g_MouseButton, g_MouseX, g_MouseY );
				break;

			case ClientMessage: loopflag = false; break;
			}
		}

		elapsedTime = ( currentTime = PRGetCurrentSecond () ) - lastTime;
		lastTime = currentTime;

		if ( m_game != nullptr ) {
			m_game->onUpdate ( elapsedTime );
			m_game->onDraw ( elapsedTime );
		}
	}
#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid
	engine.animating = 1;
	while ( 1 ) {
		int ident;
		int events;
		struct android_poll_source* source;

		while ( ( ident = ALooper_pollAll ( engine.animating ? 0 : -1, NULL, &events, ( void** ) &source ) ) >= 0 ) {
			if ( source != nullptr )
				source->process ( this->engine.app, source );

			if ( ident == LOOPER_ID_USER ) {
				if ( engine.accelerometerSensor != nullptr ) {
					ASensorEvent event;
					while ( ASensorEventQueue_getEvents ( engine.sensorEventQueue, &event, 1 ) > 0 )
						if ( m_game ) m_game->onAccelerometer ( event.acceleration.x, event.acceleration.y, event.acceleration.z );
				}
			}

			if ( this->engine.app->destroyRequested != 0 ) {
				if ( m_game ) m_game->onDestroy ();
				SAFE_DELETE ( this->m_graphicsContext );
				return;
			}
		}

		if ( engine.animating ) {
			elapsedTime = ( currentTime = PRGetCurrentSecond () ) - lastTime;
			lastTime = currentTime;

			if ( m_game != nullptr ) {
				m_game->onUpdate ( elapsedTime );
				if ( this->m_graphicsContext == nullptr || ( ( PRGraphicsContext_OpenGL* ) this->m_graphicsContext )->display == nullptr )
					continue;
				m_game->onDraw ( elapsedTime );
			}
		}
	}
#elif PRPlatformWeb

#endif
	if ( m_game ) m_game->onDestroy ();
}

void PRApplication::exit () {
#if PRPlatformMicrosoftWindowsNT
	PostQuitMessage ( 0 );
#elif PRPlatformMicrosoftWindowsRT
	this->window->Close ();
#elif PRPlatformAppleOSX
	if ( window.isVisible )
		[window orderOut:window];
#elif PRPlatformAppleiOS

#elif PRPlatformUNIX
	XEvent xev;
	xev.type = ClientMessage;
	XSendEvent ( display, window, false, 0, &xev );
#elif PRPlatformGoogleAndroid
	ANativeActivity_finish ( engine.app->activity );
#endif
}

PRApplication * PRApplication::sharedApplication () { return g_sharedApplication; }

#if POLYRAM_D3D9
PRGraphicsContext_Direct3D9::PRGraphicsContext_Direct3D9 ( PRApplication * app ) {
	IDirect3D9 * d3d;
	if ( !( d3d = Direct3DCreate9 ( D3D_SDK_VERSION ) ) )
		throw std::runtime_error ( "Failed create Direct3D." );

	int windowWidth, windowHeight;
	app->getClientSize ( &windowWidth, &windowHeight );

	D3DPRESENT_PARAMETERS pp = { 0, };
	pp.BackBufferWidth = windowWidth;
	pp.BackBufferHeight = windowHeight;
	pp.BackBufferCount = 1;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.EnableAutoDepthStencil = true;
	pp.AutoDepthStencilFormat = D3DFMT_D24S8;
	pp.hDeviceWindow = app->m_hWnd;
	pp.Windowed = true;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	D3DCAPS9 caps;
	d3d->GetDeviceCaps ( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );
	if ( FAILED ( d3d->CreateDevice ( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, app->m_hWnd,
		caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &d3dDevice ) ) ) {
		d3dDevice = nullptr;
		d3d->Release ();
		d3d = nullptr;
		throw std::runtime_error ( "Failed create Direct3D Device." );
	}
}

PRGraphicsContext_Direct3D9::~PRGraphicsContext_Direct3D9 () {
	IDirect3D9 * d3dFactory = nullptr;
	if ( d3dDevice ) d3dDevice->GetDirect3D ( &d3dFactory );
	SAFE_RELEASE ( d3dDevice );
	SAFE_RELEASE ( d3dFactory );
}
#endif

#if POLYRAM_D3D11
PRGraphicsContext_Direct3D11::PRGraphicsContext_Direct3D11 ( PRApplication * app ) {
	int windowWidth, windowHeight;
	app->getClientSize ( &windowWidth, &windowHeight );

	auto flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT |
#if defined ( _DEBUG )
		D3D11_CREATE_DEVICE_DEBUG;
#else
		0;
#endif

#if PRPlatformMicrosoftWindowsNT
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0, };
	swapChainDesc.BufferDesc.Width = windowWidth;
	swapChainDesc.BufferDesc.Height = windowHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = app->m_hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_FEATURE_LEVEL featureLevel;
	if ( FAILED ( D3D11CreateDeviceAndSwapChain ( nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, flag,
		nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &dxgiSwapChain, &d3dDevice, &featureLevel, &immediateContext ) ) )
		throw std::runtime_error ( "Failed create Direct3D device and Swap Chain." );
#elif PRPlatformMicrosoftWindowsRT
	D3D_FEATURE_LEVEL featureLevel;
	if ( FAILED ( D3D11CreateDevice ( nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, flag, nullptr, 0, D3D11_SDK_VERSION,
		&d3dDevice, &featureLevel, &immediateContext ) ) )
		throw std::runtime_error ( "Failed create Direct3D device." );

	IDXGIDevice2 * dxgiDevice;
	d3dDevice->QueryInterface<IDXGIDevice2> ( &dxgiDevice );

	IDXGIAdapter * dxgiAdapter;
	if ( FAILED ( dxgiDevice->GetAdapter ( &dxgiAdapter ) ) )
		throw std::runtime_error ( "Cannot get IDXGIFactory." );

	IDXGIFactory2 * dxgiFactory;
	if ( FAILED ( dxgiAdapter->GetParent ( __uuidof ( IDXGIFactory2 ), ( void** ) &dxgiFactory ) ) )
		throw std::runtime_error ( "Cannot get IDXGIFactory." );

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0, };
	swapChainDesc.Width = windowWidth;
	swapChainDesc.Height = windowHeight;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_BACK_BUFFER;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Stereo = false;

	if ( FAILED ( dxgiFactory->CreateSwapChainForCoreWindow ( d3dDevice, reinterpret_cast< IUnknown* >( app->window ),
		&swapChainDesc, nullptr, &dxgiSwapChain ) ) )
		throw std::runtime_error ( "Failed create DXGI Swap chain." );

	dxgiDevice->SetMaximumFrameLatency ( 1 );
#endif

	ID3D11Texture2D * backBuffer;
	if ( FAILED ( dxgiSwapChain->GetBuffer ( 0, __uuidof ( ID3D11Texture2D ), ( void ** ) &backBuffer ) ) )
		throw std::runtime_error ( "Failed get buffer from Swap Chain." );

	if ( FAILED ( d3dDevice->CreateRenderTargetView ( backBuffer, nullptr, &renderTargetView ) ) )
		throw std::runtime_error ( "Failed create Render target view." );

	D3D11_TEXTURE2D_DESC descBack;
	backBuffer->GetDesc ( &descBack );
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = descBack.Width;
	descDepth.Height = descBack.Height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	if ( FAILED ( d3dDevice->CreateTexture2D ( &descDepth, NULL, &depthStencilBuffer ) ) )
		throw std::runtime_error ( "Failed create Depth-stencil buffer." );

	if ( FAILED ( d3dDevice->CreateDepthStencilView ( depthStencilBuffer, nullptr, &depthStencilView ) ) )
		throw std::runtime_error ( "Failed create Depth-stencil view." );

	immediateContext->OMSetRenderTargets ( 1, &renderTargetView, depthStencilView );
	backBuffer->Release ();

	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = ( float ) windowWidth;
	viewport.Height = ( float ) windowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	immediateContext->RSSetViewports ( 1, &viewport );
}

PRGraphicsContext_Direct3D11::~PRGraphicsContext_Direct3D11 () {
	SAFE_RELEASE ( depthStencilView );
	SAFE_RELEASE ( depthStencilBuffer );
	SAFE_RELEASE ( renderTargetView );
	SAFE_RELEASE ( immediateContext );
	SAFE_RELEASE ( d3dDevice );
	SAFE_RELEASE ( dxgiSwapChain );
}
#endif

#if POLYRAM_D3D12
PRGraphicsContext_Direct3D12::PRGraphicsContext_Direct3D12 ( PRApplication * app ) {
	int windowWidth, windowHeight;
	app->getClientSize ( &windowWidth, &windowHeight );

#ifdef _DEBUG
	if ( SUCCEEDED ( D3D12GetDebugInterface ( IID_PPV_ARGS ( &debugLayer ) ) ) )
		debugLayer->EnableDebugLayer ();
#endif
	{
		IDXGIFactory2 * dxgiFactory;
		if ( FAILED ( CreateDXGIFactory2 ( 0, __uuidof ( IDXGIFactory2 ), ( void** ) &dxgiFactory ) ) )
			throw std::runtime_error ( "Failed create DXGI factory." );

		IDXGIAdapter1 * dxgiAdapter;
		if ( FAILED ( dxgiFactory->EnumAdapters1 ( 0, &dxgiAdapter ) ) )
			throw std::runtime_error ( "Failed enumeration DXGI Adapters." );

		if ( FAILED ( D3D12CreateDevice ( dxgiAdapter, D3D_FEATURE_LEVEL_12_0, __uuidof ( ID3D12Device ), ( void** ) &d3dDevice ) ) )
			if ( FAILED ( D3D12CreateDevice ( dxgiAdapter, D3D_FEATURE_LEVEL_11_0, __uuidof ( ID3D12Device ), ( void** ) &d3dDevice ) ) )
				if ( FAILED ( D3D12CreateDevice ( dxgiAdapter, D3D_FEATURE_LEVEL_9_3, __uuidof ( ID3D12Device ), ( void** ) &d3dDevice ) ) )
					throw std::runtime_error ( "Failed create Device." );

		dxgiAdapter->Release ();
		dxgiFactory->Release ();

		D3D12_COMMAND_QUEUE_DESC commandQueueDesc = { };
		commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		commandQueueDesc.NodeMask = 0;
		commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		if ( FAILED ( d3dDevice->CreateCommandQueue ( &commandQueueDesc, __uuidof ( ID3D12CommandQueue ), ( void** ) &commandQueue ) ) )
			throw std::runtime_error ( "Failed create Command queue." );

#if PRPlatformMicrosoftWindowsNT
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0, };
		swapChainDesc.BufferDesc.Width = windowWidth;
		swapChainDesc.BufferDesc.Height = windowHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = app->m_hWnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.Windowed = true;
		IDXGISwapChain * dxgiSwapChain;
		if ( FAILED ( dxgiFactory->CreateSwapChain ( commandQueue, &swapChainDesc, &dxgiSwapChain ) ) )
			throw std::runtime_error ( "Failed create Swap Chain." );
		if ( FAILED ( dxgiSwapChain->QueryInterface ( __uuidof ( IDXGISwapChain3 ), ( void** ) &this->dxgiSwapChain ) ) )
			throw std::runtime_error ( "Cannot query interface from IDXGISwapChain to IDXGISwapChain3." );
#elif PRPlatformMicrosoftWindowsRT
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0, };
		swapChainDesc.Width = windowWidth;
		swapChainDesc.Height = windowHeight;
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapChainDesc.Stereo = false;

		IDXGISwapChain1 * dxgiSwapChain;
		if ( FAILED ( dxgiFactory->CreateSwapChainForCoreWindow ( commandQueue, reinterpret_cast< IUnknown* >( app->window ),
			&swapChainDesc, nullptr, &dxgiSwapChain ) ) )
			throw std::runtime_error ( "Failed create DXGI Swap chain." );
		if ( FAILED ( dxgiSwapChain->QueryInterface ( __uuidof ( IDXGISwapChain3 ), ( void** ) &this->dxgiSwapChain ) ) )
			throw std::runtime_error ( "Cannot query interface from IDXGISwapChain to IDXGISwapChain3." );
#endif

		dxgiFactory->Release ();

		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc;
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		descHeapDesc.NumDescriptors = 2;
		descHeapDesc.NodeMask = 0;
		if ( FAILED ( d3dDevice->CreateDescriptorHeap ( &descHeapDesc, __uuidof ( ID3D12DescriptorHeap ), ( void** ) &descriptorHeap ) ) )
			throw std::runtime_error ( "Failed create Descriptor Heap." );
		descriptorHandleIncrementSize = d3dDevice->GetDescriptorHandleIncrementSize ( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );

		D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart ();
		for ( UINT n = 0; n < 2; n++ )
		{
			if ( FAILED ( dxgiSwapChain->GetBuffer ( n, __uuidof ( ID3D12Resource ), ( void** ) &renderTargets [ n ] ) ) )
				throw std::runtime_error ( "Failed create Render Target View." );
			d3dDevice->CreateRenderTargetView ( renderTargets [ n ], nullptr, descriptorHandle );
			descriptorHandle.ptr += descriptorHandleIncrementSize;
		}

		if ( FAILED ( d3dDevice->CreateCommandAllocator ( D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof ( ID3D12CommandAllocator ), ( void** ) &commandAllocator ) ) )
			throw std::runtime_error ( "Failed create Command Allocator." );
	}

	{
		ID3DBlob * signature;
		ID3DBlob * error;
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.NumParameters = 0;
		rootSignatureDesc.pParameters = nullptr;
		rootSignatureDesc.NumStaticSamplers = 0;
		rootSignatureDesc.pStaticSamplers = nullptr;
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		if ( FAILED ( D3D12SerializeRootSignature ( &rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error ) ) )
			throw std::runtime_error ( "Failed serialize Root Signature." );
		if ( FAILED ( d3dDevice->CreateRootSignature ( 0, signature->GetBufferPointer (), signature->GetBufferSize (),
			__uuidof ( ID3D12RootSignature ), ( void** ) &rootSignature ) ) )
			throw std::runtime_error ( "Failed create Root Signature." );
		signature->Release ();
		if ( error ) error->Release ();
	}

	{
		if ( FAILED ( d3dDevice->CreateFence ( 0, D3D12_FENCE_FLAG_NONE, __uuidof ( ID3D12Fence ), ( void** ) &fence ) ) )
			throw std::runtime_error ( "Failed create Fence." );
		fenceValue = 1;

		fenceEvent = CreateEventEx ( nullptr, FALSE, FALSE, EVENT_ALL_ACCESS );
		if ( fenceEvent == nullptr )
		{
			throw std::runtime_error ( "Cannot create Event. check GetLastError ()." );
		}

		Synchronization ();
	}
}

#if defined ( POLYRAM_D3D12 )
#include <dxgidebug.h>
#endif

PRGraphicsContext_Direct3D12::~PRGraphicsContext_Direct3D12 () {
	Synchronization ();
	CloseHandle ( fenceEvent );
	SAFE_RELEASE ( fence );
	SAFE_RELEASE ( rootSignature );
	SAFE_RELEASE ( commandAllocator );
	for ( int i = 0; i < 2; ++i )
	{
		auto rt = renderTargets [ i ];
		SAFE_RELEASE ( rt );
	}
	SAFE_RELEASE ( descriptorHeap );
	SAFE_RELEASE ( commandQueue );
	SAFE_RELEASE ( d3dDevice );
	SAFE_RELEASE ( dxgiSwapChain );
#if defined ( _DEBUG )
	SAFE_RELEASE ( debugLayer );
	IDXGIDebug1* pDebug = nullptr;
	if ( SUCCEEDED ( DXGIGetDebugInterface1 ( 0, IID_PPV_ARGS ( &pDebug ) ) ) ) {
		pDebug->ReportLiveObjects ( DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_SUMMARY );
		pDebug->Release ();
	}
#endif
}

void PRGraphicsContext_Direct3D12::Synchronization () {
	const UINT64 myFence = fenceValue;
	if ( FAILED ( commandQueue->Signal ( fence, myFence ) ) )
		throw std::runtime_error ( "Command Queue Signal failed." );
	fenceValue++;

	if ( fence->GetCompletedValue () < myFence )
	{
		if ( FAILED ( fence->SetEventOnCompletion ( myFence, fenceEvent ) ) )
			throw std::runtime_error ( "Cannot set Event on completion." );
		WaitForSingleObject ( fenceEvent, INFINITE );
	}

	frameIndex = dxgiSwapChain->GetCurrentBackBufferIndex ();
}
#endif

#if POLYRAM_OPENGL

#if PRPlatformMicrosoftWindowsNT
#include "wglext.h"
#elif PRPlatformUNIX
#include <cstdarg>
#include "glxext.h"
typedef GLXContext ( *GLXCREATECONTEXTATTRIBSARBPROC ) ( Display*, GLXFBConfig, GLXContext, Bool, const int * );
bool isExtensionSupported ( const char * extList, const char * e ) {
	const char *s, *t, *w = strchr ( e, ' ' );
	if ( w || *e == '\0' ) return false;
	for ( s = extList; ; ) {
		if ( !( w = strstr ( s, e ) ) ) break;
		t = w + strlen ( e );
		if ( ( w == s || *( w - 1 ) == ' ' ) && ( *t == ' ' || *t == '\0' ) )
			return true;
		s = t;
	}
	return false;
}
#endif

PRGraphicsContext_OpenGL::PRGraphicsContext_OpenGL ( PRApplication * app, PRRendererType rendererType ) {
#if PRPlatformMicrosoftWindowsNT
	hDC = GetDC ( app->m_hWnd );

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor =
	{
		sizeof ( PIXELFORMATDESCRIPTOR ), 1,
		PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA, 32,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		24, 8,
		0, PFD_MAIN_PLANE, 0, 0, 0, 0,
	};
	int pixelFormat = ChoosePixelFormat ( hDC, &pixelFormatDescriptor );
	if ( !SetPixelFormat ( hDC, pixelFormat, &pixelFormatDescriptor ) )
		throw std::runtime_error ( "Failed SetPixelFormat in OpenGL initialize." );

	glContext = wglCreateContext ( hDC );
	if ( glContext == 0 )
		throw std::runtime_error ( "Failed wglCreateContext in OpenGL initialize." );
	if ( !wglMakeCurrent ( hDC, glContext ) )
		throw std::runtime_error ( "Failed wglMakeCurrent." );

	if ( rendererType > PRRendererType_OpenGL1 ) {
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = ( PFNWGLCREATECONTEXTATTRIBSARBPROC ) wglGetProcAddress ( "wglCreateContextAttribsARB" );
		if ( wglCreateContextAttribsARB ) {
			int attribs [] = {
				WGL_CONTEXT_MAJOR_VERSION_ARB, ( rendererType - PRRendererType_OpenGL1 ) + 1,
				WGL_CONTEXT_MINOR_VERSION_ARB, 5,
				0
			};
			HGLRC temp = nullptr;
			while ( attribs [ 3 ] > 0 ) {
				if ( temp != nullptr ) {
					if ( attribs [ 1 ] <= 2 ) break;
					PRVersion version ( std::string ( ( const char * ) glGetString ( GL_VERSION ) ) );
					if ( version.major == attribs [ 1 ] && version.minor == attribs [ 3 ] )
						break;
				}

				temp = wglCreateContextAttribsARB ( hDC, 0, attribs );
				if ( temp == nullptr ) { --attribs [ 3 ]; continue; }
				wglDeleteContext ( glContext );
				glContext = temp;
				if ( !wglMakeCurrent ( hDC, glContext ) ) throw std::runtime_error ( "Failed wglMakeCurrent." );
			}

			if ( temp == nullptr )
				throw std::runtime_error ( "Failed create new attribs context." );
		}
	}
#elif PRPlatformAppleOSX
	auto profile = NSOpenGLProfileVersionLegacy;
	if ( rendererType == PRRendererType_OpenGL3 )
		profile = NSOpenGLProfileVersion3_2Core;
	else if ( rendererType == PRRendererType_OpenGL4 )
		profile = NSOpenGLProfileVersion4_1Core;

	NSOpenGLPixelFormatAttribute attr [] = {
		NSOpenGLPFAOpenGLProfile, profile, NSOpenGLPFAAccelerated, NSOpenGLPFADoubleBuffer,
		NSOpenGLPFADepthSize, rendererInfo.depthBufferSize, NSOpenGLPFAStencilSize, rendererInfo.stencilBufferSize, 0
	};

	NSOpenGLPixelFormat * pixelFormat = [ [ NSOpenGLPixelFormat alloc ] initWithAttributes:attr ];
	if ( pixelFormat == nil )
		throw PRException ( "Failed create NSOpenGLPixelFormat." );

	glContext = [ [ NSOpenGLContext alloc ] initWithFormat:pixelFormat shareContext : nil ];
	if ( glContext == nil )
		throw PRException ( "Failed create NSOpenGLContext." );
	glContext.view = app->window.contentView;

	[glContext makeCurrentContext];
#elif PRPlatformAppleiOS
	EAGLRenderingAPI api;
	switch ( rendererType ) {
	case PRRendererType_OpenGLES1: api = kEAGLRenderingAPIOpenGLES1; break;
	case PRRendererType_OpenGLES2: api = kEAGLRenderingAPIOpenGLES2; break;
	case PRRendererType_OpenGLES3: api = kEAGLRenderingAPIOpenGLES3; break;
	default: throw std::runtime_error ( "Invaild OpenGL ES version." );
	}
	glContext = [ [ EAGLContext alloc ] initWithAPI:api ];

	GLKView * view = ( GLKView* ) wnd->window.rootViewController.view;
	view.context = glContext;

	view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
	view.drawableStencilFormat = GLKViewDrawableStencilFormat8;
#elif PRPlatformUNIX
	const char * glxExts = glXQueryExtensionsString ( app->display, DefaultScreen ( app->display ) );
	GLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = ( GLXCREATECONTEXTATTRIBSARBPROC ) glXGetProcAddressARB ( ( const GLubyte * ) "glXCreateContextAttribsARB" );

	if ( !isExtensionSupported ( glxExts, "GLX_ARB_create_context" ) || glXCreateContextAttribsARB == nullptr ) {
		glContext = glXCreateContext ( app->display, app->visualInfo, nullptr, true );
	}
	else {
		GLint visualAttr [] = {
			GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_STENCIL_SIZE, 8, GLX_DOUBLEBUFFER, true, GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR, None
		};
		GLint contextAttribs [] = {
			GLX_CONTEXT_MAJOR_VERSION_ARB, ( rendererType - PRRendererType_OpenGL1 ) + 1,
			GLX_CONTEXT_MINOR_VERSION_ARB, 0,
			GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
			None,
		};

		int nelements;
		GLXFBConfig * config = glXChooseFBConfig ( app->display, DefaultScreen ( app->display ), visualAttr, &nelements );
		if ( nelements == 0 )
			throw std::runtime_error ( "FBConfig's count is zero." );

		glContext = glXCreateContextAttribsARB ( app->display, config [ 0 ], nullptr, true, contextAttribs );
	}

	if ( glContext == nullptr )
		throw std::runtime_error ( "Failed create OpenGL context." );

	if ( !glXMakeCurrent ( app->display, app->window, glContext ) )
		throw std::runtime_error ( "Failed make current." );
#elif PRPlatformGoogleAndroid
	const EGLint attribs [] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_DEPTH_SIZE, 24,
		EGL_STENCIL_SIZE, 8,
		EGL_NONE
	};
	EGLint w, h, format;
	EGLint numConfigs;
	EGLConfig config;

	display = eglGetDisplay ( EGL_DEFAULT_DISPLAY );

	eglInitialize ( display, 0, 0 );

	eglChooseConfig ( display, attribs, &config, 1, &numConfigs );
	eglGetConfigAttrib ( display, config, EGL_NATIVE_VISUAL_ID, &format );

	ANativeWindow_setBuffersGeometry ( PRApplication::sharedApplication ()->engine.app->window, 0, 0, format );

	surface = eglCreateWindowSurface ( display, config, PRApplication::sharedApplication ()->engine.app->window, NULL );
	EGLint createAttribs [] = { EGL_CONTEXT_CLIENT_VERSION, ( rendererType - PRRendererType_OpenGLES1 ) + 1, EGL_NONE };
	context = eglCreateContext ( display, config, NULL, createAttribs );

	if ( eglMakeCurrent ( display, surface, surface, context ) == EGL_FALSE )
		throw std::runtime_error ( "Unable to eglMakeCurrent" );

	eglQuerySurface ( display, surface, EGL_WIDTH, &w );
	eglQuerySurface ( display, surface, EGL_HEIGHT, &h );

	PRApplication::sharedApplication ()->engine.width = w;
	PRApplication::sharedApplication ()->engine.height = h;
#endif
	GLenum errorCode = glGetError ();
	if ( errorCode != GL_NO_ERROR )
		throw std::runtime_error ( "OpenGL Error." );

#if PRPlatformDesktops
	PRPrintLog ( "OGL ERR: %d", glGetError () );
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit ();
	if ( glewError != GLEW_OK )
		throw std::runtime_error ( ( const char* ) glewGetErrorString ( glewError ) );
	PRPrintLog ( "OGL ERR in GLEW: %d", glGetError () );
#endif

	glClearColor ( 0, 0, 0, 1 );
#if PRPlatformDesktops
	glClearDepth ( 1 );
#else
	glClearDepthf ( 1 );
#endif
	glClearStencil ( 0 );
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	PRPrintLog ( "OGL ERR: %d", glGetError () );
}

PRGraphicsContext_OpenGL::~PRGraphicsContext_OpenGL () {
#if PRPlatformMicrosoftWindowsNT
	wglDeleteContext ( glContext );
#elif PRPlatformAppleOSX
	glContext = nil;
#elif PRPlatformAppleiOS

#elif PRPlatformUNIX
	PRApplication * app = PRApplication::sharedApplication ();
	glXMakeCurrent ( app->display, 0, 0 );
	glXDestroyContext ( app->display, glContext );
#elif PRPlatformGoogleAndroid
	if ( display != EGL_NO_DISPLAY ) {
		eglMakeCurrent ( display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
		if ( context != EGL_NO_CONTEXT ) {
			eglDestroyContext ( display, context );
		}
		if ( surface != EGL_NO_SURFACE ) {
			eglDestroySurface ( display, surface );
		}
		eglTerminate ( display );
	}
	PRApplication::sharedApplication ()->engine.animating = 0;
	display = EGL_NO_DISPLAY;
	context = EGL_NO_CONTEXT;
	surface = EGL_NO_SURFACE;
#endif
}

void PRGraphicsContext_OpenGL::makeCurrent () {
#if PRPlatformMicrosoftWindowsNT
	wglMakeCurrent ( hDC, glContext );
#elif PRPlatformAppleOSX
	[ glContext makeCurrentContext ];
#elif PRPlatformAppleiOS
	[ EAGLContext setCurrentContext : glContext ];
#elif PRPlatformUNIX
	PRApplication * app = PRApplication::sharedApplication ();
	glXMakeCurrent ( app->display, app->window, glContext );
#elif PRPlatformGoogleAndroid
	eglMakeCurrent ( display, surface, surface, context );
#endif
}

void PRGraphicsContext_OpenGL::swapBuffers () {
	glFlush ();
#if PRPlatformMicrosoftWindowsNT
	SwapBuffers ( hDC );
#elif PRPlatformAppleOSX
	[ glContext flushBuffer ];
#elif PRPlatformAppleiOS
	[ glContext presentRenderbuffer : 0 ];
#elif PRPlatformUNIX
	PRApplication * app = PRApplication::sharedApplication ();
	glXSwapBuffers ( app->display, app->window );
#elif PRPlatformGoogleAndroid
	eglSwapBuffers ( display, surface );
#endif
}
#endif

#if POLYRAM_METAL
PRGraphicsContext_Metal::PRGraphicsContext_Metal ( PRApplication * app ) {
	device = MTLCreateSystemDefaultDevice ();
	commandQueue = [ device newCommandQueue ];
	library = [ device newDefaultLibrary ];
	commandBuffer = [ commandQueue commandBuffer ];
}

PRGraphicsContext_Metal::~PRGraphicsContext_Metal () {
	commandBuffer = nil;
	library = nil;
	commandQueue = nil;
	device = nil;
}
#endif

#if defined ( POLYRAM_VULKAN )
/*PRGraphicsContext_Vulkan::PRGraphicsContext_Vulkan ( PRApplication * app ) {
	VkApplicationInfo applicationInfo;
	VkInstanceCreateInfo instanceInfo;

	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pNext = nullptr;
	applicationInfo.pApplicationName = "libPolyram";
	applicationInfo.pEngineName = "libPolyram";
	applicationInfo.engineVersion = 1;
	applicationInfo.apiVersion = VK_API_VERSION;

	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = nullptr;
	instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo = &applicationInfo;
	instanceInfo.enabledLayerCount = 0;
	instanceInfo.ppEnabledLayerNames = nullptr;
	instanceInfo.enabledExtensionCount = 0;
	instanceInfo.ppEnabledExtensionNames = nullptr;

	VkResult result = vkCreateInstance ( &instanceInfo, nullptr, &instance );
	if ( result != VK_SUCCESS )
		throw std::runtime_error ( "Failed to create Vulkan instance." );

	uint32_t deviceCount = 0;
	result = vkEnumeratePhysicalDevices ( instance, &deviceCount, nullptr );
	if ( result != VK_SUCCESS )
		throw std::runtime_error ( "Failed to query the number of physical devices present." );

	if ( deviceCount == 0 )
		throw std::runtime_error ( "Couldn't detect any device present with Vulkan support." );

	std::vector<VkPhysicalDevice> physicalDevices ( deviceCount );
	result = vkEnumeratePhysicalDevices ( instance, &deviceCount, &physicalDevices [ 0 ] );
	if ( result != VK_SUCCESS )
		throw std::runtime_error ( "Faied to enumerate physical devices presen." );

	VkDeviceCreateInfo deviceInfo;
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.pNext = nullptr;
	deviceInfo.flags = 0;
	deviceInfo.enabledLayerCount = 0;
	deviceInfo.ppEnabledLayerNames = nullptr;
	deviceInfo.enabledExtensionCount = 0;
	deviceInfo.ppEnabledExtensionNames = nullptr;
	deviceInfo.pEnabledFeatures = nullptr;

	float queuePriorities [] = { 1.0f };
	VkDeviceQueueCreateInfo deviceQueueInfo;
	deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueInfo.pNext = nullptr;
	deviceQueueInfo.flags = 0;
	deviceQueueInfo.queueFamilyIndex = 0;
	deviceQueueInfo.queueCount = 1;
	deviceQueueInfo.pQueuePriorities = queuePriorities;

	deviceInfo.queueCreateInfoCount = 1;
	deviceInfo.pQueueCreateInfos = &deviceQueueInfo;

	result = vkCreateDevice ( physicalDevices [ 0 ], &deviceInfo, nullptr, &device );
	if ( result != VK_SUCCESS )
		throw std::runtime_error ( "Failed creating logical device." );

	vkGetDeviceQueue ( device, 0, 0, &queue );
}

PRGraphicsContext_Vulkan::~PRGraphicsContext_Vulkan ()
{
	if ( device != VK_NULL_HANDLE )
	{
		vkDeviceWaitIdle ( device );
		vkDestroyDevice ( device, nullptr );
	}
	if ( instance != VK_NULL_HANDLE )
		vkDestroyInstance ( instance, nullptr );
}*/
#endif

#define COPIEDMETHOD0(x,y) x temp; y ( &temp ); return temp;
#define COPIEDMETHOD1(x,y,z) x temp; y ( z, &temp ); return temp;
#define COPIEDMETHOD2(x,y,z,w) x temp; y ( z, w, &temp ); return temp;

PRVector2::PRVector2 () : x ( 0 ), y ( 0 ) { }
PRVector2::PRVector2 ( float v ) : x ( v ), y ( v ) { }
PRVector2::PRVector2 ( float x, float y ) : x ( x ), y ( y ) { }

void PRVector2::lengthSquared ( float * result ) { lengthSquared ( this, result ); }
void PRVector2::length ( float * result ) { length ( this, result ); }
void PRVector2::normalize ( PRVector2 * result ) { normalize ( this, result ); }

float PRVector2::lengthSquared () { float temp; lengthSquared ( this, &temp ); return temp; }
float PRVector2::length () { float temp; length ( this, &temp ); return temp; }
PRVector2 PRVector2::normalize () { PRVector2 temp; normalize ( this, &temp ); return temp; }

void PRVector2::lengthSquared ( const PRVector2 * v, float * result ) { *result = v->x * v->x + v->y * v->y; }
void PRVector2::length ( const PRVector2 * v, float * result ) { float ls; lengthSquared ( v, &ls ); *result = sqrtf ( ls ); }
void PRVector2::normalize ( const PRVector2 * v, PRVector2 * result ) { float len; length ( v, &len ); divide ( v, len, result ); }

float PRVector2::lengthSquared ( const PRVector2 & v ) { float temp; lengthSquared ( &v, &temp ); return temp; }
float PRVector2::length ( const PRVector2 & v ) { float temp; length ( &v, &temp ); return temp; }
PRVector2 PRVector2::normalize ( const PRVector2 & v ) { PRVector2 temp; normalize ( &v, &temp ); return temp; }

void PRVector2::add ( const PRVector2 * v1, const PRVector2 * v2, PRVector2 * result ) {
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
}
void PRVector2::subtract ( const PRVector2 * v1, const PRVector2 * v2, PRVector2 * result ) {
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
}
void PRVector2::negate ( const PRVector2 * v1, PRVector2 * result ) {
	result->x = -v1->x;
	result->y = -v1->y;
}
void PRVector2::multiply ( const PRVector2 * v1, const PRVector2 * v2, PRVector2 * result ) {
	result->x = v1->x * v2->x;
	result->y = v1->y * v2->y;
}
void PRVector2::multiply ( const PRVector2 * v1, float v2, PRVector2 * result ) {
	result->x = v1->x * v2;
	result->y = v1->y * v2;
}
void PRVector2::multiply ( float v1, const PRVector2 * v2, PRVector2 * result ) { multiply ( v2, v1, result ); }
void PRVector2::divide ( const PRVector2 * v1, const PRVector2 * v2, PRVector2 * result ) {
	result->x = v1->x / v2->x;
	result->y = v1->y / v2->y;
}
void PRVector2::divide ( const PRVector2 * v1, float v2, PRVector2 * result ) {
	result->x = v1->x / v2;
	result->y = v1->y / v2;
}
void PRVector2::dot ( const PRVector2 * v1, const PRVector2 * v2, float * result ) {
	*result = ( v1->x * v2->x ) + ( v1->y * v2->y );
}
void PRVector2::dot ( const PRVector2 * v1, float v2, float * result ) {
	*result = ( v1->x * v2 ) + ( v1->y * v2 );
}
void PRVector2::cross ( const PRVector2 * v1, const PRVector2 * v2, PRVector2 * result ) {
	result->x = v1->x * v2->y;
	result->y = v1->y * v2->x;
}

PRVector2 PRVector2::add ( const PRVector2 & v1, const PRVector2 & v2 ) { COPIEDMETHOD2 ( PRVector2, add, &v1, &v2 ); }
PRVector2 PRVector2::subtract ( const PRVector2 & v1, const PRVector2 & v2 ) { COPIEDMETHOD2 ( PRVector2, subtract, &v1, &v2 ); }
PRVector2 PRVector2::negate ( const PRVector2 & v1 ) { COPIEDMETHOD1 ( PRVector2, negate, &v1 ); }
PRVector2 PRVector2::multiply ( const PRVector2 & v1, const PRVector2 & v2 ) { COPIEDMETHOD2 ( PRVector2, multiply, &v1, &v2 ); }
PRVector2 PRVector2::multiply ( const PRVector2 & v1, float v2 ) { COPIEDMETHOD2 ( PRVector2, multiply, &v1, v2 ); }
PRVector2 PRVector2::multiply ( float v1, const PRVector2 & v2 ) { COPIEDMETHOD2 ( PRVector2, multiply, v1, &v2 ); }
PRVector2 PRVector2::divide ( const PRVector2 & v1, const PRVector2 & v2 ) { COPIEDMETHOD2 ( PRVector2, divide, &v1, &v2 ); }
PRVector2 PRVector2::divide ( const PRVector2 & v1, float v2 ) { COPIEDMETHOD2 ( PRVector2, divide, &v1, v2 ); }
float PRVector2::dot ( const PRVector2 & v1, const PRVector2 & v2 ) { COPIEDMETHOD2 ( float, dot, &v1, &v2 ); }
float PRVector2::dot ( const PRVector2 & v1, float v2 ) { COPIEDMETHOD2 ( float, dot, &v1, v2 ); }
PRVector2 PRVector2::cross ( const PRVector2 & v1, const PRVector2 & v2 ) { COPIEDMETHOD2 ( PRVector2, cross, &v1, &v2 ); }

void PRVector2::transform ( const PRVector2 * pos, const PRMatrix * mat, PRVector2 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + mat->_41;
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + mat->_42;
}
void PRVector2::transformNormal ( const PRVector2 * nor, const PRMatrix * mat, PRVector2 * result ) {
	result->x = ( nor->x * mat->_11 ) + ( nor->y * mat->_21 );
	result->y = ( nor->x * mat->_12 ) + ( nor->y * mat->_22 );
}

PRVector2 PRVector2::transform ( const PRVector2 & pos, const PRMatrix & mat ) { COPIEDMETHOD2 ( PRVector2, transform, &pos, &mat ); }
PRVector2 PRVector2::transformNormal ( const PRVector2 & nor, const PRMatrix & mat ) { COPIEDMETHOD2 ( PRVector2, transformNormal, &nor, &mat ); }

PRVector2 operator+ ( const PRVector2 & v1, const PRVector2 & v2 ) { return PRVector2::add ( v1, v2 ); }
PRVector2 operator- ( const PRVector2 & v1, const PRVector2 & v2 ) { return PRVector2::subtract ( v1, v2 ); }
PRVector2 operator- ( const PRVector2 & v1 ) { return PRVector2::negate ( v1 ); }
PRVector2 operator* ( const PRVector2 & v1, const PRVector2 & v2 ) { return PRVector2::multiply ( v1, v2 ); }
PRVector2 operator* ( const PRVector2 & v1, float v2 ) { return PRVector2::multiply ( v1, v2 ); }
PRVector2 operator* ( float v1, const PRVector2 & v2 ) { return PRVector2::multiply ( v1, v2 ); }
PRVector2 operator/ ( const PRVector2 & v1, const PRVector2 & v2 ) { return PRVector2::divide ( v1, v2 ); }
PRVector2 operator/ ( const PRVector2 & v1, float v2 ) { return PRVector2::divide ( v1, v2 ); }
bool operator== ( const PRVector2 & v1, const PRVector2 & v2 )
{
	return PRIsEquals ( v1.x, v2.x ) && PRIsEquals ( v1.y, v2.y );
}

PRVector3::PRVector3 () : x ( 0 ), y ( 0 ), z ( 0 ) { }
PRVector3::PRVector3 ( float v ) : x ( v ), y ( v ), z ( v ) { }
PRVector3::PRVector3 ( float x, float y, float z ) : x ( x ), y ( y ), z ( z ) { }
PRVector3::PRVector3 ( const PRVector2 & v, float z ) : x ( v.x ), y ( v.y ), z ( z ) { }

void PRVector3::lengthSquared ( float * result ) { lengthSquared ( this, result ); }
void PRVector3::length ( float * result ) { length ( this, result ); }
void PRVector3::normalize ( PRVector3 * result ) { normalize ( this, result ); }

float PRVector3::lengthSquared () { float temp; lengthSquared ( this, &temp ); return temp; }
float PRVector3::length () { float temp; length ( this, &temp ); return temp; }
PRVector3 PRVector3::normalize () { PRVector3 temp; normalize ( this, &temp ); return temp; }

void PRVector3::lengthSquared ( const PRVector3 * v, float * result ) { *result = v->x * v->x + v->y * v->y + v->z * v->z; }
void PRVector3::length ( const PRVector3 * v, float * result ) { float ls; lengthSquared ( v, &ls ); *result = sqrtf ( ls ); }
void PRVector3::normalize ( const PRVector3 * v, PRVector3 * result )
{
	float len; length ( v, &len );
	divide ( v, len, result );
}

float PRVector3::lengthSquared ( const PRVector3 & v ) { float temp; lengthSquared ( &v, &temp ); return temp; }
float PRVector3::length ( const PRVector3 & v ) { float temp; length ( &v, &temp ); return temp; }
PRVector3 PRVector3::normalize ( const PRVector3 & v ) { PRVector3 temp; normalize ( &v, &temp ); return temp; }

void PRVector3::add ( const PRVector3 * v1, const PRVector3 * v2, PRVector3 * result ) {
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;
}
void PRVector3::subtract ( const PRVector3 * v1, const PRVector3 * v2, PRVector3 * result ) {
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
	result->z = v1->z - v2->z;
}
void PRVector3::negate ( const PRVector3 * v1, PRVector3 * result ) {
	result->x = -v1->x;
	result->y = -v1->y;
	result->z = -v1->z;
}
void PRVector3::multiply ( const PRVector3 * v1, const PRVector3 * v2, PRVector3 * result ) {
	result->x = v1->x * v2->x;
	result->y = v1->y * v2->y;
	result->z = v1->z * v2->z;
}
void PRVector3::multiply ( const PRVector3 * v1, float v2, PRVector3 * result ) {
	result->x = v1->x * v2;
	result->y = v1->y * v2;
	result->z = v1->z * v2;
}
void PRVector3::multiply ( float v1, const PRVector3 * v2, PRVector3 * result ) {
	result->x = v1 * v2->x;
	result->y = v1 * v2->y;
	result->z = v1 * v2->z;
}
void PRVector3::divide ( const PRVector3 * v1, const PRVector3 * v2, PRVector3 * result ) {
	result->x = v1->x / v2->x;
	result->y = v1->y / v2->y;
	result->z = v1->z / v2->z;
}
void PRVector3::divide ( const PRVector3 * v1, float v2, PRVector3 * result ) {
	result->x = v1->x / v2;
	result->y = v1->y / v2;
	result->z = v1->z / v2;
}
void PRVector3::dot ( const PRVector3 * v1, const PRVector3 * v2, float * result ) {
	*result = ( v1->x * v2->x ) + ( v1->y * v2->y ) + ( v1->z * v2->z );
}
void PRVector3::dot ( const PRVector3 * v1, float v2, float * result ) {
	*result = ( v1->x * v2 ) + ( v1->y * v2 ) + ( v1->z * v2 );
}
void PRVector3::cross ( const PRVector3 * v1, const PRVector3 * v2, PRVector3 * result ) {
	result->x = v1->y * v2->z - v1->z * v2->y;
	result->y = v1->z * v2->x - v1->x * v2->z;
	result->z = v1->x * v2->y - v1->y * v2->x;
}

PRVector3 PRVector3::add ( const PRVector3 & v1, const PRVector3 & v2 ) { COPIEDMETHOD2 ( PRVector3, add, &v1, &v2 ); }
PRVector3 PRVector3::subtract ( const PRVector3 & v1, const PRVector3 & v2 ) { COPIEDMETHOD2 ( PRVector3, subtract, &v1, &v2 ); }
PRVector3 PRVector3::negate ( const PRVector3 & v1 ) { COPIEDMETHOD1 ( PRVector3, negate, &v1 ); }
PRVector3 PRVector3::multiply ( const PRVector3 & v1, const PRVector3 & v2 ) { COPIEDMETHOD2 ( PRVector3, multiply, &v1, &v2 ); }
PRVector3 PRVector3::multiply ( const PRVector3 & v1, float v2 ) { COPIEDMETHOD2 ( PRVector3, multiply, &v1, v2 ); }
PRVector3 PRVector3::multiply ( float v1, const PRVector3 & v2 ) { COPIEDMETHOD2 ( PRVector3, multiply, v1, &v2 ); }
PRVector3 PRVector3::divide ( const PRVector3 & v1, const PRVector3 & v2 ) { COPIEDMETHOD2 ( PRVector3, divide, &v1, &v2 ); }
PRVector3 PRVector3::divide ( const PRVector3 & v1, float v2 ) { COPIEDMETHOD2 ( PRVector3, divide, &v1, v2 ); }
float PRVector3::dot ( const PRVector3 & v1, const PRVector3 & v2 ) { COPIEDMETHOD2 ( float, dot, &v1, &v2 ); }
float PRVector3::dot ( const PRVector3 & v1, float v2 ) { COPIEDMETHOD2 ( float, dot, &v1, v2 ); }
PRVector3 PRVector3::cross ( const PRVector3 & v1, const PRVector3 & v2 ) { COPIEDMETHOD2 ( PRVector3, cross, &v1, &v2 ); }

void PRVector3::transform ( const PRVector2 * pos, const PRMatrix * mat, PRVector3 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + mat->_41;
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + mat->_42;
	result->z = ( pos->x * mat->_13 ) + ( pos->y * mat->_23 ) + mat->_43;
}
void PRVector3::transform ( const PRVector3 * pos, const PRMatrix * mat, PRVector3 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + ( pos->z * mat->_31 ) + mat->_41;
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + ( pos->z * mat->_32 ) + mat->_42;
	result->z = ( pos->x * mat->_13 ) + ( pos->y * mat->_23 ) + ( pos->z * mat->_33 ) + mat->_43;
}
void PRVector3::transform ( const PRVector3 * pos, const PRQuaternion * q, PRVector3 * result ) {
	float x = 2 * ( q->y * pos->z - q->z * pos->y ), y = 2 * ( q->z * pos->x - q->x * pos->z ),
		z = 2 * ( q->x * pos->y - q->y * pos->x );
	result->x = pos->x + x * q->w + ( q->y * z - q->z * y );
	result->y = pos->y + y * q->w + ( q->z * x - q->x * z );
	result->z = pos->z + z * q->w + ( q->x * y - q->y * x );
}
void PRVector3::transformNormal ( const PRVector2 * nor, const PRMatrix * mat, PRVector3 * result ) {
	result->x = ( nor->x * mat->_11 ) + ( nor->y * mat->_21 );
	result->y = ( nor->x * mat->_12 ) + ( nor->y * mat->_22 );
	result->z = ( nor->x * mat->_13 ) + ( nor->y * mat->_23 );
}
void PRVector3::transformNormal ( const PRVector3 * nor, const PRMatrix * mat, PRVector3 * result ) {
	result->x = ( nor->x * mat->_11 ) + ( nor->y * mat->_21 ) + ( nor->z * mat->_31 );
	result->y = ( nor->x * mat->_12 ) + ( nor->y * mat->_22 ) + ( nor->z * mat->_32 );
	result->z = ( nor->x * mat->_13 ) + ( nor->y * mat->_23 ) + ( nor->z * mat->_33 );
}

PRVector3 PRVector3::transform ( const PRVector3 & pos, const PRMatrix & mat ) { COPIEDMETHOD2 ( PRVector3, transform, &pos, &mat ); }
PRVector3 PRVector3::transform ( const PRVector2 & pos, const PRMatrix & mat ) { COPIEDMETHOD2 ( PRVector3, transform, &pos, &mat ); }
PRVector3 PRVector3::transform ( const PRVector3 & pos, const PRQuaternion & q ) { COPIEDMETHOD2 ( PRVector3, transform, &pos, &q ); }
PRVector3 PRVector3::transformNormal ( const PRVector2 & nor, const PRMatrix & mat ) { COPIEDMETHOD2 ( PRVector3, transformNormal, &nor, &mat ); }
PRVector3 PRVector3::transformNormal ( const PRVector3 & nor, const PRMatrix & mat ) { COPIEDMETHOD2 ( PRVector3, transformNormal, &nor, &mat ); }

PRVector3 operator+ ( const PRVector3 & v1, const PRVector3 & v2 ) { return PRVector3::add ( v1, v2 ); }
PRVector3 operator- ( const PRVector3 & v1, const PRVector3 & v2 ) { return PRVector3::subtract ( v1, v2 ); }
PRVector3 operator- ( const PRVector3 & v1 ) { return PRVector3::negate ( v1 ); }
PRVector3 operator* ( const PRVector3 & v1, const PRVector3 & v2 ) { return PRVector3::multiply ( v1, v2 ); }
PRVector3 operator* ( const PRVector3 & v1, float v2 ) { return PRVector3::multiply ( v1, v2 ); }
PRVector3 operator* ( float v1, const PRVector3 & v2 ) { return PRVector3::multiply ( v1, v2 ); }
PRVector3 operator/ ( const PRVector3 & v1, const PRVector3 & v2 ) { return PRVector3::divide ( v1, v2 ); }
PRVector3 operator/ ( const PRVector3 & v1, float v2 ) { return PRVector3::divide ( v1, v2 ); }
bool operator== ( const PRVector3 & v1, const PRVector3 & v2 )
{
	return PRIsEquals ( v1.x, v2.x ) && PRIsEquals ( v1.y, v2.y ) && PRIsEquals ( v1.z, v2.z );
}

PRVector4::PRVector4 () : x ( 0 ), y ( 0 ), z ( 0 ), w ( 0 ) { }
PRVector4::PRVector4 ( float v ) : x ( v ), y ( v ), z ( v ), w ( 0 ) { }
PRVector4::PRVector4 ( float x, float y, float z, float w ) : x ( x ), y ( y ), z ( z ), w ( w ) { }
PRVector4::PRVector4 ( const PRVector2 & v, float z, float w ) : x ( v.x ), y ( v.y ), z ( z ), w ( w ) { }
PRVector4::PRVector4 ( const PRVector3 & v, float w ) : x ( v.x ), y ( v.y ), z ( v.z ), w ( w ) { }
PRVector4::PRVector4 ( const PRQuaternion & v ) : x ( v.x ), y ( v.y ), z ( v.z ), w ( v.w ) { }

void PRVector4::lengthSquared ( float * result ) { lengthSquared ( this, result ); }
void PRVector4::length ( float * result ) { length ( this, result ); }
void PRVector4::normalize ( PRVector4 * result ) { normalize ( this, result ); }

float PRVector4::lengthSquared () { float temp; lengthSquared ( this, &temp ); return temp; }
float PRVector4::length () { float temp; length ( this, &temp ); return temp; }
PRVector4 PRVector4::normalize () { PRVector4 temp; normalize ( this, &temp ); return temp; }

void PRVector4::lengthSquared ( const PRVector4 * v, float * result ) { *result = v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w; }
void PRVector4::length ( const PRVector4 * v, float * result ) { float ls; lengthSquared ( v, &ls ); *result = sqrtf ( ls ); }
void PRVector4::normalize ( const PRVector4 * v, PRVector4 * result ) {
	float len; length ( v, &len );
	divide ( v, len, result );
}

float PRVector4::lengthSquared ( const PRVector4 & v ) { float temp; lengthSquared ( &v, &temp ); return temp; }
float PRVector4::length ( const PRVector4 & v ) { float temp; length ( &v, &temp ); return temp; }
PRVector4 PRVector4::normalize ( const PRVector4 & v ) { PRVector4 temp; normalize ( &v, &temp ); return temp; }

void PRVector4::add ( const PRVector4 * v1, const PRVector4 * v2, PRVector4 * result ) {
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;
	result->w = v1->w + v2->w;
}
void PRVector4::subtract ( const PRVector4 * v1, const PRVector4 * v2, PRVector4 * result ) {
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
	result->z = v1->z - v2->z;
	result->z = v1->w - v2->w;
}
void PRVector4::negate ( const PRVector4 * v1, PRVector4 * result ) {
	result->x = -v1->x;
	result->y = -v1->y;
	result->z = -v1->z;
	result->w = -v1->w;
}
void PRVector4::multiply ( const PRVector4 * v1, const PRVector4 * v2, PRVector4 * result ) {
	result->x = v1->x * v2->x;
	result->y = v1->y * v2->y;
	result->z = v1->z * v2->z;
	result->z = v1->w * v2->w;
}
void PRVector4::multiply ( const PRVector4 * v1, float v2, PRVector4 * result ) {
	result->x = v1->x * v2;
	result->y = v1->y * v2;
	result->z = v1->z * v2;
	result->z = v1->w * v2;
}
void PRVector4::multiply ( float v1, const PRVector4 * v2, PRVector4 * result ) {
	result->x = v1 * v2->x;
	result->y = v1 * v2->y;
	result->z = v1 * v2->z;
	result->z = v1 * v2->w;
}
void PRVector4::divide ( const PRVector4 * v1, const PRVector4 * v2, PRVector4 * result ) {
	result->x = v1->x / v2->x;
	result->y = v1->y / v2->y;
	result->z = v1->z / v2->z;
	result->z = v1->w / v2->w;
}
void PRVector4::divide ( const PRVector4 * v1, float v2, PRVector4 * result ) {
	result->x = v1->x / v2;
	result->y = v1->y / v2;
	result->z = v1->z / v2;
	result->z = v1->w / v2;
}
void PRVector4::dot ( const PRVector4 * v1, const PRVector4 * v2, float * result ) {
	*result = ( v1->x * v2->x ) + ( v1->y * v2->y ) + ( v1->z * v2->z ) + ( v1->w * v2->w );
}
void PRVector4::dot ( const PRVector4 * v1, float v2, float * result ) {
	*result = ( v1->x * v2 ) + ( v1->y * v2 ) + ( v1->z * v2 ) + ( v1->w * v2 );
}

PRVector4 PRVector4::add ( const PRVector4 & v1, const PRVector4 & v2 ) { COPIEDMETHOD2 ( PRVector4, add, &v1, &v2 ); }
PRVector4 PRVector4::subtract ( const PRVector4 & v1, const PRVector4 & v2 ) { COPIEDMETHOD2 ( PRVector4, subtract, &v1, &v2 ); }
PRVector4 PRVector4::negate ( const PRVector4 & v1 ) { COPIEDMETHOD1 ( PRVector4, negate, &v1 ); }
PRVector4 PRVector4::multiply ( const PRVector4 & v1, const PRVector4 & v2 ) { COPIEDMETHOD2 ( PRVector4, multiply, &v1, &v2 ); }
PRVector4 PRVector4::multiply ( const PRVector4 & v1, float v2 ) { COPIEDMETHOD2 ( PRVector4, multiply, &v1, v2 ); }
PRVector4 PRVector4::multiply ( float v1, const PRVector4 & v2 ) { COPIEDMETHOD2 ( PRVector4, multiply, v1, &v2 ); }
PRVector4 PRVector4::divide ( const PRVector4 & v1, const PRVector4 & v2 ) { COPIEDMETHOD2 ( PRVector4, divide, &v1, &v2 ); }
PRVector4 PRVector4::divide ( const PRVector4 & v1, float v2 ) { COPIEDMETHOD2 ( PRVector4, divide, &v1, v2 ); }
float PRVector4::dot ( const PRVector4 & v1, const PRVector4 & v2 ) { COPIEDMETHOD2 ( float, dot, &v1, &v2 ); }
float PRVector4::dot ( const PRVector4 & v1, float v2 ) { COPIEDMETHOD2 ( float, dot, &v1, v2 ); }

void PRVector4::transform ( const PRVector2 * pos, const PRMatrix * mat, PRVector4 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + mat->_41;
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + mat->_42;
	result->z = ( pos->x * mat->_13 ) + ( pos->y * mat->_23 ) + mat->_43;
	result->w = ( pos->x * mat->_14 ) + ( pos->y * mat->_24 ) + mat->_44;
}
void PRVector4::transform ( const PRVector3 * pos, const PRMatrix * mat, PRVector4 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + ( pos->z * mat->_31 ) + mat->_41;
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + ( pos->z * mat->_32 ) + mat->_42;
	result->z = ( pos->x * mat->_13 ) + ( pos->y * mat->_23 ) + ( pos->z * mat->_33 ) + mat->_43;
	result->w = ( pos->x * mat->_14 ) + ( pos->y * mat->_24 ) + ( pos->z * mat->_34 ) + mat->_44;
}
void PRVector4::transform ( const PRVector4 * pos, const PRMatrix * mat, PRVector4 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + ( pos->z * mat->_31 ) + ( pos->w * mat->_41 );
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + ( pos->z * mat->_32 ) + ( pos->w * mat->_42 );
	result->z = ( pos->x * mat->_13 ) + ( pos->y * mat->_23 ) + ( pos->z * mat->_33 ) + ( pos->w * mat->_43 );
	result->w = ( pos->x * mat->_14 ) + ( pos->y * mat->_24 ) + ( pos->z * mat->_34 ) + ( pos->w * mat->_44 );
}
PRVector4 PRVector4::transform ( const PRVector2 & pos, const PRMatrix & mat ) { COPIEDMETHOD2 ( PRVector4, transform, &pos, &mat ); }
PRVector4 PRVector4::transform ( const PRVector3 & pos, const PRMatrix & mat ) { COPIEDMETHOD2 ( PRVector4, transform, &pos, &mat ); }
PRVector4 PRVector4::transform ( const PRVector4 & pos, const PRMatrix & mat ) { COPIEDMETHOD2 ( PRVector4, transform, &pos, &mat ); }

PRVector4 operator+ ( const PRVector4 & v1, const PRVector4 & v2 ) { return PRVector4::add ( v1, v2 ); }
PRVector4 operator- ( const PRVector4 & v1, const PRVector4 & v2 ) { return PRVector4::subtract ( v1, v2 ); }
PRVector4 operator- ( const PRVector4 & v1 ) { return PRVector4::negate ( v1 ); }
PRVector4 operator* ( const PRVector4 & v1, const PRVector4 & v2 ) { return PRVector4::multiply ( v1, v2 ); }
PRVector4 operator* ( const PRVector4 & v1, float v2 ) { return PRVector4::multiply ( v1, v2 ); }
PRVector4 operator* ( float v1, const PRVector4 & v2 ) { return PRVector4::multiply ( v1, v2 ); }
PRVector4 operator/ ( const PRVector4 & v1, const PRVector4 & v2 ) { return PRVector4::divide ( v1, v2 ); }
PRVector4 operator/ ( const PRVector4 & v1, float v2 ) { return PRVector4::divide ( v1, v2 ); }
bool operator== ( const PRVector4 & v1, const PRVector4 & v2 )
{
	return PRIsEquals ( v1.x, v2.x ) && PRIsEquals ( v1.y, v2.y ) && PRIsEquals ( v1.z, v2.z ) && PRIsEquals ( v1.w, v2.w );
}

PRQuaternion::PRQuaternion () : x ( 0 ), y ( 0 ), z ( 0 ), w ( 1 ) { }
PRQuaternion::PRQuaternion ( float v ) : x ( v ), y ( v ), z ( v ), w ( v ) { }
PRQuaternion::PRQuaternion ( float x, float y, float z, float w ) : x ( x ), y ( y ), z ( z ), w ( w ) {  }
PRQuaternion::PRQuaternion ( const PRVector2 & v, float z, float w ) : x ( v.x ), y ( v.y ), z ( z ), w ( w ) { }
PRQuaternion::PRQuaternion ( const PRVector3 & v, float w ) : x ( v.x ), y ( v.y ), z ( v.z ), w ( w ) { }
PRQuaternion::PRQuaternion ( const PRVector4 & v ) : x ( v.x ), y ( v.y ), z ( v.z ), w ( v.w ) { }
PRQuaternion::PRQuaternion ( float yaw, float pitch, float roll ) {
	float num9 = roll * 0.5f, num6 = sinf ( num9 ), num5 = cosf ( num9 );
	float num8 = pitch * 0.5f, num4 = sinf ( num8 ), num3 = cosf ( num8 );
	float num7 = yaw * 0.5f, num2 = sinf ( num7 ), num = cosf ( num7 );
	x = ( ( num * num4 ) * num5 ) + ( ( num2 * num3 ) * num6 );
	y = ( ( num2 * num3 ) * num5 ) - ( ( num * num4 ) * num6 );
	z = ( ( num * num3 ) * num6 ) - ( ( num2 * num4 ) * num5 );
	w = ( ( num * num3 ) * num5 ) + ( ( num2 * num4 ) * num6 );
}
PRQuaternion::PRQuaternion ( const PRMatrix & m ) {
	float num8 = ( m._11 + m._22 ) + m._33;
	if ( num8 > 0.0f ) {
		float num = sqrtf ( num8 + 1.0f );
		num = 0.5f / num;
		x = ( m._23 - m._32 ) * num; y = ( m._31 - m._13 ) * num;
		z = ( m._12 - m._21 ) * num; w = num * 0.5f;
	}
	else if ( ( m._11 >= m._22 ) && ( m._11 >= m._33 ) ) {
		float num7 = sqrtf ( ( ( 1.0f + m._11 ) - m._22 ) - m._33 );
		float num4 = 0.5f / num7;
		x = 0.5f * num7; y = ( m._12 + m._21 ) * num4;
		z = ( m._13 + m._31 ) * num4; w = ( m._23 - m._32 ) * num4;
	}
	else if ( m._22 > m._33 ) {
		float num6 = sqrtf ( ( ( 1.0f + m._22 ) - m._11 ) - m._33 );
		float num3 = 0.5f / num6;
		x = ( m._21 + m._12 ) * num3; y = 0.5f * num6;
		z = ( m._32 + m._23 ) * num3; w = ( m._31 - m._13 ) * num3;
	}
	else {
		float num5 = sqrtf ( ( ( 1.0f + m._33 ) - m._11 ) - m._22 );
		float num2 = 0.5f / num5;
		x = ( m._31 + m._13 ) * num2; y = ( m._32 + m._23 ) * num2;
		z = 0.5f * num5; w = ( m._12 - m._21 ) * num2;
	}
}

void PRQuaternion::lengthSquared ( float * result ) { lengthSquared ( this, result ); }
void PRQuaternion::length ( float * result ) { length ( this, result ); }
void PRQuaternion::normalize ( PRQuaternion * result ) { normalize ( this, result ); }
void PRQuaternion::invert ( PRQuaternion * result ) { invert ( this, result ); }

float PRQuaternion::lengthSquared () { float temp; lengthSquared ( this, &temp ); return temp; }
float PRQuaternion::length () { float temp; length ( this, &temp ); return temp; }
PRQuaternion PRQuaternion::normalize () { PRQuaternion temp; normalize ( this, &temp ); return temp; }
PRQuaternion PRQuaternion::invert () { PRQuaternion temp; invert ( this, &temp ); return temp; }

void PRQuaternion::lengthSquared ( const PRQuaternion * v, float * result ) { *result = v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w; }
void PRQuaternion::length ( const PRQuaternion * v, float * result ) { float ls; lengthSquared ( v, &ls ); *result = sqrtf ( ls ); }
void PRQuaternion::normalize ( const PRQuaternion * v, PRQuaternion * result ) {
	float len; length ( v, &len );
	result->x = v->x / len;
	result->y = v->y / len;
	result->z = v->z / len;
	result->w = v->w / len;
}
void PRQuaternion::invert ( const PRQuaternion * v, PRQuaternion * result ) {
	float len; length ( v, &len );
	result->x = -v->x / len;
	result->y = -v->y / len;
	result->z = -v->z / len;
	result->w = v->w / len;
}

float PRQuaternion::lengthSquared ( const PRQuaternion & v ) { COPIEDMETHOD1 ( float, lengthSquared, &v ); }
float PRQuaternion::length ( const PRQuaternion & v ) { COPIEDMETHOD1 ( float, length, &v ); }
PRQuaternion PRQuaternion::normalize ( const PRQuaternion & v ) { COPIEDMETHOD1 ( PRQuaternion, normalize, &v ); }
PRQuaternion PRQuaternion::invert ( const PRQuaternion & v ) { COPIEDMETHOD1 ( PRQuaternion, invert, &v ); }

void PRQuaternion::add ( const PRQuaternion * v1, const PRQuaternion * v2, PRQuaternion * result ) {
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;
	result->w = v1->w + v2->w;
}
void PRQuaternion::subtract ( const PRQuaternion * v1, const PRQuaternion * v2, PRQuaternion * result ) {
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
	result->z = v1->z - v2->z;
	result->z = v1->w - v2->w;
}
void PRQuaternion::negate ( const PRQuaternion * v1, PRQuaternion * result ) {
	result->x = -v1->x;
	result->y = -v1->y;
	result->z = -v1->z;
	result->w = -v1->w;
}
void PRQuaternion::multiply ( const PRQuaternion * v1, const PRQuaternion * v2, PRQuaternion * result ) {
	result->x = v1->x * v2->x;
	result->y = v1->y * v2->y;
	result->z = v1->z * v2->z;
	result->z = v1->w * v2->w;
}
void PRQuaternion::multiply ( const PRQuaternion * v1, float v2, PRQuaternion * result ) {
	result->x = v1->x * v2;
	result->y = v1->y * v2;
	result->z = v1->z * v2;
	result->z = v1->w * v2;
}
void PRQuaternion::multiply ( float v1, const PRQuaternion * v2, PRQuaternion * result ) {
	result->x = v1 * v2->x;
	result->y = v1 * v2->y;
	result->z = v1 * v2->z;
	result->z = v1 * v2->w;
}
void PRQuaternion::divide ( const PRQuaternion * v1, const PRQuaternion * v2, PRQuaternion * result ) {
	result->x = v1->x / v2->x;
	result->y = v1->y / v2->y;
	result->z = v1->z / v2->z;
	result->z = v1->w / v2->w;
}
void PRQuaternion::divide ( const PRQuaternion * v1, float v2, PRQuaternion * result ) {
	result->x = v1->x / v2;
	result->y = v1->y / v2;
	result->z = v1->z / v2;
	result->z = v1->w / v2;
}
void PRQuaternion::dot ( const PRQuaternion * v1, const PRQuaternion * v2, float * result ) {
	*result = ( v1->x * v2->x ) + ( v1->y * v2->y ) + ( v1->z * v2->z ) + ( v1->w * v2->w );
}
void PRQuaternion::dot ( const PRQuaternion * v1, float v2, float * result ) {
	*result = ( v1->x * v2 ) + ( v1->y * v2 ) + ( v1->z * v2 ) + ( v1->w * v2 );
}
PRQuaternion PRQuaternion::add ( const PRQuaternion & v1, const PRQuaternion & v2 ) { COPIEDMETHOD2 ( PRQuaternion, add, &v1, &v2 ); }
PRQuaternion PRQuaternion::subtract ( const PRQuaternion & v1, const PRQuaternion & v2 ) { COPIEDMETHOD2 ( PRQuaternion, subtract, &v1, &v2 ); }
PRQuaternion PRQuaternion::negate ( const PRQuaternion & v1 ) { COPIEDMETHOD1 ( PRQuaternion, negate, &v1 ); }
PRQuaternion PRQuaternion::multiply ( const PRQuaternion & v1, const PRQuaternion & v2 ) { COPIEDMETHOD2 ( PRQuaternion, multiply, &v1, &v2 ); }
PRQuaternion PRQuaternion::multiply ( const PRQuaternion & v1, float v2 ) { COPIEDMETHOD2 ( PRQuaternion, multiply, &v1, v2 ); }
PRQuaternion PRQuaternion::multiply ( float v1, const PRQuaternion & v2 ) { COPIEDMETHOD2 ( PRQuaternion, multiply, v1, &v2 ); }
PRQuaternion PRQuaternion::divide ( const PRQuaternion & v1, const PRQuaternion & v2 ) { COPIEDMETHOD2 ( PRQuaternion, divide, &v1, &v2 ); }
PRQuaternion PRQuaternion::divide ( const PRQuaternion & v1, float v2 ) { COPIEDMETHOD2 ( PRQuaternion, divide, &v1, v2 ); }
float PRQuaternion::dot ( const PRQuaternion & v1, const PRQuaternion & v2 ) { COPIEDMETHOD2 ( float, dot, &v1, &v2 ); }
float PRQuaternion::dot ( const PRQuaternion & v1, float v2 ) { COPIEDMETHOD2 ( float, dot, &v1, v2 ); }

PRQuaternion operator+ ( const PRQuaternion & v1, const PRQuaternion & v2 ) { return PRQuaternion::add ( v1, v2 ); }
PRQuaternion operator- ( const PRQuaternion & v1, const PRQuaternion & v2 ) { return PRQuaternion::subtract ( v1, v2 ); }
PRQuaternion operator- ( const PRQuaternion & v1 ) { return PRQuaternion::negate ( v1 ); }
PRQuaternion operator* ( const PRQuaternion & v1, const PRQuaternion & v2 ) { return PRQuaternion::multiply ( v1, v2 ); }
PRQuaternion operator* ( const PRQuaternion & v1, float v2 ) { return PRQuaternion::multiply ( v1, v2 ); }
PRQuaternion operator* ( float v1, const PRQuaternion & v2 ) { return PRQuaternion::multiply ( v1, v2 ); }
PRQuaternion operator/ ( const PRQuaternion & v1, const PRQuaternion & v2 ) { return PRQuaternion::divide ( v1, v2 ); }
PRQuaternion operator/ ( const PRQuaternion & v1, float v2 ) { return PRQuaternion::divide ( v1, v2 ); }
bool operator== ( const PRQuaternion & v1, const PRQuaternion & v2 ) {
	return PRIsEquals ( v1.x, v2.x ) && PRIsEquals ( v1.y, v2.y ) && PRIsEquals ( v1.z, v2.z ) && PRIsEquals ( v1.w, v2.w );
}

PRMatrix::PRMatrix () : _11 ( 1 ), _12 ( 0 ), _13 ( 0 ), _14 ( 0 ), _21 ( 0 ), _22 ( 1 ), _23 ( 0 ), _24 ( 0 ),
_31 ( 0 ), _32 ( 0 ), _33 ( 1 ), _34 ( 0 ), _41 ( 0 ), _42 ( 0 ), _43 ( 0 ), _44 ( 1 ) { }
PRMatrix::PRMatrix ( float v ) : _11 ( v ), _12 ( v ), _13 ( v ), _14 ( v ), _21 ( v ), _22 ( v ), _23 ( v ), _24 ( v ),
_31 ( v ), _32 ( v ), _33 ( v ), _34 ( v ), _41 ( v ), _42 ( v ), _43 ( v ), _44 ( v ) { }
PRMatrix::PRMatrix ( float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44 )
	: _11 ( _11 ), _12 ( _12 ), _13 ( _13 ), _14 ( _14 ), _21 ( _21 ), _22 ( _22 ), _23 ( _23 ), _24 ( _24 ),
	_31 ( _31 ), _32 ( _32 ), _33 ( _33 ), _34 ( _34 ), _41 ( _41 ), _42 ( _42 ), _43 ( _43 ), _44 ( _44 ) { }
PRMatrix::PRMatrix ( PRVector4 & c1, PRVector4 & c2, PRVector4 & c3, PRVector4 & c4 )
	: _11 ( c1.x ), _12 ( c1.y ), _13 ( c1.z ), _14 ( c1.w ), _21 ( c2.x ), _22 ( c2.y ), _23 ( c2.z ), _24 ( c2.w ),
	_31 ( c3.x ), _32 ( c3.y ), _33 ( c3.z ), _34 ( c3.w ), _41 ( c4.x ), _42 ( c4.y ), _43 ( c4.z ), _44 ( c4.w ) { }
PRMatrix::PRMatrix ( PRQuaternion & q ) {
	float num9 = q.x * q.x, num8 = q.y * q.y, num7 = q.z * q.z, num6 = q.x * q.y;
	float num5 = q.z * q.w, num4 = q.z * q.x, num3 = q.y * q.w, num2 = q.y * q.z;
	float num1 = q.x * q.w;
	_11 = 1.0f - ( 2.0f * ( num8 + num7 ) ); _12 = 2.0f * ( num6 + num5 ); _13 = 2.0f * ( num4 - num3 ); _14 = 0;
	_21 = 2.0f * ( num6 - num5 ); _22 = 1.0f - ( 2.0f * ( num7 + num9 ) ); _23 = 2.0f * ( num2 + num1 ); _24 = 0;
	_31 = 2.0f * ( num4 + num3 ); _32 = 2.0f * ( num2 - num1 ); _33 = 1.0f - ( 2.0f * ( num8 + num9 ) ); _34 = 0;
	_41 = 0; _42 = 0; _43 = 0; _44 = 1;
}

void PRMatrix::invert ( PRMatrix * result ) { PRMatrix::invert ( this, result ); }
void PRMatrix::transpose ( PRMatrix * result ) { PRMatrix::transpose ( this, result ); }
void PRMatrix::determinant ( float * result ) { PRMatrix::determinant ( this, result ); }

PRMatrix PRMatrix::invert () { PRMatrix temp; invert ( &temp ); return temp; }
PRMatrix PRMatrix::transpose () { PRMatrix temp; transpose ( &temp ); return temp; }
float PRMatrix::determinant () { float temp; determinant ( &temp ); return temp; }

void PRMatrix::invert ( const PRMatrix * m, PRMatrix * result ) {
	float num1 = m->_11, num2 = m->_12, num3 = m->_13, num4 = m->_14, num5 = m->_21, num6 = m->_22, num7 = m->_23, num8 = m->_24;
	float num9 = m->_31, num10 = m->_32, num11 = m->_33, num12 = m->_34, num13 = m->_41, num14 = m->_42, num15 = m->_43, num16 = m->_44;
	float num17 = num11 * num16 - num12 * num15, num18 = num10 * num16 - num12 * num14, num19 = num10 * num15 - num11 * num14;
	float num20 = num9 * num16 - num12 * num13, num21 = num9 * num15 - num11 * num13, num22 = num9 * num14 - num10 * num13;
	float num23 = num6 * num17 - num7 * num18 + num8 * num19, num24 = -( num5 * num17 - num7 * num20 + num8 * num21 );
	float num25 = num5 * num18 - num6 * num20 + num8 * num22, num26 = -( num5 * num19 - num6 * num21 + num7 * num22 );
	float num27 = 1.0f / ( num1 * num23 + num2 * num24 + num3 * num25 + num4 * num26 );
	result->_11 = num23 * num27; result->_21 = num24 * num27; result->_31 = num25 * num27; result->_41 = num26 * num27;
	result->_12 = -( num2 * num17 - num3 * num18 + num4 * num19 ) * num27;
	result->_22 = ( num1 * num17 - num3 * num20 + num4 * num21 ) * num27;
	result->_32 = -( num1 * num18 - num2 * num20 + num4 * num22 ) * num27;
	result->_42 = ( num1 * num19 - num2 * num21 + num3 * num22 ) * num27;
	float num28 = num7 * num16 - num8 * num15, num29 = num6 * num16 - num8 * num14, num30 = num6 * num15 - num7 * num14;
	float num31 = num5 * num16 - num8 * num13, num32 = num5 * num15 - num7 * num13, num33 = num5 * num14 - num6 * num13;
	result->_13 = ( num2 * num28 - num3 * num29 + num4 * num30 ) * num27;
	result->_23 = -( num1 * num28 - num3 * num31 + num4 * num32 ) * num27;
	result->_33 = ( num1 * num29 - num2 * num31 + num4 * num33 ) * num27;
	result->_43 = -( num1 * num30 - num2 * num32 + num3 * num33 ) * num27;
	float num34 = num7 * num12 - num8 * num11, num35 = num6 * num12 - num8 * num10, num36 = num6 * num11 - num7 * num10;
	float num37 = num5 * num12 - num8 * num9, num38 = num5 * num11 - num7 * num9, num39 = num5 * num10 - num6 * num9;
	result->_14 = -( num2 * num34 - num3 * num35 + num4 * num36 ) * num27;
	result->_24 = ( num1 * num34 - num3 * num37 + num4 * num38 ) * num27;
	result->_34 = -( num1 * num35 - num2 * num37 + num4 * num39 ) * num27;
	result->_44 = ( num1 * num36 - num2 * num38 + num3 * num39 ) * num27;
}
void PRMatrix::transpose ( const PRMatrix * m, PRMatrix * result ) {
	result->_11 = m->_11; result->_12 = m->_21; result->_13 = m->_31; result->_14 = m->_41;
	result->_21 = m->_12; result->_22 = m->_22; result->_23 = m->_32; result->_24 = m->_42;
	result->_31 = m->_13; result->_32 = m->_23; result->_33 = m->_33; result->_34 = m->_43;
	result->_41 = m->_14; result->_42 = m->_24; result->_43 = m->_34; result->_44 = m->_44;
}
void PRMatrix::determinant ( const PRMatrix * m, float * result ) {
	float num22 = m->_11, num21 = m->_12, num20 = m->_13, num19 = m->_14, num12 = m->_21, num11 = m->_22, num10 = m->_23, num9 = m->_24;
	float num8 = m->_31, num7 = m->_32, num6 = m->_33, num5 = m->_34, num4 = m->_41, num3 = m->_42, num2 = m->_43, num = m->_44;
	float num18 = ( num6 * num ) - ( num5 * num2 ), num17 = ( num7 * num ) - ( num5 * num3 );
	float num16 = ( num7 * num2 ) - ( num6 * num3 ), num15 = ( num8 * num ) - ( num5 * num4 );
	float num14 = ( num8 * num2 ) - ( num6 * num4 ), num13 = ( num8 * num3 ) - ( num7 * num4 );
	*result = ( ( ( ( num22 * ( ( ( num11 * num18 ) - ( num10 * num17 ) ) + ( num9 * num16 ) ) ) -
		( num21 * ( ( ( num12 * num18 ) - ( num10 * num15 ) ) + ( num9 * num14 ) ) ) ) +
		( num20 * ( ( ( num12 * num17 ) - ( num11 * num15 ) ) + ( num9 * num13 ) ) ) ) -
		( num19 * ( ( ( num12 * num16 ) - ( num11 * num14 ) ) + ( num10 * num13 ) ) ) );
}
PRMatrix PRMatrix::invert ( const PRMatrix & m ) { COPIEDMETHOD1 ( PRMatrix, invert, &m ); }
PRMatrix PRMatrix::transpose ( const PRMatrix & m ) { COPIEDMETHOD1 ( PRMatrix, transpose, &m ); }
float PRMatrix::determinant ( const PRMatrix & m ) { COPIEDMETHOD1 ( float, determinant, &m ); }

void PRMatrix::add ( const PRMatrix * v1, const PRMatrix * v2, PRMatrix * result ) {
	result->_11 = v1->_11 + v2->_11; result->_12 = v1->_12 + v2->_12; result->_13 = v1->_13 + v2->_13; result->_14 = v1->_14 + v2->_14;
	result->_21 = v1->_21 + v2->_21; result->_22 = v1->_22 + v2->_22; result->_23 = v1->_23 + v2->_23; result->_24 = v1->_24 + v2->_24;
	result->_31 = v1->_31 + v2->_31; result->_32 = v1->_32 + v2->_32; result->_33 = v1->_33 + v2->_33; result->_34 = v1->_34 + v2->_34;
	result->_41 = v1->_41 + v2->_41; result->_42 = v1->_42 + v2->_42; result->_43 = v1->_43 + v2->_43; result->_44 = v1->_44 + v2->_44;
}
void PRMatrix::subtract ( const PRMatrix * v1, const PRMatrix * v2, PRMatrix * result ) {
	result->_11 = v1->_11 - v2->_11; result->_12 = v1->_12 - v2->_12; result->_13 = v1->_13 - v2->_13; result->_14 = v1->_14 - v2->_14;
	result->_21 = v1->_21 - v2->_21; result->_22 = v1->_22 - v2->_22; result->_23 = v1->_23 - v2->_23; result->_24 = v1->_24 - v2->_24;
	result->_31 = v1->_31 - v2->_31; result->_32 = v1->_32 - v2->_32; result->_33 = v1->_33 - v2->_33; result->_34 = v1->_34 - v2->_34;
	result->_41 = v1->_41 - v2->_41; result->_42 = v1->_42 - v2->_42; result->_43 = v1->_43 - v2->_43; result->_44 = v1->_44 - v2->_44;
}
void PRMatrix::negate ( const PRMatrix * v1, PRMatrix * result ) {
	result->_11 = -v1->_11; result->_12 = -v1->_12; result->_13 = -v1->_13; result->_14 = -v1->_14;
	result->_21 = -v1->_21; result->_22 = -v1->_22; result->_23 = -v1->_23; result->_24 = -v1->_24;
	result->_31 = -v1->_31; result->_32 = -v1->_32; result->_33 = -v1->_33; result->_34 = -v1->_34;
	result->_41 = -v1->_41; result->_42 = -v1->_42; result->_43 = -v1->_43; result->_44 = -v1->_44;
}
void PRMatrix::multiply ( const PRMatrix * v1, const PRMatrix * v2, PRMatrix * result ) {
	result->_11 = ( ( ( v1->_11 * v2->_11 ) + ( v1->_12 * v2->_21 ) ) + ( v1->_13 * v2->_31 ) ) + ( v1->_14 * v2->_41 );
	result->_12 = ( ( ( v1->_11 * v2->_12 ) + ( v1->_12 * v2->_22 ) ) + ( v1->_13 * v2->_32 ) ) + ( v1->_14 * v2->_42 );
	result->_13 = ( ( ( v1->_11 * v2->_13 ) + ( v1->_12 * v2->_23 ) ) + ( v1->_13 * v2->_33 ) ) + ( v1->_14 * v2->_43 );
	result->_14 = ( ( ( v1->_11 * v2->_14 ) + ( v1->_12 * v2->_24 ) ) + ( v1->_13 * v2->_34 ) ) + ( v1->_14 * v2->_44 );
	result->_21 = ( ( ( v1->_21 * v2->_11 ) + ( v1->_22 * v2->_21 ) ) + ( v1->_23 * v2->_31 ) ) + ( v1->_24 * v2->_41 );
	result->_22 = ( ( ( v1->_21 * v2->_12 ) + ( v1->_22 * v2->_22 ) ) + ( v1->_23 * v2->_32 ) ) + ( v1->_24 * v2->_42 );
	result->_23 = ( ( ( v1->_21 * v2->_13 ) + ( v1->_22 * v2->_23 ) ) + ( v1->_23 * v2->_33 ) ) + ( v1->_24 * v2->_43 );
	result->_24 = ( ( ( v1->_21 * v2->_14 ) + ( v1->_22 * v2->_24 ) ) + ( v1->_23 * v2->_34 ) ) + ( v1->_24 * v2->_44 );
	result->_31 = ( ( ( v1->_31 * v2->_11 ) + ( v1->_32 * v2->_21 ) ) + ( v1->_33 * v2->_31 ) ) + ( v1->_34 * v2->_41 );
	result->_32 = ( ( ( v1->_31 * v2->_12 ) + ( v1->_32 * v2->_22 ) ) + ( v1->_33 * v2->_32 ) ) + ( v1->_34 * v2->_42 );
	result->_33 = ( ( ( v1->_31 * v2->_13 ) + ( v1->_32 * v2->_23 ) ) + ( v1->_33 * v2->_33 ) ) + ( v1->_34 * v2->_43 );
	result->_34 = ( ( ( v1->_31 * v2->_14 ) + ( v1->_32 * v2->_24 ) ) + ( v1->_33 * v2->_34 ) ) + ( v1->_34 * v2->_44 );
	result->_41 = ( ( ( v1->_41 * v2->_11 ) + ( v1->_42 * v2->_21 ) ) + ( v1->_43 * v2->_31 ) ) + ( v1->_44 * v2->_41 );
	result->_42 = ( ( ( v1->_41 * v2->_12 ) + ( v1->_42 * v2->_22 ) ) + ( v1->_43 * v2->_32 ) ) + ( v1->_44 * v2->_42 );
	result->_43 = ( ( ( v1->_41 * v2->_13 ) + ( v1->_42 * v2->_23 ) ) + ( v1->_43 * v2->_33 ) ) + ( v1->_44 * v2->_43 );
	result->_44 = ( ( ( v1->_41 * v2->_14 ) + ( v1->_42 * v2->_24 ) ) + ( v1->_43 * v2->_34 ) ) + ( v1->_44 * v2->_44 );
}
void PRMatrix::multiply ( const PRMatrix * v1, float v2, PRMatrix * result ) {
	result->_11 = v1->_11 * v2; result->_12 = v1->_12 * v2; result->_13 = v1->_13 * v2; result->_14 = v1->_14 * v2;
	result->_21 = v1->_21 * v2; result->_22 = v1->_22 * v2; result->_23 = v1->_23 * v2; result->_24 = v1->_24 * v2;
	result->_31 = v1->_31 * v2; result->_32 = v1->_32 * v2; result->_33 = v1->_33 * v2; result->_34 = v1->_34 * v2;
	result->_41 = v1->_41 * v2; result->_42 = v1->_42 * v2; result->_43 = v1->_43 * v2; result->_44 = v1->_44 * v2;
}
void PRMatrix::multiply ( float v1, const PRMatrix * v2, PRMatrix * result ) {
	result->_11 = v2->_11 * v1; result->_12 = v2->_12 * v1; result->_13 = v2->_13 * v1; result->_14 = v2->_14 * v1;
	result->_21 = v2->_21 * v1; result->_22 = v2->_22 * v1; result->_23 = v2->_23 * v1; result->_24 = v2->_24 * v1;
	result->_31 = v2->_31 * v1; result->_32 = v2->_32 * v1; result->_33 = v2->_33 * v1; result->_34 = v2->_34 * v1;
	result->_41 = v2->_41 * v1; result->_42 = v2->_42 * v1; result->_43 = v2->_43 * v1; result->_44 = v2->_44 * v1;
}
void PRMatrix::divide ( const PRMatrix * v1, const PRMatrix * v2, PRMatrix * result ) {
	result->_11 = v1->_11 / v2->_11; result->_12 = v1->_12 / v2->_12; result->_13 = v1->_13 / v2->_13; result->_14 = v1->_14 / v2->_14;
	result->_21 = v1->_21 / v2->_21; result->_22 = v1->_22 / v2->_22; result->_23 = v1->_23 / v2->_23; result->_24 = v1->_24 / v2->_24;
	result->_31 = v1->_31 / v2->_31; result->_32 = v1->_32 / v2->_32; result->_33 = v1->_33 / v2->_33; result->_34 = v1->_34 / v2->_34;
	result->_41 = v1->_41 / v2->_41; result->_42 = v1->_42 / v2->_42; result->_43 = v1->_43 / v2->_43; result->_44 = v1->_44 / v2->_44;
}
void PRMatrix::divide ( const PRMatrix * v1, float v2, PRMatrix * result ) {
	result->_11 = v1->_11 / v2; result->_12 = v1->_12 / v2; result->_13 = v1->_13 / v2; result->_14 = v1->_14 / v2;
	result->_21 = v1->_21 / v2; result->_22 = v1->_22 / v2; result->_23 = v1->_23 / v2; result->_24 = v1->_24 / v2;
	result->_31 = v1->_31 / v2; result->_32 = v1->_32 / v2; result->_33 = v1->_33 / v2; result->_34 = v1->_34 / v2;
	result->_41 = v1->_41 / v2; result->_42 = v1->_42 / v2; result->_43 = v1->_43 / v2; result->_44 = v1->_44 / v2;
}

PRMatrix PRMatrix::add ( const PRMatrix & v1, const PRMatrix & v2 ) { COPIEDMETHOD2 ( PRMatrix, add, &v1, &v2 ); }
PRMatrix PRMatrix::subtract ( const PRMatrix & v1, const PRMatrix & v2 ) { COPIEDMETHOD2 ( PRMatrix, subtract, &v1, &v2 ); }
PRMatrix PRMatrix::negate ( const PRMatrix & v1 ) { COPIEDMETHOD1 ( PRMatrix, negate, &v1 ); }
PRMatrix PRMatrix::multiply ( const PRMatrix & v1, const PRMatrix & v2 ) { COPIEDMETHOD2 ( PRMatrix, multiply, &v1, &v2 ); }
PRMatrix PRMatrix::multiply ( const PRMatrix & v1, float v2 ) { COPIEDMETHOD2 ( PRMatrix, multiply, &v1, v2 ); }
PRMatrix PRMatrix::multiply ( float v1, const PRMatrix & v2 ) { COPIEDMETHOD2 ( PRMatrix, multiply, v1, &v2 ); }
PRMatrix PRMatrix::divide ( const PRMatrix & v1, const PRMatrix & v2 ) { COPIEDMETHOD2 ( PRMatrix, divide, &v1, &v2 ); }
PRMatrix PRMatrix::divide ( const PRMatrix & v1, float v2 ) { COPIEDMETHOD2 ( PRMatrix, divide, &v1, v2 ); }

void PRMatrix::createTranslate ( const PRVector3 * v, PRMatrix * result ) {
	*result = PRMatrix (
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		v->x, v->y, v->z, 1
	);
}
void PRMatrix::createScale ( const PRVector3 * v, PRMatrix * result ) {
	*result = PRMatrix (
		v->x, 0, 0, 0,
		0, v->y, 0, 0,
		0, 0, v->z, 0,
		0, 0, 0, 1
	);
}
void PRMatrix::createRotationX ( float r, PRMatrix * result ) {
	float v1 = cosf ( r ), v2 = sinf ( r );
	*result = PRMatrix (
		1, 0, 0, 0,
		0, v1, v2, 0,
		0, -v2, v1, 0,
		0, 0, 0, 1
	);
}
void PRMatrix::createRotationY ( float r, PRMatrix * result ) {
	float v1 = cosf ( r ), v2 = sinf ( r );
	*result = PRMatrix (
		v1, 0, -v2, 0,
		0, 1, 0, 0,
		v2, 0, v1, 0,
		0, 0, 0, 1
	);
}
void PRMatrix::createRotationZ ( float r, PRMatrix * result ) {
	float v1 = cosf ( r ), v2 = sinf ( r );
	*result = PRMatrix (
		v1, v2, 0, 0,
		-v2, v1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}
PRMatrix PRMatrix::createTranslate ( const PRVector3 & v ) {
	PRMatrix temp;
	createTranslate ( &v, &temp );
	return temp;
}
PRMatrix PRMatrix::createScale ( const PRVector3 & v ) {
	PRMatrix temp;
	createScale ( &v, &temp );
	return temp;
}
PRMatrix PRMatrix::createRotationX ( float r ) {
	PRMatrix temp;
	createRotationX ( r, &temp );
	return temp;
}
PRMatrix PRMatrix::createRotationY ( float r ) {
	PRMatrix temp;
	createRotationY ( r, &temp );
	return temp;
}
PRMatrix PRMatrix::createRotationZ ( float r ) {
	PRMatrix temp;
	createRotationZ ( r, &temp );
	return temp;
}
void PRMatrix::createLookAtLH ( const PRVector3 * position, const PRVector3 * target, const PRVector3 * upVector, PRMatrix * result ) {
	PRVector3 zaxis;
	PRVector3::subtract ( target, position, &zaxis );
	zaxis.normalize ( &zaxis );
	PRVector3 xaxis;
	PRVector3::cross ( upVector, &zaxis, &xaxis );
	xaxis.normalize ( &xaxis );
	PRVector3 yaxis;
	PRVector3::cross ( &zaxis, &xaxis, &yaxis );
	*result = PRMatrix (
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		-PRVector3::dot ( xaxis, *position ), -PRVector3::dot ( yaxis, *position ), -PRVector3::dot ( zaxis, *position ), 1 );
}
void PRMatrix::createLookAtRH ( const PRVector3 * position, const PRVector3 * target, const PRVector3 * upVector, PRMatrix * result ) {
	PRVector3 zaxis;
	PRVector3::subtract ( position, target, &zaxis );
	zaxis.normalize ( &zaxis );
	PRVector3 xaxis;
	PRVector3::cross ( upVector, &zaxis, &xaxis );
	xaxis.normalize ( &xaxis );
	PRVector3 yaxis;
	PRVector3::cross ( &zaxis, &xaxis, &yaxis );
	*result = PRMatrix (
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		-PRVector3::dot ( xaxis, *position ), -PRVector3::dot ( yaxis, *position ), -PRVector3::dot ( zaxis, *position ), 1 );
}
PRMatrix PRMatrix::createLookAtLH ( const PRVector3 & position, const PRVector3 & target, const PRVector3 & upVector ) {
	PRMatrix temp;
	createLookAtLH ( &position, &target, &upVector, &temp );
	return temp;
}
PRMatrix PRMatrix::createLookAtRH ( const PRVector3 & position, const PRVector3 & target, const PRVector3 & upVector ) {
	PRMatrix temp;
	createLookAtRH ( &position, &target, &upVector, &temp );
	return temp;
}
void PRMatrix::createOrthographicLH ( float w, float h, float zn, float zf, PRMatrix * result ) {
	*result = PRMatrix (
		2 / w, 0, 0, 0,
		0, 2 / h, 0, 0,
		0, 0, 1 / ( zf - zn ), 0,
		0, 0, -zn / ( zf - zn ), 0
	);
}
void PRMatrix::createOrthographicRH ( float w, float h, float zn, float zf, PRMatrix * result ) {
	*result = PRMatrix (
		2 / w, 0, 0, 0,
		0, 2 / h, 0, 0,
		0, 0, 1 / ( zn - zf ), 0,
		0, 0, -zn / ( zn - zf ), 0
	);
}
void PRMatrix::createOrthographicOffCenterLH ( float l, float r, float b, float t, float zn, float zf, PRMatrix * result ) {
	*result = PRMatrix (
		2 / ( r - l ), 0, 0, 0,
		0, 2 / ( t - b ), 0, 0,
		0, 0, 1 / ( zf - zn ), 0,
		( l + r ) / ( l - r ), ( t + b ) / ( b - t ), -zn / ( zf - zn ), 1
	);
}
void PRMatrix::createOrthographicOffCenterRH ( float l, float r, float b, float t, float zn, float zf, PRMatrix * result ) {
	*result = PRMatrix (
		2 / ( r - l ), 0, 0, 0,
		0, 2 / ( t - b ), 0, 0,
		0, 0, 1 / ( zn - zf ), 0,
		( l + r ) / ( l - r ), ( t + b ) / ( b - t ), -zn / ( zn - zf ), 1
	);
}
void PRMatrix::createPerspectiveLH ( float w, float h, float zn, float zf, PRMatrix * result ) {
	*result = PRMatrix (
		2 * zn / w, 0, 0, 0,
		0, 2 * zn / h, 0, 0,
		0, 0, zf / ( zf - zn ), 1,
		0, 0, zn * zf / ( zf - zn ), 0
	);
}
void PRMatrix::createPerspectiveRH ( float w, float h, float zn, float zf, PRMatrix * result ) {
	*result = PRMatrix (
		2 * zn / w, 0, 0, 0,
		0, 2 * zn / h, 0, 0,
		0, 0, zf / ( zn - zf ), 1,
		0, 0, zn * zf / ( zn - zf ), 0
	);
}
void PRMatrix::createPerspectiveOffCenterLH ( float l, float r, float b, float t, float zn, float zf, PRMatrix * result ) {
	*result = PRMatrix (
		2 * zn / ( r - l ), 0, 0, 0,
		0, 2 * zn / ( t - b ), 0, 0,
		( l + r ) / ( l - r ), ( t + b ) / ( b - t ), zf / ( zf - zn ), 1,
		0, 0, zn * zf / ( zf - zn ), 1 );
}
void PRMatrix::createPerspectiveOffCenterRH ( float l, float r, float b, float t, float zn, float zf, PRMatrix * result ) {
	*result = PRMatrix (
		2 * zn / ( r - l ), 0, 0, 0,
		0, 2 * zn / ( t - b ), 0, 0,
		( l + r ) / ( l - r ), ( t + b ) / ( t - b ), zf / ( zn - zf ), 1,
		0, 0, zn * zf / ( zn - zf ), 1 );
}
void PRMatrix::createPerspectiveFieldOfViewLH ( float fov, float aspect, float zn, float zf, PRMatrix * result ) {
	float ys = 1 / tanf ( fov * 0.5f ), xs = ys / aspect;
	*result = PRMatrix (
		xs, 0, 0, 0,
		0, ys, 0, 0,
		0, 0, zf / ( zf - zn ), 1,
		0, 0, ( -zn * zf ) / ( zf - zn ), 0
	);
}
void PRMatrix::createPerspectiveFieldOfViewRH ( float fov, float aspect, float zn, float zf, PRMatrix * result ) {
	float ys = 1 / tanf ( fov * 0.5f ), xs = ys / aspect;
	*result = PRMatrix (
		xs, 0, 0, 0,
		0, ys, 0, 0,
		0, 0, zf / ( zn - zf ), -1,
		0, 0, ( zn * zf ) / ( zn - zf ), 0
	);
}
PRMatrix PRMatrix::createOrthographicLH ( float w, float h, float zn, float zf ) {
	PRMatrix temp;
	createOrthographicLH ( w, h, zn, zf, &temp );
	return temp;
}
PRMatrix PRMatrix::createOrthographicRH ( float w, float h, float zn, float zf ) {
	PRMatrix temp;
	createOrthographicRH ( w, h, zn, zf, &temp );
	return temp;
}
PRMatrix PRMatrix::createOrthographicOffCenterLH ( float l, float r, float b, float t, float zn, float zf ) {
	PRMatrix temp;
	createOrthographicOffCenterLH ( l, r, b, t, zn, zf, &temp );
	return temp;
}
PRMatrix PRMatrix::createOrthographicOffCenterRH ( float l, float r, float b, float t, float zn, float zf ) {
	PRMatrix temp;
	createOrthographicOffCenterRH ( l, r, b, t, zn, zf, &temp );
	return temp;
}
PRMatrix PRMatrix::createPerspectiveLH ( float w, float h, float zn, float zf ) {
	PRMatrix temp;
	createPerspectiveLH ( w, h, zn, zf, &temp );
	return temp;
}
PRMatrix PRMatrix::createPerspectiveRH ( float w, float h, float zn, float zf ) {
	PRMatrix temp;
	createPerspectiveRH ( w, h, zn, zf, &temp );
	return temp;
}
PRMatrix PRMatrix::createPerspectiveOffCenterLH ( float l, float r, float b, float t, float zn, float zf ) {
	PRMatrix temp;
	createPerspectiveOffCenterLH ( l, r, b, t, zn, zf, &temp );
	return temp;
}
PRMatrix PRMatrix::createPerspectiveOffCenterRH ( float l, float r, float b, float t, float zn, float zf ) {
	PRMatrix temp;
	createPerspectiveOffCenterRH ( l, r, b, t, zn, zf, &temp );
	return temp;
}
PRMatrix PRMatrix::createPerspectiveFieldOfViewLH ( float fov, float aspect, float zn, float zf ) {
	PRMatrix temp;
	createPerspectiveFieldOfViewLH ( fov, aspect, zn, zf, &temp );
	return temp;
}
PRMatrix PRMatrix::createPerspectiveFieldOfViewRH ( float fov, float aspect, float zn, float zf ) {
	PRMatrix temp;
	createPerspectiveFieldOfViewRH ( fov, aspect, zn, zf, &temp );
	return temp;
}
void PRMatrix::createBillboard ( const PRVector3 * objPos, const PRVector3 * camPos, const PRVector3 * camUpVec,
	const PRVector3 * camForwardVec, PRMatrix * result ) {
	PRVector3 vector, vector2, vector3;
	vector = *objPos - *camPos;
	float num = vector.lengthSquared ();
	if ( num < 0.0001f ) vector = -*camForwardVec;
	else vector = vector * ( 1.0f / sqrtf ( num ) );

	PRVector3::cross ( camUpVec, &vector, &vector3 );
	vector3 = vector3.normalize ();
	PRVector3::cross ( &vector, &vector3, &vector2 );
	*result = PRMatrix (
		vector3.x, vector3.y, vector3.z, 0,
		vector2.x, vector2.y, vector2.z, 0,
		vector.x, vector.y, vector.z, 0,
		objPos->x, objPos->y, objPos->z, 1
	);
}

PRMatrix operator+ ( const PRMatrix & v1, const PRMatrix & v2 ) { return PRMatrix::add ( v1, v2 ); }
PRMatrix operator- ( const PRMatrix & v1, const PRMatrix & v2 ) { return PRMatrix::subtract ( v1, v2 ); }
PRMatrix operator- ( const PRMatrix & v1 ) { return PRMatrix::negate ( v1 ); }
PRMatrix operator* ( const PRMatrix & v1, const PRMatrix & v2 ) { return PRMatrix::multiply ( v1, v2 ); }
PRMatrix operator* ( const PRMatrix & v1, float v2 ) { return PRMatrix::multiply ( v1, v2 ); }
PRMatrix operator* ( float v1, const PRMatrix & v2 ) { return PRMatrix::multiply ( v1, v2 ); }
PRMatrix operator/ ( const PRMatrix & v1, const PRMatrix & v2 ) { return PRMatrix::divide ( v1, v2 ); }
PRMatrix operator/ ( const PRMatrix & v1, float v2 ) { return PRMatrix::divide ( v1, v2 ); }
bool operator== ( const PRMatrix & v1, const PRMatrix & v2 ) {
	return PRIsEquals ( v1._11, v2._11 ) && PRIsEquals ( v1._12, v2._12 ) && PRIsEquals ( v1._13, v2._13 ) && PRIsEquals ( v1._14, v2._14 ) &&
		PRIsEquals ( v1._21, v2._21 ) && PRIsEquals ( v1._22, v2._22 ) && PRIsEquals ( v1._23, v2._23 ) && PRIsEquals ( v1._24, v2._24 ) &&
		PRIsEquals ( v1._31, v2._31 ) && PRIsEquals ( v1._32, v2._32 ) && PRIsEquals ( v1._33, v2._33 ) && PRIsEquals ( v1._34, v2._34 ) &&
		PRIsEquals ( v1._41, v2._41 ) && PRIsEquals ( v1._42, v2._42 ) && PRIsEquals ( v1._43, v2._43 ) && PRIsEquals ( v1._44, v2._44 );
}

#if PRPlatformUNIX
#	include <SOIL/SOIL.h>
#elif PRPlatformGoogleAndroid
#	include "stb_image/stb_image_aug.h"
#endif

FILE* PR_openFile ( std::string & filename, const char * openmode ) {
#if PRPlatformAppleFamily
	CFBundleRef mainBundle = CFBundleGetMainBundle ();
	CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL ( mainBundle );
	char path [ 1024 ];
	if ( !CFURLGetFileSystemRepresentation ( resourceURL, true, ( UInt8 * ) path, 1024 ) )
		throw std::runtime_error ( "Cannot get resource directory path." );
	CFRelease ( resourceURL );

	chdir ( path );
#endif

#if PRPlatformMicrosoftWindowsRT
	USES_CONVERSION;
#endif

	char fullpath [ 2048 ] = { 0, };
#if PRPlatformMicrosoftWindowsRT
	strcat_s ( fullpath, 2048, W2A ( Windows::ApplicationModel::Package::Current->InstalledLocation->Path->Data () ) );
	strcat_s ( fullpath, 2048, "\\" );
#endif
#if defined ( __STDC_WANT_SECURE_LIB__ ) && ( __STDC_WANT_SECURE_LIB__ == 1 )
	strcat_s ( fullpath, 2048, filename.c_str () );
#else
	strcat ( fullpath, filename.c_str () );
#endif

#if defined ( __STDC_WANT_SECURE_LIB__ ) && ( __STDC_WANT_SECURE_LIB__ == 1 )
	FILE * fp;
	fopen_s ( &fp, fullpath, openmode );
#else
	FILE * fp = fopen ( fullpath, openmode );
#endif
	if ( fp == nullptr )
		throw std::runtime_error ( "File Not Found." );
	return fp;
}

PRImageLoader::PRImageLoader ( std::string & filename ) {
#if PRPlatformAppleFamily
	CFBundleRef mainBundle = CFBundleGetMainBundle ();
	CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL ( mainBundle );
	char path [ 1024 ];
	if ( !CFURLGetFileSystemRepresentation ( resourceURL, true, ( UInt8 * ) path, 1024 ) )
		throw std::runtime_error ( "Cannot get resource directory path." );
	CFRelease ( resourceURL );

	chdir ( path );
#endif

#if PRPlatformUNIX
	m_data = SOIL_load_image ( filename.c_str (), ( int* ) &m_width, ( int* ) &m_height, nullptr, 4 );
	if ( m_data == nullptr )
		throw std::runtime_error ( "Error from SOIL_load_image ()." );
#elif !PRPlatformMicrosoftWindowsFamily
	m_data = stbi_load ( filename.c_str (), ( int* ) &m_width, ( int* ) &m_height, 0, 4 );
	if ( m_data == nullptr )
		throw std::runtime_error ( stbi_failure_reason () );
#else
	USES_CONVERSION;

	IWICImagingFactory * factory;
	IWICBitmapDecoder * decoder;
	IWICBitmapFrameDecode * frameDecode;
	IWICFormatConverter * formatConverter;

	char fullpath [ 2048 ] = { 0, };
#if PRPlatformMicrosoftWindowsRT
	strcat_s ( fullpath, 2048, W2A ( Windows::ApplicationModel::Package::Current->InstalledLocation->Path->Data () ) );
	strcat_s ( fullpath, 2048, "\\Assets\\" );
#endif
	strcat_s ( fullpath, 2048, filename.c_str () );

	if ( FAILED ( CoCreateInstance ( CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, ( void** ) &factory ) ) )
		throw std::runtime_error ( "Cannot create IWICImagingFactory." );

	if ( FAILED ( factory->CreateDecoderFromFilename ( A2W ( fullpath ), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder ) ) )
		throw std::runtime_error ( "Cannot load image file." );

	decoder->GetFrame ( 0, &frameDecode );
	frameDecode->GetSize ( &m_width, &m_height );

	factory->CreateFormatConverter ( &formatConverter );
	if ( FAILED ( formatConverter->Initialize ( frameDecode, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeCustom ) ) )
		throw std::runtime_error ( "Cannot create format converter." );

	m_data = new int [ m_width * m_height ];
	formatConverter->CopyPixels ( nullptr, sizeof ( int ) * m_width, sizeof ( int ) * m_width * m_height, ( BYTE* ) m_data );

	formatConverter->Release ();
	frameDecode->Release ();
	decoder->Release ();
	factory->Release ();
#endif
}

PRImageLoader::~PRImageLoader () { if ( m_data ) free ( ( unsigned char * ) m_data ); }

unsigned PRImageLoader::getWidth () { return m_width; }
unsigned PRImageLoader::getHeight () { return m_height; }
const void * PRImageLoader::getData () { return m_data; }

PRDataLoader::PRDataLoader ( std::string & filename ) {
	FILE * fp = PR_openFile ( filename, "rb" );

	fseek ( fp, 0, SEEK_END );
	m_dataSize = ( unsigned ) ftell ( fp );
	fseek ( fp, 0, SEEK_SET );

	m_data = new char [ m_dataSize ];
	fread ( m_data, m_dataSize, 1, fp );

	fclose ( fp );
}

PRDataLoader::~PRDataLoader () { SAFE_DELETE_ARRAY ( m_data ); }

const void * PRDataLoader::getData () { return m_data; }
unsigned PRDataLoader::getDataSize () { return m_dataSize; }

struct vertex { PRVector3 position; PRVector2 texCoord; PRVector4 diffuse; };
struct polygonTriangle { vertex v1, v2, v3; };
struct polygonLine { vertex v1, v2; };

void generateTriangleModel ( void * data, unsigned dataSize, PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale,
	void** result, unsigned * length );
void generateCube ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale, void** result, unsigned * length );
void generateRect ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale, void** result, unsigned * length );
void generateSphere ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale, void** result, unsigned * length );
void generateCircle ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale, void** result, unsigned * length );
void generateGrid ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale, void** result, unsigned * length );
void generateGuide ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale, void** result, unsigned * length );

PRModelGenerator::PRModelGenerator ( PRModelType modelType, PRModelProperty properties,
	PRModelTexCoord tcs, const PRVector3 * scale ) {
	switch ( modelType ) {
	case PRModelType_Box:		generateCube ( properties, tcs, scale, &m_data, &m_dataSize ); break;
	case PRModelType_Rectangle:	generateRect ( properties, tcs, scale, &m_data, &m_dataSize ); break;
	case PRModelType_Sphere:		generateSphere ( properties, tcs, scale, &m_data, &m_dataSize ); break;
	case PRModelType_Circle:		generateCircle ( properties, tcs, scale, &m_data, &m_dataSize ); break;
	case PRModelType_Grid:		generateGrid ( properties, tcs, scale, &m_data, &m_dataSize ); break;
	case PRModelType_Guide:		generateGuide ( properties, tcs, scale, &m_data, &m_dataSize ); break;
	}
	m_properties = properties;
}

PRModelGenerator::PRModelGenerator ( std::string & filename, PRModelTexCoord tcs, const PRVector3 * scale ) {
	if ( filename.substr ( filename.size () - 3, 3 ).compare ( "obj" ) != 0 )
		throw std::runtime_error ( "This object can read Wavefront's OBJ file only." );

	FILE * fp = PR_openFile ( filename, "rt" );

	// Original Source from "http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading"
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<PRVector3> temp_vertices;
	std::vector<PRVector2> temp_uvs;
	std::vector<PRVector3> temp_normals;

	PRModelProperty prop = PRModelProperty_Position;

	while ( 1 ) {
		char lineHeader [ 128 ];
		int res = fscanf ( fp, "%s", lineHeader );
		if ( res == EOF )
			break;

		if ( strcmp ( lineHeader, "v" ) == 0 ) {
			PRVector3 vertex;
			fscanf ( fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back ( vertex );
			prop |= PRModelProperty_Position;
		} else if ( strcmp ( lineHeader, "vt" ) == 0 ) {
			PRVector2 uv;
			fscanf ( fp, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back ( uv );
			prop |= PRModelProperty_TexCoord;
		} else if ( strcmp ( lineHeader, "vn" ) == 0 ) {
			PRVector3 normal;
			fscanf ( fp, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back ( normal );
			prop |= PRModelProperty_Normal;
		} else if ( strcmp ( lineHeader, "f" ) == 0 ) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex [ 3 ] = { 0, }, uvIndex [ 3 ] = { 0, }, normalIndex [ 3 ] = { 0, };
			if ( prop == ( PRModelProperty_Position | PRModelProperty_Normal | PRModelProperty_TexCoord ) ) {
				int matches = fscanf ( fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex [ 0 ], &uvIndex [ 0 ], &normalIndex [ 0 ],
					&vertexIndex [ 1 ], &uvIndex [ 1 ], &normalIndex [ 1 ], &vertexIndex [ 2 ], &uvIndex [ 2 ], &normalIndex [ 2 ] );
				if ( matches != 9 )
					throw std::runtime_error ( "File format is invalid." );
			} else if ( prop == ( PRModelProperty_Position | PRModelProperty_Normal ) ) {
				int matches = fscanf ( fp, "%d//%d %d//%d %d//%d\n", &vertexIndex [ 0 ], &normalIndex [ 0 ],
					&vertexIndex [ 1 ], &normalIndex [ 1 ], &vertexIndex [ 2 ], &normalIndex [ 2 ] );
				if ( matches != 6 )
					throw std::runtime_error ( "File format is invalid." );
			} else if ( prop == ( PRModelProperty_Position | PRModelProperty_TexCoord ) ) {
				int matches = fscanf ( fp, "%d/%d %d/%d %d/%d\n", &vertexIndex [ 0 ], &uvIndex [ 0 ],
					&vertexIndex [ 1 ], &uvIndex [ 1 ], &vertexIndex [ 2 ], &uvIndex [ 2 ] );
				if ( matches != 6 )
					throw std::runtime_error ( "File format is invalid." );
			} else if ( prop == PRModelProperty_Position ) {
				int matches = fscanf ( fp, "%d %d %d\n", &vertexIndex [ 0 ], &vertexIndex [ 1 ], &vertexIndex [ 2 ] );
				if ( matches != 3 )
					throw std::runtime_error ( "File format is invalid." );
			}

			vertexIndices.push_back ( vertexIndex [ 0 ] );
			vertexIndices.push_back ( vertexIndex [ 1 ] );
			vertexIndices.push_back ( vertexIndex [ 2 ] );

			if ( prop & PRModelProperty_TexCoord ) {
				uvIndices.push_back ( uvIndex [ 0 ] );
				uvIndices.push_back ( uvIndex [ 1 ] );
				uvIndices.push_back ( uvIndex [ 2 ] );
			}
			if ( prop & PRModelProperty_Normal ) {
				normalIndices.push_back ( normalIndex [ 0 ] );
				normalIndices.push_back ( normalIndex [ 1 ] );
				normalIndices.push_back ( normalIndex [ 2 ] );
			}
		} else {
			char stupidBuffer [ 1000 ];
			fgets ( stupidBuffer, 1000, fp );
		}
	}

	std::vector<float> vv;
	for ( unsigned int i = 0; i < vertexIndices.size (); i++ ) {
		unsigned int vertexIndex = vertexIndices [ i ];
		unsigned int uvIndex = uvIndices.size () > 0 ? uvIndices [ i ] : 0;
		unsigned int normalIndex = normalIndices.size () > 0 ? normalIndices [ i ] : 0;

		PRVector3 vertex = temp_vertices [ vertexIndex - 1 ];
		vv.push_back ( vertex.x ); vv.push_back ( vertex.y ); vv.push_back ( vertex.z );
		if ( prop & PRModelProperty_Normal ) {
			PRVector3 normal = temp_normals [ normalIndex - 1 ];
			vv.push_back ( normal.x ); vv.push_back ( normal.y ); vv.push_back ( normal.z );
		}
		if ( prop & PRModelProperty_TexCoord ) {
			PRVector2 uv = temp_uvs [ uvIndex - 1 ];
			vv.push_back ( uv.x ); vv.push_back ( uv.y );
		}
		vv.push_back ( 1 ); vv.push_back ( 1 ); vv.push_back ( 1 ); vv.push_back ( 1 );
	}

	m_data = new float [ vv.size () ];
	m_dataSize = vv.size () * sizeof ( float );
	memcpy ( m_data, &vv [ 0 ], m_dataSize );
	m_properties = prop | PRModelProperty_Diffuse;
}

PRModelProperty PRModelGenerator::getProperties () { return m_properties; }
const void* PRModelGenerator::getData () { return m_data; }
unsigned PRModelGenerator::getDataSize () { return m_dataSize; }

PRModelGenerator::~PRModelGenerator () { SAFE_DELETE_ARRAY ( m_data ); }

void generateTriangleModel ( void * data, unsigned dataSize, PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale,
	void** result, unsigned * length ) {
	polygonTriangle *vertices = ( polygonTriangle* ) data;

	std::vector<float> vv;
	for ( unsigned i = 0; i < dataSize / sizeof ( polygonTriangle ); ++i ) {
		PRVector3 norm = PRCalculateNormal ( vertices->v1.position, vertices->v2.position, vertices->v3.position );

		PRVector3 p1 = vertices->v1.position;
		if ( scale != nullptr ) p1 = p1 * *scale;
		vv.push_back ( p1.x ); vv.push_back ( p1.y ); vv.push_back ( p1.z );

		if ( properties & PRModelProperty_Normal ) {
			vv.push_back ( norm.x ); vv.push_back ( norm.y ); vv.push_back ( norm.z );
		}

		if ( properties & PRModelProperty_TexCoord ) {
			vv.push_back ( vertices->v1.texCoord.x );
			vv.push_back ( tcs == PRModelTexCoord_ST ? 1 - vertices->v1.texCoord.y : vertices->v1.texCoord.y );
		}

		if ( properties & PRModelProperty_Diffuse ) {
			vv.push_back ( vertices->v1.diffuse.x );
			vv.push_back ( vertices->v1.diffuse.y );
			vv.push_back ( vertices->v1.diffuse.z );
			vv.push_back ( vertices->v1.diffuse.w );
		}

		PRVector3 p2 = vertices->v2.position;
		if ( scale != nullptr ) p2 = p2 * *scale;
		vv.push_back ( p2.x ); vv.push_back ( p2.y ); vv.push_back ( p2.z );

		if ( properties & PRModelProperty_Normal ) {
			vv.push_back ( norm.x ); vv.push_back ( norm.y ); vv.push_back ( norm.z );
		}

		if ( properties & PRModelProperty_TexCoord ) {
			vv.push_back ( vertices->v2.texCoord.x );
			vv.push_back ( tcs == PRModelTexCoord_ST ? 1 - vertices->v2.texCoord.y : vertices->v2.texCoord.y );
		}

		if ( properties & PRModelProperty_Diffuse ) {
			vv.push_back ( vertices->v2.diffuse.x );
			vv.push_back ( vertices->v2.diffuse.y );
			vv.push_back ( vertices->v2.diffuse.z );
			vv.push_back ( vertices->v2.diffuse.w );
		}

		PRVector3 p3 = vertices->v3.position;
		if ( scale != nullptr ) p3 = p3 * *scale;
		vv.push_back ( p3.x ); vv.push_back ( p3.y ); vv.push_back ( p3.z );

		if ( properties & PRModelProperty_Normal ) {
			vv.push_back ( norm.x ); vv.push_back ( norm.y ); vv.push_back ( norm.z );
		}

		if ( properties & PRModelProperty_TexCoord ) {
			vv.push_back ( vertices->v3.texCoord.x );
			vv.push_back ( tcs == PRModelTexCoord_ST ? 1 - vertices->v3.texCoord.y : vertices->v3.texCoord.y );
		}

		if ( properties & PRModelProperty_Diffuse ) {
			vv.push_back ( vertices->v3.diffuse.x );
			vv.push_back ( vertices->v3.diffuse.y );
			vv.push_back ( vertices->v3.diffuse.z );
			vv.push_back ( vertices->v3.diffuse.w );
		}

		++vertices;
	}

	*result = new float [ vv.size () ];
	*length = ( unsigned ) vv.size () * sizeof ( float );
#if defined ( __STDC_WANT_SECURE_LIB__ ) && ( __STDC_WANT_SECURE_LIB__ == 1 )
	memcpy_s ( *result, *length, &vv [ 0 ], *length );
#else
	memcpy ( *result, &vv [ 0 ], *length );
#endif
}

void generateLineModel ( void * data, unsigned dataSize, PRModelProperty properties, PRModelTexCoord tcs,
	const PRVector3 * scale, void** result, unsigned * length ) {
	polygonLine *vertices = ( polygonLine* ) data;

	std::vector<float> vv;
	for ( unsigned i = 0; i < dataSize / sizeof ( polygonLine ); ++i ) {
		PRVector3 norm = vertices->v2.position - vertices->v1.position;

		PRVector3 p1 = vertices->v1.position;
		if ( scale != nullptr ) p1 = p1 * *scale;
		vv.push_back ( p1.x ); vv.push_back ( p1.y ); vv.push_back ( p1.z );

		if ( properties & PRModelProperty_Normal ) {
			vv.push_back ( norm.x ); vv.push_back ( norm.y ); vv.push_back ( norm.z );
		}

		if ( properties & PRModelProperty_TexCoord ) {
			vv.push_back ( vertices->v1.texCoord.x );
			vv.push_back ( tcs == PRModelTexCoord_ST ? 1 - vertices->v1.texCoord.y : vertices->v1.texCoord.y );
		}

		if ( properties & PRModelProperty_Diffuse ) {
			vv.push_back ( vertices->v1.diffuse.x );
			vv.push_back ( vertices->v1.diffuse.y );
			vv.push_back ( vertices->v1.diffuse.z );
			vv.push_back ( vertices->v1.diffuse.w );
		}

		PRVector3 p2 = vertices->v2.position;
		if ( scale != nullptr ) p2 = p2 * *scale;
		vv.push_back ( p2.x ); vv.push_back ( p2.y ); vv.push_back ( p2.z );

		if ( properties & PRModelProperty_Normal ) {
			vv.push_back ( norm.x ); vv.push_back ( norm.y ); vv.push_back ( norm.z );
		}

		if ( properties & PRModelProperty_TexCoord ) {
			vv.push_back ( vertices->v2.texCoord.x );
			vv.push_back ( tcs == PRModelTexCoord_ST ? 1 - vertices->v2.texCoord.y : vertices->v2.texCoord.y );
		}

		if ( properties & PRModelProperty_Diffuse ) {
			vv.push_back ( vertices->v2.diffuse.x );
			vv.push_back ( vertices->v2.diffuse.y );
			vv.push_back ( vertices->v2.diffuse.z );
			vv.push_back ( vertices->v2.diffuse.w );
		}

		++vertices;
	}

	*result = new float [ vv.size () ];
	*length = ( unsigned ) vv.size () * sizeof ( float );
#if defined ( __STDC_WANT_SECURE_LIB__ ) && ( __STDC_WANT_SECURE_LIB__ == 1 )
	memcpy_s ( *result, *length, &vv [ 0 ], *length );
#else
	memcpy ( *result, &vv [ 0 ], *length );
#endif
}

void generateCube ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale,
	void** result, unsigned * length ) {
	vertex cube [] = {
		{ { -0.5f, -0.5f, -0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, -0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, -0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },

		{ { -0.5f, -0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, +0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, +0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, +0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },

		{ { -0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },

		{ { +0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },

		{ { -0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },

		{ { -0.5f, +0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } }
	};
	generateTriangleModel ( cube, sizeof ( cube ), properties, tcs, scale, result, length );
}

void generateRect ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale,
	void** result, unsigned * length )
{
	vertex rect [] = {
		{ { -0.5f, -0.5f, 0 }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, 0 }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, 0 }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, 0 }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, 0 }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, 0 }, { 0, 0 }, { 1, 1, 1, 1 } },
	};
	generateTriangleModel ( rect, sizeof ( rect ), properties, tcs, scale, result, length );
}

void generateSphere ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale,
	void** result, unsigned * length ) {
	// Source from "http://stackoverflow.com/questions/5988686/creating-a-3d-sphere-in-opengl-using-visual-c"

	const unsigned rings = scale == nullptr ? 20 : ( unsigned ) scale->x * 10;
	const unsigned sectors = scale == nullptr ? 20 : ( unsigned ) scale->y * 10;

	float const R = 1.0f / ( float ) ( rings - 1 );
	float const S = 1.0f / ( float ) ( sectors - 1 );
	unsigned r, s;

	std::vector<PRVector3> vertices;
	std::vector<PRVector2> texcoords;
	std::vector<unsigned> indices;

	for ( r = 0; r < rings; r++ ) {
		for ( s = 0; s < sectors; s++ ) {
			float const y = sin ( -PR_PIover2 + PR_PI * r * R );
			float const x = cos ( 2 * PR_PI * s * S ) * sin ( PR_PI * r * R );
			float const z = sin ( 2 * PR_PI * s * S ) * sin ( PR_PI * r * R );
			vertices.push_back ( PRVector3 ( x, y, z ) * 0.5f );
			texcoords.push_back ( PRVector2 ( s * S, r * R ) );
		}
	}

	for ( r = 0; r < rings - 1; r++ ) {
		for ( s = 0; s < sectors - 1; s++ ) {
			int curRow = r * sectors;
			int nextRow = ( r + 1 ) * sectors;

			indices.push_back ( curRow + s );
			indices.push_back ( nextRow + s );
			indices.push_back ( nextRow + ( s + 1 ) );

			indices.push_back ( curRow + s );
			indices.push_back ( nextRow + ( s + 1 ) );
			indices.push_back ( curRow + ( s + 1 ) );
		}
	}

	std::vector<vertex> sphere;
	sphere.resize ( indices.size () );
	int j = 0;
	for ( auto i = indices.begin (); i != indices.end (); ++i ) {
		vertex vtx;
		vtx.position = vertices [ *i ];
		vtx.texCoord = texcoords [ *i ];
		vtx.diffuse = PRVector4 ( 1, 1, 1, 1 );
		sphere [ j++ ] = vtx;
	}

	float * temp = new float [ sphere.size () * sizeof ( vertex ) ];
	unsigned templen = ( unsigned ) ( sizeof ( vertex ) * sphere.size () );
#if defined ( __STDC_WANT_SECURE_LIB__ ) && ( __STDC_WANT_SECURE_LIB__ == 1 )
	memcpy_s ( temp, templen, &sphere [ 0 ], templen );
#else
	memcpy ( temp, &sphere [ 0 ], templen );
#endif

	generateTriangleModel ( temp, templen, properties, tcs, scale, result, length );

	delete [] temp;
}

void generateCircle ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale,
	void** result, unsigned * length ) {
	unsigned sectors = scale == nullptr ? 20 : ( unsigned ) PRMax ( scale->x, scale->y ) * 10;

	std::vector<vertex> vertices;
	for ( float r = 0; r <= PR_2PI; r += ( PR_2PI / sectors ) ) {
		vertex vtx;

		vtx.position = PRVector3 ( 0, 0, 0 );
		vtx.texCoord = PRVector2 ( 0.5f, 0.5f );
		vtx.diffuse = PRVector4 ( 1, 1, 1, 1 );
		vertices.push_back ( vtx );

		vtx.position = PRVector3 ( cos ( r ), sin ( r ), 0 ) * 0.5f;
		vtx.texCoord = PRVector2 ( vtx.position.x + 0.5f, vtx.position.y + 0.5f );
		vtx.diffuse = PRVector4 ( 1, 1, 1, 1 );
		vertices.push_back ( vtx );

		vtx.position = PRVector3 ( cos ( r + ( PR_2PI / sectors ) ), sin ( r + ( PR_2PI / sectors ) ), 0 ) * 0.5f;
		vtx.texCoord = PRVector2 ( vtx.position.x + 0.5f, vtx.position.y + 0.5f );
		vtx.diffuse = PRVector4 ( 1, 1, 1, 1 );
		vertices.push_back ( vtx );
	}

	float * temp = new float [ vertices.size () * sizeof ( vertex ) ];
	unsigned templen = ( unsigned ) ( sizeof ( vertex ) * vertices.size () );
#if defined ( __STDC_WANT_SECURE_LIB__ ) && ( __STDC_WANT_SECURE_LIB__ == 1 )
	memcpy_s ( temp, templen, &vertices [ 0 ], templen );
#else
	memcpy ( temp, &vertices [ 0 ], templen );
#endif

	generateTriangleModel ( temp, templen, properties, tcs, scale, result, length );

	delete [] temp;
}

void generateGrid ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale,
	void** result, unsigned * length ) {
	polygonLine vertices [ 202 ];
	unsigned index = 0;
	for ( unsigned z = 0; z <= 100; ++z ) {
		vertices [ index ].v1.position = PRVector3 ( -50, 0, ( float ) z - 50 );
		vertices [ index ].v1.texCoord = PRVector2 ( 0, 0 );
		vertices [ index ].v1.diffuse = PRVector4 ( 1, 1, 1, 1 );
		vertices [ index ].v2.position = PRVector3 ( 50, 0, ( float ) z - 50 );
		vertices [ index ].v2.texCoord = PRVector2 ( 1, 0 );
		vertices [ index ].v2.diffuse = PRVector4 ( 1, 1, 1, 1 );
		++index;
	}
	for ( unsigned x = 0; x <= 100; ++x ) {
		vertices [ index ].v1.position = PRVector3 ( ( float ) x - 50, 0, -50 );
		vertices [ index ].v1.texCoord = PRVector2 ( 0, 0 );
		vertices [ index ].v1.diffuse = PRVector4 ( 1, 1, 1, 1 );
		vertices [ index ].v2.position = PRVector3 ( ( float ) x - 50, 0, 50 );
		vertices [ index ].v2.texCoord = PRVector2 ( 0, 1 );
		vertices [ index ].v2.diffuse = PRVector4 ( 1, 1, 1, 1 );
		++index;
	}
	generateLineModel ( vertices, sizeof ( vertices ), properties, tcs, scale, result, length );
}

void generateGuide ( PRModelProperty properties, PRModelTexCoord tcs, const PRVector3 * scale,
	void** result, unsigned * length ) {
	polygonLine vertices [ 3 ] = {
		{ { { 0, 0, 0 }, { 0, 0 }, { 1, 0, 0, 1 } }, { { 1, 0, 0 }, { 1, 0 }, { 1, 0, 0, 1 } } },
		{ { { 0, 0, 0 }, { 0, 0 }, { 0, 1, 0, 1 } }, { { 0, 1, 0 }, { 1, 0 }, { 0, 1, 0, 1 } } },
		{ { { 0, 0, 0 }, { 0, 0 }, { 0, 0, 1, 1 } }, { { 0, 0, 1 }, { 0, 1 }, { 0, 0, 1, 1 } } },
	};
	generateLineModel ( vertices, sizeof ( vertices ), properties, tcs, scale, result, length );
}

PRVector3 PRCalculateNormal ( const PRVector3 & v1, const PRVector3 & v2, const PRVector3 & v3 ) {
	PRVector3 temp1 = v2 - v1, temp2 = v3 - v1;
	return PRVector3::cross ( temp1, temp2 ).normalize ();
}

#if PRPlatformMicrosoftWindowsNT || PRPlatformMicrosoftWindowsRT
LARGE_INTEGER performanceFrequency;
bool isPerformanceFrequencySupport = false;
#endif

double PRGetCurrentSecond () {
#if PRPlatformMicrosoftWindowsNT || PRPlatformMicrosoftWindowsRT
	isPerformanceFrequencySupport = QueryPerformanceFrequency ( &performanceFrequency ) ? true : false;
	if ( isPerformanceFrequencySupport ) {
		LARGE_INTEGER getTime;
		QueryPerformanceCounter ( &getTime );
		return ( getTime.QuadPart / ( double ) performanceFrequency.QuadPart );
	}
	else
#if !PRPlatformMicrosoftWindowsRT
		return timeGetTime () / 1000.0;
#else
		return 0;
#endif
#elif PRPlatformAppleFamily || PRPlatformUNIXFamily
	timeval tv;
	gettimeofday ( &tv, nullptr );
	return ( tv.tv_sec * 1000 + tv.tv_usec / 1000 ) / 1000.0;
#endif
}

void PRPrintLog ( const char * format, ... ) {
	va_list vl;
	va_start ( vl, format );
	char text [ 1024 ];
#if defined ( __STDC_WANT_SECURE_LIB__ ) && ( __STDC_WANT_SECURE_LIB__ == 1 )
	vsprintf_s ( text, 1023, format, vl );
#else
	vsprintf ( text, format, vl );
#endif
	va_end ( vl );
#if defined ( __STDC_WANT_SECURE_LIB__ ) && ( __STDC_WANT_SECURE_LIB__ == 1 )
	size_t len = strlen ( text );
	text [ len ] = '\n';
	text [ len + 1 ] = '\0';
	OutputDebugStringA ( text );
#elif PRPlatformGoogleAndroid
	__android_log_print ( ANDROID_LOG_INFO, "libPolyram", text );
#else
	size_t len = strlen ( text );
	text [ len ] = '\n';
	text [ len + 1 ] = '\0';
	fprintf ( stderr, text );
#endif
}