/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_FileName.h"

#include <EScript/EScript.h>

using namespace EScript;

namespace E_Util {

//! (static)
Type * E_FileName::getTypeObject(){
	// [E_FileName] ---|> [Object]
	static auto typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject;
}

//! initMembers
void E_FileName::init(EScript::Namespace & lib) {
	using namespace Util;
	// E_FileName ---|> [Object]
	Type * typeObject=getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] FileName new FileName( [String] )
	ES_CTOR(typeObject,0,1,EScript::create(Util::FileName(parameter[0].toString())))

	//! [ESMF] Bool FileName.empty()
	ES_MFUN(typeObject,const FileName,"empty",0,0,thisObj->empty())

	//! [ESMF] String FileName.getDir()
	ES_MFUN(typeObject,const FileName,"getDir",0,0,thisObj->getDir())

	//! [ESMF] String FileName.getFile()
	ES_MFUN(typeObject,const FileName,"getFile",0,0,thisObj->getFile())

	//! [ESMF] String FileName.getEnding()
	ES_MFUN(typeObject,const FileName,"getEnding",0,0,thisObj->getEnding())

	//! [ESMF] String FileName.getFSName()
	ES_MFUN(typeObject,FileName,"getFSName",0,0,thisObj->getFSName())

	//! [ESMF] String FileName.getPath()
	ES_MFUN(typeObject,FileName,"getPath",0,0,thisObj->getPath())

	//! [ESMF] thisObj FileName.setDir(String)
	ES_MFUN(typeObject,FileName,"setDir",1,1,(thisObj->setDir(parameter[0].toString()),thisEObj))

	//! [ESMF] thisObj FileName.setFile(String)
	ES_MFUN(typeObject,FileName,"setFile",1,1,(thisObj->setFile(parameter[0].toString()),thisEObj))

	//! [ESMF] thisObj FileName.setEnding(String)
	ES_MFUN(typeObject,FileName,"setEnding",1,1,(thisObj->setEnding(parameter[0].toString()),thisEObj))

	//! [ESMF] thisObj FileName.setFile(setFSName)
	ES_MFUN(typeObject,FileName,"setFSName",1,1,(thisObj->setFSName(parameter[0].toString()),thisEObj))
}

}
