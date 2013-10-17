/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_MICROXMLREADER_H
#define E_MICROXMLREADER_H

#include <EScript/EScript.h>

namespace E_Util{

/**
 **   [E_MicroXMLReader]  ---|> [ExtObject]
 **/
class E_MicroXMLReader : public EScript::ExtObject {
		ES_PROVIDES_TYPE_NAME(MicroXMLReader)
	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		E_MicroXMLReader(EScript::Type * type=nullptr);
		virtual ~E_MicroXMLReader();
};

}


#endif // E_MICROXMLREADER_H
