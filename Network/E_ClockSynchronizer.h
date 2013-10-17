/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_SYNCHRONIZER_H
#define E_SYNCHRONIZER_H

#include <EScript/Objects/ReferenceObject.h>
#include <Util/Network/ClockSynchronizer.h>

namespace E_Util{
namespace Network{

/**
 **   [E_ClockSynchronizer] ---|> [ReferenceObject] ---|> [Object]
 **/
class E_ClockSynchronizer : public EScript::ReferenceObject<Util::Network::ClockSynchronizer * > {
		ES_PROVIDES_TYPE_NAME(ClockSynchronizer)
	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		E_ClockSynchronizer(Util::Network::ClockSynchronizer * s);

		Util::Network::ClockSynchronizer * getSynchronizer()const{
			return ref();
		}
};
}
}
#endif // E_SYNCHRONIZER_H
