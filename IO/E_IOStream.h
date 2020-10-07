/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef _E_Util_E_IOStream_H_
#define _E_Util_E_IOStream_H_

#include <EScript/Objects/ReferenceObject.h>
#include <iostream>
#include <memory>

namespace EScript {
class Namespace;
class Type;
}
namespace E_Util{

//!	EScript wrapper class for Util::IOStream
class E_IOStream : public EScript::ReferenceObject<std::unique_ptr<std::iostream>, EScript::Policies::SameEObjects_ComparePolicy> {
		ES_PROVIDES_TYPE_NAME(IOStream)
	public:
		EUTILAPI static EScript::Type * getTypeObject();
		EUTILAPI static void init(EScript::Namespace & lib);

		template<typename ... Types>
		explicit E_IOStream(Types && ... params) :
			ReferenceObject_t(E_IOStream::getTypeObject(), std::forward<Types>(params) ...) {
		}
		virtual ~E_IOStream() {}
};

}


ES_CONV_EOBJ_TO_OBJ(E_Util::E_IOStream, std::iostream*, (**eObj).get())
ES_CONV_EOBJ_TO_OBJ(E_Util::E_IOStream, std::iostream&, *(**eObj).get())

#endif // _E_Util_E_IOStream_H_
