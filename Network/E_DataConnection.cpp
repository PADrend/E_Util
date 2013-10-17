/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_DataConnection.h"
#include "E_NetworkTCP.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_Util{
namespace Network{


//! (static)
EScript::Type * E_DataConnection::getTypeObject() {
	// E_DataConnection ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members 
void E_DataConnection::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_DataConnection::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESF] new DataConnection(TCPConnection)
	ES_CTOR(typeObject,1,1,
				new E_DataConnection( 
						new Util::Network::DataConnection( (**EScript::assertType<E_TCPConnection>(rt,parameter[0])).get()),thisType))

	//! [ESMF] thisObj DataConnection.close()
	ES_MFUN(typeObject,E_DataConnection,"close",0,0,	((**thisObj)->close(),thisEObj))
	
	//! [ESMF] Bool DataConnection.isOpen()
	ES_MFUN(typeObject,E_DataConnection,"isOpen",0,0,	(**thisObj)->isOpen())

//	//! [ESMF] thisEObj DataConnection.handleIncomingData([maxDurationInMS])
//	ES_MFUN(typeObject,E_DataConnection,"handleIncomingData",0,1,	((**thisObj)->handleIncomingData(parameter[0].to<float>(rt,-1.0)),thisEObj))


	// ExtObject{ channelId, stringData } | void
	ES_MFUNCTION(typeObject,E_DataConnection,"receiveValue",0,0,{
		(**thisObj)->handleIncomingData(); // process incoming data
		
		if(thisObj->incomingData.empty()){
			return EScript::create(false);
		}else{
			static const EScript::StringId ATTR_CHANNEL_ID("channelId");
			static const EScript::StringId ATTR_DATA("data");
			auto * result = new EScript::ExtObject;
			result->setAttribute(ATTR_CHANNEL_ID,EScript::create(static_cast<uint32_t>(thisObj->incomingData.front().first)));
			const auto & data = thisObj->incomingData.front().second;
			const std::string strData(reinterpret_cast<const char*>(data.data()),data.size());
			result->setAttribute(ATTR_DATA,EScript::create(strData));
			thisObj->incomingData.pop();
			return result;
		}
	})

	// ExtObect{ channelId, stringData }
	ES_MFUNCTION(typeObject,E_DataConnection,"sendValue",2,2,{
		const std::string strData(parameter[1].to<std::string>(rt));
		const std::vector<uint8_t> data(strData.c_str(),strData.c_str()+strData.length() );
		(**thisObj)->sendValue(parameter[0].to<uint16_t>(rt),data);
		return thisEObj;
	})

}

void E_DataConnection::_handleIncomingValue(Util::Network::DataConnection::channelId_t c,const Util::Network::DataConnection::dataPacket_t & data){
	incomingData.push(std::make_pair(c,data));
//std::vector<std::pair<Util::Network::DataConnection::channelId_t,const Util::Network::DataConnection::dataPacket_t>> incomingData;
}




E_DataConnection::E_DataConnection( Util::Network::DataConnection * dataConnection,EScript::Type * type) : 
			ReferenceObject_t(dataConnection, type ? type : E_DataConnection::getTypeObject()) {
		
	dataConnection->registerValueChannelHandler(Util::Network::DataConnection::FALLBACK_HANDLER,
						std::bind(&E_DataConnection::_handleIncomingValue, this,
										std::placeholders::_1,std::placeholders::_2));

}

}
}
