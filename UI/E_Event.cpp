/*
	This file is part of the E_Util library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Event.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Util/UI/Event.h>

namespace E_Util {
namespace E_UI {

void E_Event::init(EScript::Namespace & lib) {
	EScript::declareConstant(&lib, "EVENT_QUIT", static_cast<uint32_t>(Util::UI::EVENT_QUIT));
	EScript::declareConstant(&lib, "EVENT_RESIZE", static_cast<uint32_t>(Util::UI::EVENT_RESIZE));
	EScript::declareConstant(&lib, "EVENT_KEYBOARD", static_cast<uint32_t>(Util::UI::EVENT_KEYBOARD));
	EScript::declareConstant(&lib, "EVENT_MOUSE_BUTTON", static_cast<uint32_t>(Util::UI::EVENT_MOUSE_BUTTON));
	EScript::declareConstant(&lib, "EVENT_MOUSE_MOTION", static_cast<uint32_t>(Util::UI::EVENT_MOUSE_MOTION));
	EScript::declareConstant(&lib, "EVENT_JOY_AXIS", static_cast<uint32_t>(Util::UI::EVENT_JOY_AXIS));
	EScript::declareConstant(&lib, "EVENT_JOY_BUTTON", static_cast<uint32_t>(Util::UI::EVENT_JOY_BUTTON));
	EScript::declareConstant(&lib, "EVENT_JOY_HAT", static_cast<uint32_t>(Util::UI::EVENT_JOY_HAT));

	EScript::declareConstant(&lib, "KEY_NONE", static_cast<uint32_t>(Util::UI::KEY_NONE));
	EScript::declareConstant(&lib, "KEY_BACKSPACE", static_cast<uint32_t>(Util::UI::KEY_BACKSPACE));
	EScript::declareConstant(&lib, "KEY_TAB", static_cast<uint32_t>(Util::UI::KEY_TAB));
	EScript::declareConstant(&lib, "KEY_LINEFEED", static_cast<uint32_t>(Util::UI::KEY_LINEFEED));
	EScript::declareConstant(&lib, "KEY_CLEAR", static_cast<uint32_t>(Util::UI::KEY_CLEAR));
	EScript::declareConstant(&lib, "KEY_RETURN", static_cast<uint32_t>(Util::UI::KEY_RETURN));
	EScript::declareConstant(&lib, "KEY_PAUSE", static_cast<uint32_t>(Util::UI::KEY_PAUSE));
	EScript::declareConstant(&lib, "KEY_SCROLLLOCK", static_cast<uint32_t>(Util::UI::KEY_SCROLLLOCK));
	EScript::declareConstant(&lib, "KEY_SYSREQ", static_cast<uint32_t>(Util::UI::KEY_SYSREQ));
	EScript::declareConstant(&lib, "KEY_ESCAPE", static_cast<uint32_t>(Util::UI::KEY_ESCAPE));
	EScript::declareConstant(&lib, "KEY_DELETE", static_cast<uint32_t>(Util::UI::KEY_DELETE));
	EScript::declareConstant(&lib, "KEY_MULTIKEY", static_cast<uint32_t>(Util::UI::KEY_MULTIKEY));
	EScript::declareConstant(&lib, "KEY_HOME", static_cast<uint32_t>(Util::UI::KEY_HOME));
	EScript::declareConstant(&lib, "KEY_LEFT", static_cast<uint32_t>(Util::UI::KEY_LEFT));
	EScript::declareConstant(&lib, "KEY_UP", static_cast<uint32_t>(Util::UI::KEY_UP));
	EScript::declareConstant(&lib, "KEY_RIGHT", static_cast<uint32_t>(Util::UI::KEY_RIGHT));
	EScript::declareConstant(&lib, "KEY_DOWN", static_cast<uint32_t>(Util::UI::KEY_DOWN));
	EScript::declareConstant(&lib, "KEY_PAGEUP", static_cast<uint32_t>(Util::UI::KEY_PAGEUP));
	EScript::declareConstant(&lib, "KEY_PAGEDOWN", static_cast<uint32_t>(Util::UI::KEY_PAGEDOWN));
	EScript::declareConstant(&lib, "KEY_END", static_cast<uint32_t>(Util::UI::KEY_END));
	EScript::declareConstant(&lib, "KEY_PRINT", static_cast<uint32_t>(Util::UI::KEY_PRINT));
	EScript::declareConstant(&lib, "KEY_INSERT", static_cast<uint32_t>(Util::UI::KEY_INSERT));
	EScript::declareConstant(&lib, "KEY_UNDO", static_cast<uint32_t>(Util::UI::KEY_UNDO));
	EScript::declareConstant(&lib, "KEY_REDO", static_cast<uint32_t>(Util::UI::KEY_REDO));
	EScript::declareConstant(&lib, "KEY_MENU", static_cast<uint32_t>(Util::UI::KEY_MENU));
	EScript::declareConstant(&lib, "KEY_HELP", static_cast<uint32_t>(Util::UI::KEY_HELP));
	EScript::declareConstant(&lib, "KEY_BREAK", static_cast<uint32_t>(Util::UI::KEY_BREAK));
	EScript::declareConstant(&lib, "KEY_MODESWITCH", static_cast<uint32_t>(Util::UI::KEY_MODESWITCH));
	EScript::declareConstant(&lib, "KEY_NUMLOCK", static_cast<uint32_t>(Util::UI::KEY_NUMLOCK));
	EScript::declareConstant(&lib, "KEY_KPENTER", static_cast<uint32_t>(Util::UI::KEY_KPENTER));
	EScript::declareConstant(&lib, "KEY_KPEQUAL", static_cast<uint32_t>(Util::UI::KEY_KPEQUAL));
	EScript::declareConstant(&lib, "KEY_KPMULTIPLY", static_cast<uint32_t>(Util::UI::KEY_KPMULTIPLY));
	EScript::declareConstant(&lib, "KEY_KPADD", static_cast<uint32_t>(Util::UI::KEY_KPADD));
	EScript::declareConstant(&lib, "KEY_KPSEPARATOR", static_cast<uint32_t>(Util::UI::KEY_KPSEPARATOR));
	EScript::declareConstant(&lib, "KEY_KPSUBTRACT", static_cast<uint32_t>(Util::UI::KEY_KPSUBTRACT));
	EScript::declareConstant(&lib, "KEY_KPDIVIDE", static_cast<uint32_t>(Util::UI::KEY_KPDIVIDE));
	EScript::declareConstant(&lib, "KEY_KP0", static_cast<uint32_t>(Util::UI::KEY_KP0));
	EScript::declareConstant(&lib, "KEY_KP1", static_cast<uint32_t>(Util::UI::KEY_KP1));
	EScript::declareConstant(&lib, "KEY_KP2", static_cast<uint32_t>(Util::UI::KEY_KP2));
	EScript::declareConstant(&lib, "KEY_KP3", static_cast<uint32_t>(Util::UI::KEY_KP3));
	EScript::declareConstant(&lib, "KEY_KP4", static_cast<uint32_t>(Util::UI::KEY_KP4));
	EScript::declareConstant(&lib, "KEY_KP5", static_cast<uint32_t>(Util::UI::KEY_KP5));
	EScript::declareConstant(&lib, "KEY_KP6", static_cast<uint32_t>(Util::UI::KEY_KP6));
	EScript::declareConstant(&lib, "KEY_KP7", static_cast<uint32_t>(Util::UI::KEY_KP7));
	EScript::declareConstant(&lib, "KEY_KP8", static_cast<uint32_t>(Util::UI::KEY_KP8));
	EScript::declareConstant(&lib, "KEY_KP9", static_cast<uint32_t>(Util::UI::KEY_KP9));
	EScript::declareConstant(&lib, "KEY_F1", static_cast<uint32_t>(Util::UI::KEY_F1));
	EScript::declareConstant(&lib, "KEY_F2", static_cast<uint32_t>(Util::UI::KEY_F2));
	EScript::declareConstant(&lib, "KEY_F3", static_cast<uint32_t>(Util::UI::KEY_F3));
	EScript::declareConstant(&lib, "KEY_F4", static_cast<uint32_t>(Util::UI::KEY_F4));
	EScript::declareConstant(&lib, "KEY_F5", static_cast<uint32_t>(Util::UI::KEY_F5));
	EScript::declareConstant(&lib, "KEY_F6", static_cast<uint32_t>(Util::UI::KEY_F6));
	EScript::declareConstant(&lib, "KEY_F7", static_cast<uint32_t>(Util::UI::KEY_F7));
	EScript::declareConstant(&lib, "KEY_F8", static_cast<uint32_t>(Util::UI::KEY_F8));
	EScript::declareConstant(&lib, "KEY_F9", static_cast<uint32_t>(Util::UI::KEY_F9));
	EScript::declareConstant(&lib, "KEY_F10", static_cast<uint32_t>(Util::UI::KEY_F10));
	EScript::declareConstant(&lib, "KEY_F11", static_cast<uint32_t>(Util::UI::KEY_F11));
	EScript::declareConstant(&lib, "KEY_F12", static_cast<uint32_t>(Util::UI::KEY_F12));
	EScript::declareConstant(&lib, "KEY_F13", static_cast<uint32_t>(Util::UI::KEY_F13));
	EScript::declareConstant(&lib, "KEY_F14", static_cast<uint32_t>(Util::UI::KEY_F14));
	EScript::declareConstant(&lib, "KEY_F15", static_cast<uint32_t>(Util::UI::KEY_F15));
	EScript::declareConstant(&lib, "KEY_SHIFTL", static_cast<uint32_t>(Util::UI::KEY_SHIFTL));
	EScript::declareConstant(&lib, "KEY_SHIFTR", static_cast<uint32_t>(Util::UI::KEY_SHIFTR));
	EScript::declareConstant(&lib, "KEY_CONTROLL", static_cast<uint32_t>(Util::UI::KEY_CONTROLL));
	EScript::declareConstant(&lib, "KEY_CONTROLR", static_cast<uint32_t>(Util::UI::KEY_CONTROLR));
	EScript::declareConstant(&lib, "KEY_METAL", static_cast<uint32_t>(Util::UI::KEY_METAL));
	EScript::declareConstant(&lib, "KEY_METAR", static_cast<uint32_t>(Util::UI::KEY_METAR));
	EScript::declareConstant(&lib, "KEY_ALTL", static_cast<uint32_t>(Util::UI::KEY_ALTL));
	EScript::declareConstant(&lib, "KEY_ALTR", static_cast<uint32_t>(Util::UI::KEY_ALTR));
	EScript::declareConstant(&lib, "KEY_SUPERL", static_cast<uint32_t>(Util::UI::KEY_SUPERL));
	EScript::declareConstant(&lib, "KEY_SUPERR", static_cast<uint32_t>(Util::UI::KEY_SUPERR));
	EScript::declareConstant(&lib, "KEY_CAPSLOCK", static_cast<uint32_t>(Util::UI::KEY_CAPSLOCK));
	EScript::declareConstant(&lib, "KEY_SPACE", static_cast<uint32_t>(Util::UI::KEY_SPACE));
	EScript::declareConstant(&lib, "KEY_EXCLAMATION", static_cast<uint32_t>(Util::UI::KEY_EXCLAMATION));
	EScript::declareConstant(&lib, "KEY_QUOTATION", static_cast<uint32_t>(Util::UI::KEY_QUOTATION));
	EScript::declareConstant(&lib, "KEY_NUMBERSIGN", static_cast<uint32_t>(Util::UI::KEY_NUMBERSIGN));
	EScript::declareConstant(&lib, "KEY_DOLLAR", static_cast<uint32_t>(Util::UI::KEY_DOLLAR));
	EScript::declareConstant(&lib, "KEY_PERCENT", static_cast<uint32_t>(Util::UI::KEY_PERCENT));
	EScript::declareConstant(&lib, "KEY_AMPERSAND", static_cast<uint32_t>(Util::UI::KEY_AMPERSAND));
	EScript::declareConstant(&lib, "KEY_APOSTROPHE", static_cast<uint32_t>(Util::UI::KEY_APOSTROPHE));
	EScript::declareConstant(&lib, "KEY_PARENLEFT", static_cast<uint32_t>(Util::UI::KEY_PARENLEFT));
	EScript::declareConstant(&lib, "KEY_PARENRIGHT", static_cast<uint32_t>(Util::UI::KEY_PARENRIGHT));
	EScript::declareConstant(&lib, "KEY_ASTERISK", static_cast<uint32_t>(Util::UI::KEY_ASTERISK));
	EScript::declareConstant(&lib, "KEY_PLUS", static_cast<uint32_t>(Util::UI::KEY_PLUS));
	EScript::declareConstant(&lib, "KEY_COMMA", static_cast<uint32_t>(Util::UI::KEY_COMMA));
	EScript::declareConstant(&lib, "KEY_MINUS", static_cast<uint32_t>(Util::UI::KEY_MINUS));
	EScript::declareConstant(&lib, "KEY_PERIOD", static_cast<uint32_t>(Util::UI::KEY_PERIOD));
	EScript::declareConstant(&lib, "KEY_SLASH", static_cast<uint32_t>(Util::UI::KEY_SLASH));
	EScript::declareConstant(&lib, "KEY_0", static_cast<uint32_t>(Util::UI::KEY_0));
	EScript::declareConstant(&lib, "KEY_1", static_cast<uint32_t>(Util::UI::KEY_1));
	EScript::declareConstant(&lib, "KEY_2", static_cast<uint32_t>(Util::UI::KEY_2));
	EScript::declareConstant(&lib, "KEY_3", static_cast<uint32_t>(Util::UI::KEY_3));
	EScript::declareConstant(&lib, "KEY_4", static_cast<uint32_t>(Util::UI::KEY_4));
	EScript::declareConstant(&lib, "KEY_5", static_cast<uint32_t>(Util::UI::KEY_5));
	EScript::declareConstant(&lib, "KEY_6", static_cast<uint32_t>(Util::UI::KEY_6));
	EScript::declareConstant(&lib, "KEY_7", static_cast<uint32_t>(Util::UI::KEY_7));
	EScript::declareConstant(&lib, "KEY_8", static_cast<uint32_t>(Util::UI::KEY_8));
	EScript::declareConstant(&lib, "KEY_9", static_cast<uint32_t>(Util::UI::KEY_9));
	EScript::declareConstant(&lib, "KEY_COLON", static_cast<uint32_t>(Util::UI::KEY_COLON));
	EScript::declareConstant(&lib, "KEY_SEMICOLON", static_cast<uint32_t>(Util::UI::KEY_SEMICOLON));
	EScript::declareConstant(&lib, "KEY_LESS", static_cast<uint32_t>(Util::UI::KEY_LESS));
	EScript::declareConstant(&lib, "KEY_EQUAL", static_cast<uint32_t>(Util::UI::KEY_EQUAL));
	EScript::declareConstant(&lib, "KEY_GREATER", static_cast<uint32_t>(Util::UI::KEY_GREATER));
	EScript::declareConstant(&lib, "KEY_QUESTION", static_cast<uint32_t>(Util::UI::KEY_QUESTION));
	EScript::declareConstant(&lib, "KEY_AT", static_cast<uint32_t>(Util::UI::KEY_AT));
	EScript::declareConstant(&lib, "KEY_A", static_cast<uint32_t>(Util::UI::KEY_A));
	EScript::declareConstant(&lib, "KEY_B", static_cast<uint32_t>(Util::UI::KEY_B));
	EScript::declareConstant(&lib, "KEY_C", static_cast<uint32_t>(Util::UI::KEY_C));
	EScript::declareConstant(&lib, "KEY_D", static_cast<uint32_t>(Util::UI::KEY_D));
	EScript::declareConstant(&lib, "KEY_E", static_cast<uint32_t>(Util::UI::KEY_E));
	EScript::declareConstant(&lib, "KEY_F", static_cast<uint32_t>(Util::UI::KEY_F));
	EScript::declareConstant(&lib, "KEY_G", static_cast<uint32_t>(Util::UI::KEY_G));
	EScript::declareConstant(&lib, "KEY_H", static_cast<uint32_t>(Util::UI::KEY_H));
	EScript::declareConstant(&lib, "KEY_I", static_cast<uint32_t>(Util::UI::KEY_I));
	EScript::declareConstant(&lib, "KEY_J", static_cast<uint32_t>(Util::UI::KEY_J));
	EScript::declareConstant(&lib, "KEY_K", static_cast<uint32_t>(Util::UI::KEY_K));
	EScript::declareConstant(&lib, "KEY_L", static_cast<uint32_t>(Util::UI::KEY_L));
	EScript::declareConstant(&lib, "KEY_M", static_cast<uint32_t>(Util::UI::KEY_M));
	EScript::declareConstant(&lib, "KEY_N", static_cast<uint32_t>(Util::UI::KEY_N));
	EScript::declareConstant(&lib, "KEY_O", static_cast<uint32_t>(Util::UI::KEY_O));
	EScript::declareConstant(&lib, "KEY_P", static_cast<uint32_t>(Util::UI::KEY_P));
	EScript::declareConstant(&lib, "KEY_Q", static_cast<uint32_t>(Util::UI::KEY_Q));
	EScript::declareConstant(&lib, "KEY_R", static_cast<uint32_t>(Util::UI::KEY_R));
	EScript::declareConstant(&lib, "KEY_S", static_cast<uint32_t>(Util::UI::KEY_S));
	EScript::declareConstant(&lib, "KEY_T", static_cast<uint32_t>(Util::UI::KEY_T));
	EScript::declareConstant(&lib, "KEY_U", static_cast<uint32_t>(Util::UI::KEY_U));
	EScript::declareConstant(&lib, "KEY_V", static_cast<uint32_t>(Util::UI::KEY_V));
	EScript::declareConstant(&lib, "KEY_W", static_cast<uint32_t>(Util::UI::KEY_W));
	EScript::declareConstant(&lib, "KEY_X", static_cast<uint32_t>(Util::UI::KEY_X));
	EScript::declareConstant(&lib, "KEY_Y", static_cast<uint32_t>(Util::UI::KEY_Y));
	EScript::declareConstant(&lib, "KEY_Z", static_cast<uint32_t>(Util::UI::KEY_Z));
	EScript::declareConstant(&lib, "KEY_BRACKETLEFT", static_cast<uint32_t>(Util::UI::KEY_BRACKETLEFT));
	EScript::declareConstant(&lib, "KEY_BACKSLASH", static_cast<uint32_t>(Util::UI::KEY_BACKSLASH));
	EScript::declareConstant(&lib, "KEY_BRACKETRIGHT", static_cast<uint32_t>(Util::UI::KEY_BRACKETRIGHT));
	EScript::declareConstant(&lib, "KEY_CIRCUMFLEX", static_cast<uint32_t>(Util::UI::KEY_CIRCUMFLEX));
	EScript::declareConstant(&lib, "KEY_UNDERSCORE", static_cast<uint32_t>(Util::UI::KEY_UNDERSCORE));
	EScript::declareConstant(&lib, "KEY_GRAVE", static_cast<uint32_t>(Util::UI::KEY_GRAVE));
	EScript::declareConstant(&lib, "KEY_BRACELEFT", static_cast<uint32_t>(Util::UI::KEY_BRACELEFT));
	EScript::declareConstant(&lib, "KEY_BAR", static_cast<uint32_t>(Util::UI::KEY_BAR));
	EScript::declareConstant(&lib, "KEY_BRACERIGHT", static_cast<uint32_t>(Util::UI::KEY_BRACERIGHT));
	EScript::declareConstant(&lib, "KEY_TILDE", static_cast<uint32_t>(Util::UI::KEY_TILDE));
	EScript::declareConstant(&lib, "KEY_EUROSIGN", static_cast<uint32_t>(Util::UI::KEY_EUROSIGN));

	EScript::declareConstant(&lib, "MOUSE_BUTTON_LEFT", static_cast<uint32_t>(Util::UI::MOUSE_BUTTON_LEFT));
	EScript::declareConstant(&lib, "MOUSE_BUTTON_MIDDLE", static_cast<uint32_t>(Util::UI::MOUSE_BUTTON_MIDDLE));
	EScript::declareConstant(&lib, "MOUSE_BUTTON_RIGHT", static_cast<uint32_t>(Util::UI::MOUSE_BUTTON_RIGHT));
	EScript::declareConstant(&lib, "MOUSE_WHEEL_UP", static_cast<uint32_t>(Util::UI::MOUSE_WHEEL_UP));
	EScript::declareConstant(&lib, "MOUSE_WHEEL_DOWN", static_cast<uint32_t>(Util::UI::MOUSE_WHEEL_DOWN));
	EScript::declareConstant(&lib, "MOUSE_BUTTON_OTHER", static_cast<uint32_t>(Util::UI::MOUSE_BUTTON_OTHER));

	EScript::declareConstant(&lib, "MASK_NO_BUTTON", static_cast<uint32_t>(Util::UI::MASK_NO_BUTTON));
	EScript::declareConstant(&lib, "MASK_MOUSE_BUTTON_LEFT", static_cast<uint32_t>(Util::UI::MASK_MOUSE_BUTTON_LEFT));
	EScript::declareConstant(&lib, "MASK_MOUSE_BUTTON_MIDDLE", static_cast<uint32_t>(Util::UI::MASK_MOUSE_BUTTON_MIDDLE));
	EScript::declareConstant(&lib, "MASK_MOUSE_BUTTON_RIGHT", static_cast<uint32_t>(Util::UI::MASK_MOUSE_BUTTON_RIGHT));

	EScript::declareConstant(&lib, "MASK_HAT_CENTER", static_cast<uint32_t>(Util::UI::MASK_HAT_CENTER));
	EScript::declareConstant(&lib, "MASK_HAT_UP", static_cast<uint32_t>(Util::UI::MASK_HAT_UP));
	EScript::declareConstant(&lib, "MASK_HAT_RIGHT", static_cast<uint32_t>(Util::UI::MASK_HAT_RIGHT));
	EScript::declareConstant(&lib, "MASK_HAT_DOWN", static_cast<uint32_t>(Util::UI::MASK_HAT_DOWN));
	EScript::declareConstant(&lib, "MASK_HAT_LEFT", static_cast<uint32_t>(Util::UI::MASK_HAT_LEFT));
}

E_Event::E_Event(const Util::UI::Event & event) : EScript::ExtObject() {
	setAttribute("type", EScript::create(static_cast<uint32_t>(event.type)));
	switch(event.type) {
		case Util::UI::EVENT_RESIZE:
			setAttribute("width", EScript::create(event.resize.width));
			setAttribute("height", EScript::create(event.resize.height));
			break;
		case Util::UI::EVENT_KEYBOARD:
			setAttribute("str", EScript::create(event.keyboard.str));
			setAttribute("key", EScript::create(static_cast<uint32_t>(event.keyboard.key)));
			setAttribute("pressed", EScript::create(event.keyboard.pressed));
			break;
		case Util::UI::EVENT_MOUSE_BUTTON:
			setAttribute("x", EScript::create(static_cast<uint32_t>(event.button.x)));
			setAttribute("y", EScript::create(static_cast<uint32_t>(event.button.y)));
			setAttribute("button", EScript::create(static_cast<uint32_t>(event.button.button)));
			setAttribute("pressed", EScript::create(event.button.pressed));
			break;
		case Util::UI::EVENT_MOUSE_MOTION:
			setAttribute("x", EScript::create(static_cast<uint32_t>(event.motion.x)));
			setAttribute("y", EScript::create(static_cast<uint32_t>(event.motion.y)));
			setAttribute("buttonMask", EScript::create(static_cast<uint32_t>(event.motion.buttonMask)));
			setAttribute("deltaX", EScript::create(static_cast<int32_t>(event.motion.deltaX)));
			setAttribute("deltaY", EScript::create(static_cast<int32_t>(event.motion.deltaY)));
			break;
		case Util::UI::EVENT_JOY_AXIS:
			setAttribute("joystick", EScript::create(static_cast<uint32_t>(event.joyAxis.joystick)));
			setAttribute("axis", EScript::create(static_cast<uint32_t>(event.joyAxis.axis)));
			setAttribute("value", EScript::create(static_cast<int32_t>(event.joyAxis.value)));
			break;
		case Util::UI::EVENT_JOY_BUTTON:
			setAttribute("joystick", EScript::create(static_cast<uint32_t>(event.joyButton.joystick)));
			setAttribute("button", EScript::create(static_cast<uint32_t>(event.joyButton.button)));
			setAttribute("pressed", EScript::create(event.joyButton.pressed));
			break;
		case Util::UI::EVENT_JOY_HAT:
			setAttribute("joystick", EScript::create(static_cast<uint32_t>(event.joyHat.joystick)));
			setAttribute("hat", EScript::create(static_cast<uint32_t>(event.joyHat.hat)));
			setAttribute("value", EScript::create(static_cast<uint32_t>(event.joyHat.value)));
			break;
		case Util::UI::EVENT_QUIT:
		default:
			break;
	}
}

Util::UI::Event E_Event::getEvent() const {
	Util::UI::Event event;
	event.type = static_cast<Util::UI::EventType_t>(getAttribute("type").getValue()->toUInt());
	switch(event.type) {
		case Util::UI::EVENT_RESIZE:
			event.resize.width = getAttribute("width").getValue()->toInt();
			event.resize.height = getAttribute("height").getValue()->toInt();
			break;
		case Util::UI::EVENT_KEYBOARD: {
			const std::string str = getAttribute("str").getValue()->toString();
			std::fill_n(event.keyboard.str,sizeof(event.keyboard.str),0);
			std::copy(str.data(), str.data() + std::min(static_cast<std::size_t>(4), str.size()), event.keyboard.str);
			event.keyboard.key = static_cast<Util::UI::Key>(getAttribute("key").getValue()->toUInt());
			event.keyboard.pressed = getAttribute("pressed").getValue()->toBool();
			break;
		}
		case Util::UI::EVENT_MOUSE_BUTTON:
			event.button.x = getAttribute("x").getValue()->toUInt();
			event.button.y = getAttribute("y").getValue()->toUInt();
			event.button.button = static_cast<Util::UI::Button>(getAttribute("button").getValue()->toUInt());
			event.button.pressed = getAttribute("pressed").getValue()->toBool();
			break;
		case Util::UI::EVENT_MOUSE_MOTION:
			event.motion.x = getAttribute("x").getValue()->toUInt();
			event.motion.y = getAttribute("y").getValue()->toUInt();
			event.motion.buttonMask = getAttribute("buttonMask").getValue()->toUInt();
			event.motion.deltaX = getAttribute("deltaX").getValue()->toUInt();
			event.motion.deltaY = getAttribute("deltaY").getValue()->toUInt();
			break;
		case Util::UI::EVENT_JOY_AXIS:
			event.joyAxis.joystick = getAttribute("joystick").getValue()->toUInt();
			event.joyAxis.axis = getAttribute("axis").getValue()->toUInt();
			event.joyAxis.value = getAttribute("value").getValue()->toInt();
			break;
		case Util::UI::EVENT_JOY_BUTTON:
			event.joyButton.joystick = getAttribute("joystick").getValue()->toUInt();
			event.joyButton.button = getAttribute("button").getValue()->toUInt();
			event.joyButton.pressed = getAttribute("pressed").getValue()->toBool();
			break;
		case Util::UI::EVENT_JOY_HAT:
			event.joyHat.joystick = getAttribute("joystick").getValue()->toUInt();
			event.joyHat.hat = getAttribute("hat").getValue()->toUInt();
			event.joyHat.value = getAttribute("value").getValue()->toUInt();
			break;
		case Util::UI::EVENT_QUIT:
		default:
			break;
	}
	return event;
}

E_Event* E_Event::clone()const {
	return new E_Event(getEvent());	
}
}
}
