/*
	This file is part of the E_Util library.
	Copyright (C) 2012 Benjamin Eikel <benjamin@eikel.org>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_WINDOW_H
#define E_UTIL_WINDOW_H

#include <EScript/Objects/ReferenceObject.h>
#include <Util/UI/Window.h>
#include <memory>
#include <string>

namespace EScript {
class Type;
class Namespace;
}

namespace E_Util {
namespace E_UI {

class E_Window : public EScript::ReferenceObject<Util::Reference<Util::UI::Window>> {
	ES_PROVIDES_TYPE_NAME(Window)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		//! Create a new Util::UI::Window with the given properties.
		E_Window(const Util::UI::Window::Properties & properties);

		//! The destructor calls @a destroy().
		virtual ~E_Window();

		//! Delete the Window pointer and thereby close the window.
		void destroy();
};

}
}

ES_CONV_EOBJ_TO_OBJ(E_Util::E_UI::E_Window, Util::UI::Window*, (**eObj).get())

#endif /* E_UTIL_WINDOW_H */
