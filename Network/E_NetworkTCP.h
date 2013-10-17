/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_NETWORK_TCP_H
#define E_NETWORK_TCP_H

#include <EScript/Objects/ReferenceObject.h>
#include <Util/Network/NetworkTCP.h>
#include <memory>

namespace Util {
namespace Network {
class TCPServer;
class UDPNetworkSocket;
}
}

namespace E_Util {
namespace Network {

// ----------------------------------------------------------------------------

/**
 *   [E_TCPConnection] ---|> [ReferenceObject]
 */
class E_TCPConnection : public EScript::ReferenceObject<Util::Reference<Util::Network::TCPConnection>>{
		ES_PROVIDES_TYPE_NAME(TCPConnection)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_TCPConnection(const Util::Reference<Util::Network::TCPConnection> & _obj, EScript::Type * type = nullptr) : 
			ReferenceObject_t(type ? type : getTypeObject(), _obj) {
		}
		virtual ~E_TCPConnection() {
		}

};

/**
 *   [E_TCPServer] ---|> [ReferenceObject]
 */
class E_TCPServer : public EScript::ReferenceObject<std::unique_ptr<Util::Network::TCPServer>> {
		ES_PROVIDES_TYPE_NAME(TCPServer)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_TCPServer(Util::Network::TCPServer * _obj, EScript::Type * type = nullptr) :
			ReferenceObject_t(type ? type : getTypeObject(), _obj) {
		}
		virtual ~E_TCPServer() {
		}
};

}
}

#endif // E_NETWORK_TCP_H
