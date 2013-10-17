/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Timer.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <sstream>
#include <string>

using namespace Util;
using namespace EScript;

namespace E_Util {
//--------------------------------------------------------------------------------------------------
// E_Timer

//! (static)
EScript::Type * E_Timer::getTypeObject() {
	// E_Timer ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//!	initMembers
void E_Timer::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESF] Timer new Timer()
	ES_CTOR(typeObject,0,0,new E_Timer)

	//! [ESMF] Number Timer.getMilliseconds()
	ES_MFUN(typeObject,const Timer,"getMilliseconds", 0, 0, thisObj->getMilliseconds())

	//! [ESMF] Number Timer.getMicroseconds()
	ES_MFUN(typeObject,const Timer,"getMicroseconds", 0, 0, thisObj->getMicroseconds())

	//! [ESMF] Number Timer.getNanoseconds()
	ES_MFUN(typeObject,const Timer,"getNanoseconds", 0, 0, static_cast<double>(thisObj->getNanoseconds()))

	//! [ESMF] Number Timer.getSeconds()
	ES_MFUN(typeObject,const Timer,"getSeconds", 0, 0, thisObj->getSeconds())

	//! [ESMF] Bool Timer.isRunning()
	ES_MFUN(typeObject,const Timer, "isRunning", 0, 0, thisObj->isRunning())

	//! [ESMF] thisObj Timer.reset()
	ES_MFUN(typeObject,Timer,"reset", 0, 0, (thisObj->reset(),thisEObj))

	//! [ESMF] thisObj Timer.resume()
	ES_MFUN(typeObject,Timer,"resume", 0, 0, (thisObj->resume(),thisEObj))

	//! [ESMF] thisObj Timer.stop()
	ES_MFUN(typeObject,Timer,"stop", 0, 0, (thisObj->stop(),thisEObj))

	// static
	//! [ESF] (static) Number Timer.now()
	ES_FUN(typeObject,"now", 0, 0,  Timer::now())

}

}
