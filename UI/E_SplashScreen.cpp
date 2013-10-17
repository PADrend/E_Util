/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_SplashScreen.h"

#include <EScript/EScript.h>
#include <Util/Graphics/Bitmap.h>
#include <Util/IO/FileName.h>
#include <Util/Serialization/Serialization.h>
#include <Util/UI/UI.h>

namespace E_Util {
namespace E_UI {

EScript::Type * E_SplashScreen::getTypeObject() {
	// E_SplashScreen ---|> E_Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

void E_SplashScreen::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_SplashScreen::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	using namespace EScript;

	//! [ESMF] SplashScreen new SplashScreen(String title, String imagePath)
	ES_CTOR(typeObject, 2, 2, new E_SplashScreen(parameter[0].toString(), parameter[1].toString()))

	//! [ESMF] Void SplashScreen.showMessage(String)
	ES_MFUN(typeObject, E_SplashScreen, "showMessage", 1, 1, (thisObj->showMessage(parameter[0].toString()), EScript::create(nullptr)))

	//! [ESMF] Void SplashScreen.destroy()
	ES_MFUN(typeObject, E_SplashScreen, "destroy", 0, 0, (thisObj->destroy(), EScript::create(nullptr)))
}

E_SplashScreen::E_SplashScreen(const std::string & title, const std::string & imagePath) :
	ReferenceObject_t(E_SplashScreen::getTypeObject(), nullptr), bitmap(Util::Serialization::loadBitmap(Util::FileName(imagePath))) {
	ref().reset(Util::UI::createSplashScreen(title, bitmap.get()));
}

E_SplashScreen::~E_SplashScreen() = default;

void E_SplashScreen::destroy() {
	ref().reset();
}

void E_SplashScreen::showMessage(const std::string & message) {
	if(ref()) {
		ref()->showMessage(message);
	}
}


}
}
