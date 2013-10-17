/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ClockSynchronizer.h"

#include <EScript/EScript.h>

using namespace Util::Network;
using namespace Util;
using namespace EScript;

namespace E_Util {
namespace Network {

//! (static)
EScript::Type * E_ClockSynchronizer::getTypeObject() {
	// E_ClockSynchronizer ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_ClockSynchronizer::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESF] (static) ClockSynchronizer ClockSynchronizer.createSever(port)
	ES_FUN(typeObject,"createServer",1,1,
			new E_ClockSynchronizer( ClockSynchronizer::createServer( parameter[0].toInt())))

	//! [ESF] (static) ClockSynchronizer ClockSynchronizer.createClient(host, port)
	ES_FUN(typeObject,"createClient",2,2,
			new E_ClockSynchronizer( ClockSynchronizer::createClient(
				Util::Network::IPAddress::resolveHost(   parameter[0].toString(),parameter[1].toInt()))))

	// ----

	//! [ESMF] Number ClockSynchronizer.getClockSec()
	ES_MFUN(typeObject,E_ClockSynchronizer,"getClockSec",0,0,thisObj->getSynchronizer()->getClockSec())

	//! [ESMF] Bool ClockSynchronizer.isRunning()
	ES_MFUN(typeObject,E_ClockSynchronizer,"isRunning",0,0,thisObj->getSynchronizer()->isRunning())

	//! [ESMF] thisObj ClockSynchronizer.close()
	ES_MFUN(typeObject,E_ClockSynchronizer,"close",0,0,(thisObj->getSynchronizer()->close(),thisEObj))
}

//---

E_ClockSynchronizer::E_ClockSynchronizer(Util::Network::ClockSynchronizer * s):ReferenceObject<Util::Network::ClockSynchronizer * >(s,getTypeObject()){
}

}
}
