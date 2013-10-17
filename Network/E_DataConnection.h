/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_NETWORK_E_DATACONNECTION_H_
#define E_UTIL_NETWORK_E_DATACONNECTION_H_

#include <EScript/Objects/ReferenceObject.h>
#include <Util/Network/DataConnection.h>
#include <queue>

namespace EScript {
class Namespace;
class Type;
}
namespace E_Util{
namespace Network{


/*!	EScript wrapper class for Util::Network::DataConnection

		E_DataConnection ---|> EScript::ReferenceObject<Util::Reference<Util::Network::DataConnection> >
			|
			--------------> Util::Network::DataConnection		*/
class E_DataConnection : public EScript::ReferenceObject<Util::Reference<Util::Network::DataConnection> > {
		ES_PROVIDES_TYPE_NAME(DataConnection)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_DataConnection( Util::Network::DataConnection * _obj,EScript::Type * type=nullptr);
		E_DataConnection(E_DataConnection&) = delete;
		virtual ~E_DataConnection() {}
		
		void _handleIncomingValue(Util::Network::DataConnection::channelId_t,const Util::Network::DataConnection::dataPacket_t &);
	private:
		std::queue<std::pair<Util::Network::DataConnection::channelId_t,const Util::Network::DataConnection::dataPacket_t>> incomingData;
};
}
}

#endif // E_UTIL_NETWORK_E_DATACONNECTION_H_

