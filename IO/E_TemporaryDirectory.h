/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef _E_Util_E_TemporaryDirectory_H_
#define _E_Util_E_TemporaryDirectory_H_

#include <EScript/Objects/ReferenceObject.h>
#include <Util/IO/TemporaryDirectory.h>

namespace EScript {
class Namespace;
class Type;
}
namespace E_Util{

//!	EScript wrapper class for Util::TemporaryDirectory
class E_TemporaryDirectory : public EScript::ReferenceObject<Util::TemporaryDirectory, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(TemporaryDirectory)
	public:
		EUTILAPI static EScript::Type * getTypeObject();
		EUTILAPI static void init(EScript::Namespace & lib);

		template<typename ... Types>
		explicit E_TemporaryDirectory(Types && ... params) :
			ReferenceObject_t(E_TemporaryDirectory::getTypeObject(), std::forward<Types>(params) ...) {
		}
		virtual ~E_TemporaryDirectory() {
		}
};

}

#endif // _E_Util_E_TemporaryDirectory_H_
