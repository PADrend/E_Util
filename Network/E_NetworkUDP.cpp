/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_NetworkUDP.h"

#include <Util/Network/NetworkUDP.h>

#include <EScript/EScript.h>

using namespace EScript;

namespace E_Util {
namespace Network {

//! (static)
EScript::Type * E_UDPNetworkSocket::getTypeObject() {
	// E_UDPNetworkSocket ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//!	[E_UDPNetworkSocket] initMembers
void E_UDPNetworkSocket::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] thisObj UDPNetworkSocket.addTarget(string hostname,number port)
	ES_MFUN(typeObject,E_UDPNetworkSocket,"addTarget",2,2,
				((**thisObj)->addTarget(Util::Network::IPv4Address::resolveHost(
					parameter[0].toString(),parameter[1].toInt())),thisEObj))

	//! [ESMF] thisObj UDPNetworkSocket.close()
	ES_MFUN(typeObject,E_UDPNetworkSocket,"close",0,0,
				((**thisObj)->close(),thisEObj))

	//! [ESMF] bool UDPNetworkSocket.isOpen()
	ES_MFUN(typeObject,E_UDPNetworkSocket,"isOpen",0,0,
				Bool::create((**thisObj)->isOpen()))

	//! [ESMF] bool UDPNetworkSocket.open()
	ES_MFUN(typeObject,E_UDPNetworkSocket,"open",0,0,
				Bool::create((**thisObj)->open()))

	//!	[ESMF] DataObj|Void UDPNetworkSocket.receive()
	ES_MFUNCTION(typeObject,E_UDPNetworkSocket,"receive",0,0,{
		Util::Network::UDPNetworkSocket::Packet * p =(**thisObj)->receive();
		if(p==nullptr)  return nullptr;
		ExtObject * o=new ExtObject();

		o->setAttribute("data",String::create(p->getString()));
		o->setAttribute("dataSize",Number::create(p->packetData.size()));
		o->setAttribute("host",String::create(p->source.getHostAsString()));
		o->setAttribute("port",Number::create(p->source.getPort()));
		return o;
	})

	//! [ESMF] thisObj UDPNetworkSocket.removeTarget(string hostname,number port[,channel=0])
	ES_MFUN(typeObject,E_UDPNetworkSocket,"removeTarget",2,2,
				((**thisObj)->removeTarget(Util::Network::IPv4Address::resolveHost(parameter[0].toString(),parameter[1].toInt())),thisEObj))

	//! [ESMF] number UDPNetworkSocket.sendString(string s)
	ES_MFUN(typeObject,E_UDPNetworkSocket,"sendString",1,1,
				Number::create((**thisObj)->sendString(parameter[0].toString())))

}

E_UDPNetworkSocket::E_UDPNetworkSocket(Util::Network::UDPNetworkSocket * _obj, EScript::Type * type):
	ReferenceObject_t(type ? type : getTypeObject(), _obj) {
}

E_UDPNetworkSocket::~E_UDPNetworkSocket() = default;

}
}
