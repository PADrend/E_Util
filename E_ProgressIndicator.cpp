/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_ProgressIndicator.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_Util {

EScript::Type * E_ProgressIndicator::typeObject = nullptr;

void E_ProgressIndicator::init(EScript::Namespace & lib) {
	typeObject = new EScript::Type(Object::getTypeObject());
	declareConstant(&lib, getClassName(), typeObject);

	//! [ESMF] ProgressIndicator new ProgressIndicator(String description, Number totalSteps, Number updateInterval)
	ES_CTOR(typeObject, 3, 3, new E_ProgressIndicator(parameter[0].toString(), parameter[1].toInt(), parameter[2].toDouble()))

	//! [ESMF] Void ProgressIndicator.increment()
	ES_MFUN(typeObject, E_ProgressIndicator, "increment", 0, 0, ((**thisObj).increment(), EScript::create(nullptr)))
}

E_ProgressIndicator::E_ProgressIndicator(std::string description, uint32_t totalSteps, double updateInterval) :
		EScript::ReferenceObject<Util::ProgressIndicator>(Util::ProgressIndicator(description, totalSteps, updateInterval), typeObject) {
}

}
