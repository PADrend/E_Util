/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_NETWORK_E_DATABROADCASTER_H_
#define E_UTIL_NETWORK_E_DATABROADCASTER_H_

#include <EScript/Objects/ReferenceObject.h>
#include <Util/Network/DataBroadcaster.h>


namespace EScript {
class Namespace;
class Type;
}
namespace E_Util{
namespace Network{


/*!	EScript wrapper class for Util::Network::DataBroadcaster

		E_DataBroadcaster ---|> EScript::ReferenceObject<Util::Reference<Util::Network::DataBroadcaster>>
			|
			--------------> Util::Network::DataBroadcaster		*/
class E_DataBroadcaster : public EScript::ReferenceObject<Util::Reference<Util::Network::DataBroadcaster>> {
		ES_PROVIDES_TYPE_NAME(DataBroadcaster)
	public:
		EUTILAPI static EScript::Type * getTypeObject();
		EUTILAPI static void init(EScript::Namespace & lib);

		E_DataBroadcaster(Util::Network::DataBroadcaster * _obj,EScript::Type * type=nullptr) : 
				ReferenceObject_t(_obj, type ? type : E_DataBroadcaster::getTypeObject()) {}
		virtual ~E_DataBroadcaster() {}

};
}
}

#endif // E_UTIL_NETWORK_E_DATABROADCASTER_H_

