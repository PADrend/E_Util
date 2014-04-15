/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Network.h"
#include "E_DataBroadcaster.h"
#include "E_DataConnection.h"
#include "E_NetworkTCP.h"
#include "E_NetworkUDP.h"
#include "E_ClockSynchronizer.h"

#include <Util/Network/Network.h>
#include <Util/Network/NetworkTCP.h>
#include <Util/Network/NetworkUDP.h>

#include <EScript/EScript.h>


using namespace EScript;

namespace E_Util {
namespace Network {

//! initMembers
void E_Network::init(EScript::Namespace & lib) {
	/// [E_Network] ----|> [Object]
	EScript::Namespace * networkLib=new E_Network();
	declareConstant(&lib,getClassName(),networkLib);

	//-------------

	//! [ESF] bool Network.init()
	ES_FUNCTION(networkLib,"init",0,0, {
		if (!Util::Network::init()) {
			std::cout << "Network initialization failed!\n";
			return Bool::create(false);
		}
		return Bool::create(true);
	})

	//! [ESF] TCPNetworkSocket Network.createUDPNetworkSocket(port=0,maxPktSize=1024)
	ES_FUN(networkLib,"createUDPNetworkSocket",0,2,
		new E_UDPNetworkSocket(Util::Network::createUDPNetworkSocket(
				parameter[0].toInt(0),
				parameter[1].toInt(Util::Network::UDPNetworkSocket::defaultMaxPktSize))))

	//-------------

	E_DataBroadcaster::init(*networkLib);
	E_DataConnection::init(*networkLib);
	E_TCPConnection::init(*networkLib);
	E_TCPServer::init(*networkLib);
	E_UDPNetworkSocket::init(*networkLib);
	E_ClockSynchronizer::init(*networkLib);
}

//---

//! [ctor]
E_Network::E_Network():Namespace(){
}

//! [dtor]
E_Network::~E_Network(){
}

}
}
