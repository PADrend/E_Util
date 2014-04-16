/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_FileLocator.h"
#include "../E_FileName.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_Util {

//! (static)
EScript::Type * E_FileLocator::getTypeObject() {
	// E_FileLocator ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_FileLocator::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_FileLocator::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	
	using namespace Util;

	//! [ESF] new FileLocator
	ES_CTOR(typeObject, 0, 0, new E_FileLocator)

	//! [ESMF] thisEObj FileLocator.getPath()
	ES_MFUN(typeObject, FileLocator, "addSearchPath", 1, 1,	 (thisObj->addSearchPath(parameter[0].toString()),thisEObj))

	//! [ESMF] Array FileLocator.getSearchPaths()
	ES_MFUN(typeObject, const FileLocator, "getSearchPaths", 0, 0,	 EScript::Array::create(thisObj->getSearchPaths()))

	//! [ESMF] thisEObj FileLocator.setSearchPaths(Array)
	ES_MFUNCTION(typeObject, FileLocator, "setSearchPaths", 1, 1,{
		std::vector<std::string> paths;
		for(const auto& obj : *parameter[0].to<EScript::Array*>(rt))
			paths.emplace_back(obj->toString());
		thisObj->setSearchPaths(paths);
		return thisEObj;
	})

	//! [ESMF] String FileLocator.locateFile(String )
	ES_MFUNCTION(typeObject, const FileLocator, "locateFile", 1, 1,	 {
		const auto result = thisObj->locateFile( FileName( parameter[0].to<std::string>(rt)));
		if(!result.first)
			return EScript::create(false);
		else 
			return EScript::create(result.second);
	})
	
}

}
