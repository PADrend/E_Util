/*
	This file is part of the E_Util library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_EventQueue.h"
#include "E_Event.h"
#include "E_Window.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Util/UI/EventQueue.h>
#include <Util/UI/Window.h>
#include <functional>

namespace E_Util {
namespace E_UI {

EScript::Type * E_EventQueue::getTypeObject() {
	// E_EventQueue ---|> E_Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

void E_EventQueue::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_EventQueue::getTypeObject();
	EScript::declareConstant(&lib, getClassName(), typeObject);
	
	//! [ESMF] Number EventQueue.getNumEventsAvailable()
	ES_MFUN(typeObject, const E_EventQueue, "getNumEventsAvailable", 0, 0, 
				 EScript::Number::create((**thisObj).getNumEventsAvailable()))

	//! [ESMF] Event EventQueue.peekEvent()
	ES_MFUN(typeObject, const E_EventQueue, "peekEvent", 0, 0, new E_Event((**thisObj).peekEvent()))

	//! [ESMF] Event EventQueue.popEvent()
	ES_MFUN(typeObject, E_EventQueue, "popEvent", 0, 0, new E_Event((**thisObj).popEvent()))

	//! [ESMF] Void EventQueue.process()
	ES_MFUN(typeObject, E_EventQueue, "process", 0, 0, ((**thisObj).process(), EScript::create(nullptr)))

	//! [ESMF] Void EventQueue.registerWindow()
	ES_MFUNCTION(typeObject, E_EventQueue, "registerWindow", 1, 1, {
		(**thisObj).registerEventGenerator(std::bind(&Util::UI::Window::fetchEvents, 
												  (**EScript::assertType<E_Window>(rt, parameter[0])).get()));
		return EScript::create(nullptr);
	})
}

E_EventQueue::E_EventQueue(Util::UI::EventQueue & eventQueue) : 
	ReferenceObject_t(eventQueue, E_EventQueue::getTypeObject()) {
}

E_EventQueue::~E_EventQueue() = default;

}
}
