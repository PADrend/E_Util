/*
	This file is part of the E_Util library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Window.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Util/Graphics/Bitmap.h>
#include <Util/IO/FileName.h>
#include <Util/Serialization/Serialization.h>
#include <Util/UI/UI.h>

namespace E_Util {
namespace E_UI {

EScript::Type * E_Window::getTypeObject() {
	// E_Window ---|> E_Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

void E_Window::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Window::getTypeObject();
	EScript::declareConstant(&lib, getClassName(), typeObject);

	static const EScript::StringId ATTR_borderless("borderless");
	static const EScript::StringId ATTR_debug("debug");
	static const EScript::StringId ATTR_compatibilityProfile("compatibilityProfile");
	static const EScript::StringId ATTR_fullscreen("fullscreen");
	static const EScript::StringId ATTR_multisampled("multisampled");
	static const EScript::StringId ATTR_positioned("positioned");
	static const EScript::StringId ATTR_resizable("resizable");
	static const EScript::StringId ATTR_clientAreaWidth("clientAreaWidth");
	static const EScript::StringId ATTR_clientAreaHeight("clientAreaHeight");
	static const EScript::StringId ATTR_posX("posX");
	static const EScript::StringId ATTR_posY("posY");
	static const EScript::StringId ATTR_multisamples("multisamples");
	static const EScript::StringId ATTR_title("title");
	static const EScript::StringId ATTR_shareContext("shareContext");
	static const EScript::StringId ATTR_contextVersionMajor("contextVersionMajor");
	static const EScript::StringId ATTR_contextVersionMinor("contextVersionMinor");

		
	//!(static) [ESM] ExtObject Window.createPropertyObject()
	ES_FUNCTION(typeObject, "createPropertyObject", 0, 0, {
		EScript::ERef<EScript::ExtObject> eProperties = EScript::ExtObject::create();
		const Util::UI::Window::Properties properties; // for default values
		
		eProperties->setAttribute(ATTR_borderless,EScript::Bool::create(properties.borderless));
		eProperties->setAttribute(ATTR_debug,EScript::Bool::create(properties.debug));
		eProperties->setAttribute(ATTR_compatibilityProfile,EScript::Bool::create(properties.compatibilityProfile));
		eProperties->setAttribute(ATTR_fullscreen,EScript::Bool::create(properties.fullscreen));
		eProperties->setAttribute(ATTR_multisampled,EScript::Bool::create(properties.multisampled));
		eProperties->setAttribute(ATTR_positioned,EScript::Bool::create(properties.positioned));
		eProperties->setAttribute(ATTR_resizable,EScript::Bool::create(properties.resizable));
		eProperties->setAttribute(ATTR_clientAreaWidth,EScript::Number::create(properties.clientAreaWidth));
		eProperties->setAttribute(ATTR_clientAreaHeight,EScript::Number::create(properties.clientAreaHeight));
		eProperties->setAttribute(ATTR_posX,EScript::Number::create(properties.posX));
		eProperties->setAttribute(ATTR_posY,EScript::Number::create(properties.posY));
		eProperties->setAttribute(ATTR_multisamples,EScript::Number::create(properties.multisamples));
		eProperties->setAttribute(ATTR_title,EScript::String::create(properties.title));
		eProperties->setAttribute(ATTR_shareContext,EScript::Bool::create(properties.shareContext));
		eProperties->setAttribute(ATTR_contextVersionMajor,EScript::Number::create(properties.contextVersionMajor));
		eProperties->setAttribute(ATTR_contextVersionMinor,EScript::Number::create(properties.contextVersionMinor));
		return eProperties.detachAndDecrease();
	})

	//! [ESMF] Window new Window(Properties)
	ES_CONSTRUCTOR(typeObject, 1, 1,{
		Util::UI::Window::Properties properties; 
		Object * eProperties = parameter[0].get();
		
		Object * attr;
		if( (attr = eProperties->getAttribute(ATTR_borderless).getValue()) != nullptr)
			properties.borderless = attr->toBool();
		if( (attr = eProperties->getAttribute(ATTR_debug).getValue()) != nullptr)
			properties.debug = attr->toBool();
		if( (attr = eProperties->getAttribute(ATTR_compatibilityProfile).getValue()) != nullptr)
			properties.compatibilityProfile = attr->toBool();
		if( (attr = eProperties->getAttribute(ATTR_fullscreen).getValue()) != nullptr)
			properties.fullscreen = attr->toBool();
		if( (attr = eProperties->getAttribute(ATTR_multisampled).getValue()) != nullptr)
			properties.multisampled = attr->toBool();
		if( (attr = eProperties->getAttribute(ATTR_positioned).getValue()) != nullptr)
			properties.positioned = attr->toBool();
		if( (attr = eProperties->getAttribute(ATTR_resizable).getValue()) != nullptr)
			properties.resizable = attr->toBool();
		if( (attr = eProperties->getAttribute(ATTR_clientAreaWidth).getValue()) != nullptr)
			properties.clientAreaWidth = attr->toUInt();
		if( (attr = eProperties->getAttribute(ATTR_clientAreaHeight).getValue()) != nullptr)
			properties.clientAreaHeight = attr->toUInt();
		if( (attr = eProperties->getAttribute(ATTR_posX).getValue()) != nullptr)
			properties.posX = attr->toInt();
		if( (attr = eProperties->getAttribute(ATTR_posY).getValue()) != nullptr)
			properties.posY = attr->toInt();
		if( (attr = eProperties->getAttribute(ATTR_multisamples).getValue()) != nullptr)
			properties.multisamples = attr->toUInt();
		if( (attr = eProperties->getAttribute(ATTR_title).getValue()) != nullptr)
			properties.title = attr->toString();
		if( (attr = eProperties->getAttribute(ATTR_shareContext).getValue()) != nullptr)
			properties.shareContext = attr->toBool();
		if( (attr = eProperties->getAttribute(ATTR_contextVersionMajor).getValue()) != nullptr)
			properties.contextVersionMajor = attr->toUInt();
		if( (attr = eProperties->getAttribute(ATTR_contextVersionMinor).getValue()) != nullptr)
			properties.contextVersionMinor = attr->toUInt();
		return new E_Window(properties);
	})

	//! [ESMF] Void Window.destroy()
	ES_MFUN(typeObject, E_Window, "destroy", 0, 0, (thisObj->destroy(),thisEObj))

	//! [ESMF] thisObj Window.swapBuffers()
	ES_MFUN(typeObject, E_Window, "swapBuffers", 0, 0, ((**thisObj)->swapBuffers(), thisObj))

	//! [ESMF] Number Window.getSwapInterval()
	ES_MFUN(typeObject, E_Window, "getSwapInterval", 0, 0, (**thisObj)->getSwapInterval())

	//! [ESMF] self Window.grabInput()
	ES_MFUN(typeObject, E_Window, "grabInput", 0, 0, ((**thisObj)->grabInput(),thisEObj))

	//! [ESMF] thisObj Window.hideCursor()
	ES_MFUN(typeObject, E_Window, "hideCursor", 0, 0, ((**thisObj)->hideCursor(),thisEObj))

	//! [ESMF] thisObj Window.showCursor()
	ES_MFUN(typeObject, E_Window, "showCursor", 0, 0, ((**thisObj)->showCursor(), thisObj))

	//! [ESMF] self Window.ungrabInput()
	ES_MFUN(typeObject, E_Window, "ungrabInput", 0, 0, ((**thisObj)->ungrabInput(),thisEObj))

	//! [ESMF] thisObj Window.warpCursor(Number x, Number y)
	ES_MFUN(typeObject, E_Window, "warpCursor", 2, 2, 
				 ((**thisObj)->warpCursor(parameter[0].toInt(), parameter[1].toInt()), thisObj))

	//! [ESMF] thisObj Window.setIcon(String imagePath)
	ES_MFUN(typeObject, E_Window, "setIcon", 1, 1, 
				 ((**thisObj)->setIcon(*Util::Serialization::loadBitmap(Util::FileName(parameter[0].toString())).get()), thisObj))
				 
	//! [ESMF] thisObj Window.makeCurrent()
	ES_MFUN(typeObject, E_Window, "makeCurrent", 0, 0, ((**thisObj)->makeCurrent(),thisEObj))
}

E_Window::E_Window(const Util::UI::Window::Properties & properties) :
	ReferenceObject_t(E_Window::getTypeObject(), Util::UI::createWindow(properties)) {
}

E_Window::~E_Window() = default;

void E_Window::destroy() {
	ref().reset();
}

}
}
