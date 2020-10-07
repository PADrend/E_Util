/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_NETWORK_UDP_H
#define E_NETWORK_UDP_H

#include <EScript/Objects/ReferenceObject.h>
#include <memory>

namespace Util {
namespace Network {
class UDPNetworkSocket;
}
}

namespace E_Util {
namespace Network {

/**
 *   [E_UDPNetworkSocket] ---|> [Object]
 */
class E_UDPNetworkSocket : public EScript::ReferenceObject<std::unique_ptr<Util::Network::UDPNetworkSocket>> {
		ES_PROVIDES_TYPE_NAME(UDPNetworkSocket)
	public:
		EUTILAPI static EScript::Type* getTypeObject();
		EUTILAPI static void init(EScript::Namespace & lib);

		EUTILAPI E_UDPNetworkSocket(Util::Network::UDPNetworkSocket * obj,EScript::Type * type=nullptr);
		EUTILAPI virtual ~E_UDPNetworkSocket();
};

}
}

#endif // E_NETWORK_UDP_H
