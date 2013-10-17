/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_NetworkTCP.h"

#include <EScript/EScript.h>
#include <EScript/Utils/DeprecatedMacros.h>

using namespace EScript;
using namespace Util::Network;

namespace E_Util {
namespace Network {

//! (static)
EScript::Type * E_TCPConnection::getTypeObject() {
	// E_TCPConnection ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! [E_TCPConnection] initMembers
void E_TCPConnection::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESF] (static) TCPConnection|false TCPConnection.connect(host,port)
	ES_FUNCTION2(typeObject,"connect",2,2,{
		Util::Reference<TCPConnection> s=TCPConnection::connect(IPAddress::resolveHost(parameter[0].toString(), parameter[1].toInt()));
		if (s.isNull()) {
			return Bool::create(false);
		} else {
			return new E_TCPConnection(s);
		}
	})
	// ----

	//! [ESMF] thisObj TCPConnection.close()
	ES_MFUN(typeObject,E_TCPConnection,"close",0,0,((**thisObj)->close(),thisEObj))

	//! [ESMF] thisObj TCPConnection.isOpen()
	ES_MFUN(typeObject,E_TCPConnection,"isOpen",0,0,(**thisObj)->isOpen())

	//! [ESMF] String|false TCPConnection.receiveString([delimiter='\0'])
	ES_MFUNCTION(typeObject,E_TCPConnection,"receiveString",0,1,{
		std::string s=(**thisObj)->receiveString(parameter[0].toString("\0").c_str()[0]);
		if (s.empty()) {
			return EScript::create(false);
		} else {
			return EScript::create(s);
		}
	})

	//! [ESMF] thisObj TCPConnection.sendString(String,[delimiter='\0'])
	ES_MFUN(typeObject,E_TCPConnection,"sendString",1,2,
				((**thisObj)->sendString(parameter[0].toString()+parameter[1].toString("\0").c_str()[0]),thisEObj))
}

//---

// ------------------------------------------------------------------------------

//! (static)
EScript::Type * E_TCPServer::getTypeObject() {
	// E_TCPServer ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! [E_TCPServer] initMembers
void E_TCPServer::init(EScript::Namespace & lib) {

	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESF] (static) TCPServer|false TCPServer.create(port)
	ES_FUNCTION2(typeObject,"create",1,1,{
		TCPServer * s=TCPServer::create(parameter[0].toInt());
		if (s == nullptr) {
			return Bool::create(false);
		} else {
			return new E_TCPServer(s);
		}
	})

	// -----------

	//! [ESMF] thisObj TCPServer.close()
	ES_MFUN(typeObject,E_TCPServer,"close",0,0,((**thisObj)->close(),thisEObj))

	//! [ESMF] bool TCPServer.isOpen()
	ES_MFUN(typeObject,const E_TCPServer,"isOpen",0,0,Bool::create((**thisObj)->isOpen()))

	//! [ESMF] TCPConnection|false TCPServer.getIncomingConnection()
	ES_MFUNCTION(typeObject,E_TCPServer,"getIncomingConnection",0,0,{
		Util::Reference<TCPConnection> c=(**thisObj)->getIncomingConnection();
		if (c == nullptr) {
			return EScript::create(false);
		} else {
			return new E_TCPConnection(c);
		}
	})

}

}
}
