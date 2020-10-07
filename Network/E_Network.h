/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_NETWORK_H
#define E_NETWORK_H

#include <EScript/Objects/Namespace.h>

namespace E_Util {
namespace Network {

/**
 * EScript network library.
 *
 * [E_Network] ---|> [Namespace]
 */
class E_Network : public EScript::Namespace{
		ES_PROVIDES_TYPE_NAME(Network)
	public:
		EUTILAPI static void init(EScript::Namespace & lib);

	private:
		EUTILAPI E_Network();
		EUTILAPI virtual ~E_Network();
};

}
}

#endif // E_NETWORK_H
