/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_DataBroadcaster.h"
#include "E_DataConnection.h"
#include <EScript/Basics.h>

namespace E_Util{
namespace Network{


//! (static)
EScript::Type * E_DataBroadcaster::getTypeObject() {
	// E_DataBroadcaster ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members 
void E_DataBroadcaster::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_DataBroadcaster::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);


	//! [ESF] new DataBroadcaster()
	ES_CTOR(typeObject,0,0,
				new E_DataBroadcaster(new Util::Network::DataBroadcaster))

	//! [ESMF] thisObj DataBroadcaster.addDataConnection(E_DataConnection)
	ES_MFUN(typeObject,E_DataBroadcaster,"addDataConnection",1,1,
				((**thisObj)->addDataConnection((**EScript::assertType<E_DataConnection>(rt,parameter[0])).get()),thisEObj))

}
}

}

