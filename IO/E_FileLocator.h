/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef _E_Util_E_FileLocator_H_
#define _E_Util_E_FileLocator_H_

#include <EScript/Objects/ReferenceObject.h>
#include <Util/IO/FileLocator.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_Util{

//!	EScript wrapper class for Util::FileLocator
class E_FileLocator : public EScript::ReferenceObject<Util::FileLocator, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(FileLocator)
	public:
		EUTILAPI static EScript::Type * getTypeObject();
		EUTILAPI static void init(EScript::Namespace & lib);

		template<typename ... Types>
		explicit E_FileLocator(Types && ... params) :
			ReferenceObject_t(E_FileLocator::getTypeObject(), std::forward<Types>(params) ...) {
		}
		virtual ~E_FileLocator() {}
};

}


ES_CONV_EOBJ_TO_OBJ(E_Util::E_FileLocator, Util::FileLocator*, &(**eObj))
ES_CONV_EOBJ_TO_OBJ(E_Util::E_FileLocator, Util::FileLocator&, **eObj)

#endif // _E_Util_E_FileLocator_H_
