/*
	This file is part of the E_Util library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_E_EVENTCONTEXT_H
#define E_UTIL_E_EVENTCONTEXT_H

#include <EScript/Objects/ReferenceObject.h>
#include <Util/UI/EventContext.h>

namespace EScript {
class Type;
class Namespace;
}

namespace E_Util {
namespace E_UI {

class E_EventContext : public EScript::ReferenceObject<Util::UI::EventContext, EScript::Policies::SameEObjects_ComparePolicy> {
	ES_PROVIDES_TYPE_NAME(EventContext)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_EventContext() : ReferenceObject_t(E_EventContext::getTypeObject()) {
		}
		virtual ~E_EventContext() {
		}
};

}
}

#endif /* E_UTIL_E_EVENTCONTEXT_H */
