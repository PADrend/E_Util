/*
	This file is part of the E_Util library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_E_UPDATABLEHEAP_H
#define E_UTIL_E_UPDATABLEHEAP_H

#include <EScript/Objects/ReferenceObject.h>
#include <Util/UpdatableHeap.h>
#include <memory>

namespace EScript {
class Namespace;
class Type;
}
namespace E_Util {

class E_UpdatableHeap : public EScript::ReferenceObject<std::unique_ptr<Util::UpdatableHeap<double, EScript::ObjRef>>> {
	ES_PROVIDES_TYPE_NAME(UpdatableHeap)
	public:
		EUTILAPI static EScript::Type * getTypeObject();
		EUTILAPI static void init(EScript::Namespace & lib);

		EUTILAPI E_UpdatableHeap(EScript::Type * type = nullptr);
		EUTILAPI virtual ~E_UpdatableHeap();
};

}

#endif /* E_UTIL_E_UPDATABLEHEAP_H */
