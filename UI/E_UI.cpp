/*
	This file is part of the E_Util library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_UI.h"
#include "E_Event.h"
#include "E_EventContext.h"
#include "E_EventQueue.h"
#include "E_SplashScreen.h"
#include "E_Window.h"
#include <EScript/Basics.h>

namespace E_Util {
namespace E_UI {

void init(EScript::Namespace * parentNamespace) {
	auto uiNamespace = new EScript::Namespace;
	EScript::declareConstant(parentNamespace, "UI", uiNamespace);
	
	E_Event::init(*uiNamespace);
	E_EventContext::init(*uiNamespace);
	E_EventQueue::init(*uiNamespace);
	E_SplashScreen::init(*uiNamespace);
	E_Window::init(*uiNamespace);
}

}
}
