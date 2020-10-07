/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_TIMER_H
#define E_UTIL_TIMER_H

#include <EScript/Objects/ReferenceObject.h>
#include <Util/Timer.h>

namespace E_Util{

/**
 ** EScript-Binding for Util::Timer
 **   [Timer] ---|> [ReferenceObject] ---|> [Object]
 **/
class E_Timer : public EScript::ReferenceObject<Util::Timer> {
		ES_PROVIDES_TYPE_NAME(Timer)
	public:
		EUTILAPI static EScript::Type* getTypeObject();
		EUTILAPI static void init(EScript::Namespace & lib);

		E_Timer() : ReferenceObject_t(Util::Timer(),getTypeObject())	{}
		E_Timer(const Util::Timer & t) : ReferenceObject_t(Util::Timer(t),getTypeObject()) 	{}
		virtual ~E_Timer()	{}

		E_Timer * clone() const override		{	return new E_Timer(ref());	}
};

}

ES_CONV_EOBJ_TO_OBJ(E_Util::E_Timer, 	Util::Timer*, 	&(**eObj))
ES_CONV_EOBJ_TO_OBJ(E_Util::E_Timer,	Util::Timer&, 	**eObj)

#endif // E_UTIL_TIMER_H
