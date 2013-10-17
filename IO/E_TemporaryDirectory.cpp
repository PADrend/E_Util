/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_TemporaryDirectory.h"
#include <EScript/Basics.h>

namespace E_Util {

//! (static)
EScript::Type * E_TemporaryDirectory::getTypeObject() {
	// E_TemporaryDirectory ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_TemporaryDirectory::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_TemporaryDirectory::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	//! [ESF] new TemporaryDirectory(String)
	ES_CTOR(typeObject, 1, 1,
				new E_TemporaryDirectory(parameter[0].toString()))

	//! [ESMF] String TemporaryDirectory.getPath()
	ES_MFUN(typeObject, const E_TemporaryDirectory, "getPath", 0, 0,
				 (**thisObj).getPath().toString())
}

}
