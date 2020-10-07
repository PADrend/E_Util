/*
	This file is part of the E_Util library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_E_EVENT_H
#define E_UTIL_E_EVENT_H

#include <EScript/Objects/ExtObject.h>

namespace EScript {
class Namespace;
}
namespace Util {
namespace UI {
union Event;
}
}

namespace E_Util {
namespace E_UI {

class E_Event : public EScript::ExtObject {
	ES_PROVIDES_TYPE_NAME(Event)
	public:
		EUTILAPI static void init(EScript::Namespace & lib);

		EUTILAPI E_Event(const Util::UI::Event & event);
		virtual ~E_Event() { }

		EUTILAPI E_Event* clone()const override;
		EUTILAPI Util::UI::Event getEvent() const;
};

}
}

#endif /* E_UTIL_E_EVENT_H */
