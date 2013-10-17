/*
	This file is part of the E_Util library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_E_UI_H
#define E_UTIL_E_UI_H

// Forward declaration.
namespace EScript {
class Namespace;
}

namespace E_Util {
namespace E_UI {
void init(EScript::Namespace * parentNamespace);
}
}

#endif /* E_UTIL_E_UI_H */
