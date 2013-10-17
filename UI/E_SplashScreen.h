/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_SPLASHSCREEN_H
#define E_UTIL_SPLASHSCREEN_H

#include <EScript/Objects/ReferenceObject.h>
#include <Util/UI/SplashScreen.h>
#include <Util/References.h>
#include <memory>

namespace E_Util {
namespace E_UI {

/**
 ** EScript-Binding for Util::UI::SplashScreen
 **   [E_SplashScreen] ---|> [ReferenceObject] ---|> [Object]
 **/
class E_SplashScreen : public EScript::ReferenceObject<std::unique_ptr<Util::UI::SplashScreen>> {
	ES_PROVIDES_TYPE_NAME(SplashScreen)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		//! Create a new Util::UI::SplashScreen with the given title and background image.
		E_SplashScreen(const std::string & title, const std::string & imagePath);

		//! The destructor calls @a destroy().
		virtual ~E_SplashScreen();

		//! Display a message on the splash screen. Automatically checks if the splash screen pointer is valid.
		void showMessage(const std::string & message);

		//! Delete the SplashScreen pointer and thereby close the splash screen.
		void destroy();

	private:
		Util::Reference<Util::Bitmap> bitmap;
};

}
}

#endif /* E_UTIL_SPLASHSCREEN_H */
