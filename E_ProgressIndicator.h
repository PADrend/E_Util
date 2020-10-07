/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_PROGRESSINDICATOR_H_
#define E_PROGRESSINDICATOR_H_

#include <EScript/Objects/ReferenceObject.h>
#include <Util/ProgressIndicator.h>

namespace E_Util {

class E_ProgressIndicator : public EScript::ReferenceObject<Util::ProgressIndicator> {
	ES_PROVIDES_TYPE_NAME(ProgressIndicator)
	public:
		static EScript::Type * typeObject;
		EUTILAPI static void init(EScript::Namespace & lib);

		//! Create a new Util::ProgressIndicator with the given parameters (see Util::ProgressIndicator for a description of the parameters).
		EUTILAPI E_ProgressIndicator(std::string description, uint32_t totalSteps, double updateInterval);
		virtual ~E_ProgressIndicator() {}
};

}

#endif /* E_PROGRESSINDICATOR_H_ */
