/*
	This file is part of the E_Util library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_EventContext.h"
#include "E_EventQueue.h"
#include <EScript/Basics.h>
#include <Util/UI/EventContext.h>
#include <functional>

namespace E_Util {
namespace E_UI {

EScript::Type * E_EventContext::getTypeObject() {
	// E_EventContext ---|> E_Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

void E_EventContext::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_EventContext::getTypeObject();
	EScript::declareConstant(&lib, getClassName(), typeObject);

	//! [ESF] new EventContext()
	ES_CTOR(typeObject, 0, 0, new E_EventContext)

	//! [ESMF] EventQueue EventContext.getEventQueue()
	ES_MFUN(typeObject, E_EventContext, "getEventQueue", 0, 0, 
				 new E_EventQueue((**thisObj).getEventQueue()))

	//! [ESMF] Bool EventContext.isKeyPressed(Number)
	ES_MFUN(typeObject, E_EventContext, "isKeyPressed", 1, 1, 
				 (**thisObj).isKeyPressed(
					 static_cast<Util::UI::Key>(parameter[0].to<uint32_t>(rt))))

	//! [ESMF] Bool EventContext.isAltPressed()
	ES_MFUN(typeObject, E_EventContext, "isAltPressed", 0, 0, 
				 (**thisObj).isAltPressed())

	//! [ESMF] Bool EventContext.isCtrlPressed()
	ES_MFUN(typeObject, E_EventContext, "isCtrlPressed", 0, 0, 
				 (**thisObj).isCtrlPressed())

	//! [ESMF] Bool EventContext.isShiftPressed()
	ES_MFUN(typeObject, E_EventContext, "isShiftPressed", 0, 0, 
				 (**thisObj).isShiftPressed())
}

}
}
