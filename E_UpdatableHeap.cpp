/*
	This file is part of the E_Util library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_UpdatableHeap.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_Util {

class E_UpdatableHeapElement : public EScript::ReferenceObject<Util::UpdatableHeap<double, EScript::ObjRef>::UpdatableHeapElement *> {
	ES_PROVIDES_TYPE_NAME(UpdatableHeapElement)
	public:
		static EScript::Type * getTypeObject() {
			// E_UpdatableHeapElement ---|> [Object]
			static auto typeObject = new EScript::Type(EScript::Object::getTypeObject());
			return typeObject;
		}
		static void init(EScript::Namespace & lib) {
			EScript::Type * typeObject = E_UpdatableHeapElement::getTypeObject();
			EScript::declareConstant(&lib, getClassName(), typeObject);
			
			//! [ESMF] Object UpdatableHeapElement.data()
			ES_MFUN(typeObject, E_UpdatableHeapElement, "data", 0, 0, (**thisObj)->data.get())
			
			//! [ESMF] Object UpdatableHeapElement.getCost()
			ES_MFUN(typeObject, const E_UpdatableHeapElement, "getCost", 0, 0, EScript::Number::create((**thisObj)->getCost()))
		}

		E_UpdatableHeapElement(Util::UpdatableHeap<double, EScript::ObjRef>::UpdatableHeapElement * element,
							   EScript::Type * type = nullptr) :
			ReferenceObject_t(element, type ? type : getTypeObject()) {
		}
		virtual ~E_UpdatableHeapElement() {
		}
};

EScript::Type * E_UpdatableHeap::getTypeObject() {
	// E_UpdatableHeap ---|> [Object]
	static auto typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject;
}

void E_UpdatableHeap::init(EScript::Namespace & lib) {
	E_UpdatableHeapElement::init(lib);

	EScript::Type * typeObject = E_UpdatableHeap::getTypeObject();
	EScript::declareConstant(&lib, getClassName(), typeObject);

	//! [ESF] UpdatableHeap new UpdatableHeap()
	ES_CTOR(typeObject, 0, 0,new E_UpdatableHeap)

	//! [ESMF] UpdatableHeapElement UpdatableHeap.insert(Number, Object)
	ES_MFUN(typeObject, E_UpdatableHeap, "insert", 2, 2, 
				 new E_UpdatableHeapElement((**thisObj)->insert(parameter[0].toDouble(), parameter[1])))

	//! [ESMF] thisObj UpdatableHeap.erase(UpdatableHeapElement)
	ES_MFUN(typeObject, E_UpdatableHeap, "erase", 1, 1, 
				 ((**thisObj)->erase(**EScript::assertType<E_UpdatableHeapElement>(rt, parameter[0])), thisObj))

	//! [ESMF] thisObj UpdatableHeap.pop()
	ES_MFUN(typeObject, E_UpdatableHeap, "pop", 0, 0, 
				 ((**thisObj)->pop(), thisObj))

	//! [ESMF] thisObj UpdatableHeap.clear()
	ES_MFUN(typeObject, E_UpdatableHeap, "clear", 0, 0, 
				 ((**thisObj)->clear(), thisObj))

	//! [ESMF] thisObj UpdatableHeap.update(UpdatableHeapElement, Number)
	ES_MFUN(typeObject, E_UpdatableHeap, "update", 2, 2, 
				 ((**thisObj)->update(**EScript::assertType<E_UpdatableHeapElement>(rt, parameter[0]), parameter[1].toDouble()), thisObj))

	//! [ESMF] UpdatableHeapElement UpdatableHeap.top()
	ES_MFUN(typeObject, E_UpdatableHeap, "top", 0, 0, 
				 new E_UpdatableHeapElement((**thisObj)->top()))

	//! [ESMF] Number UpdatableHeap.size()
	ES_MFUN(typeObject, const E_UpdatableHeap, "size", 0, 0, 
				 EScript::Number::create(static_cast<double>((**thisObj)->size())))
}

E_UpdatableHeap::E_UpdatableHeap(EScript::Type * type) :
	ReferenceObject_t(type ? type : getTypeObject(), new Util::UpdatableHeap<double, EScript::ObjRef>) {
}

E_UpdatableHeap::~E_UpdatableHeap() = default;

}
