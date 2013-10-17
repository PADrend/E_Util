/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_COLOR_H
#define E_UTIL_COLOR_H

#include <EScript/Objects/ReferenceObject.h>
#include <Util/Graphics/Color.h>
#include <Util/References.h>

namespace E_Util{

/**
 ** EScript-Binding for Util::Color
 **   [E_Color4ub] ---|> [ReferenceObject] ---|> [Object]
 **/
class E_Color4ub : public EScript::ReferenceObject<Util::Color4ub> {
		ES_PROVIDES_TYPE_NAME(Color4ub)
	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Color4ub(args&&... params) :
			ReferenceObject_t(E_Color4ub::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Color4ub() {}

		E_Color4ub * clone() const override		{	return new E_Color4ub(ref());	}
		std::string toString()const override;
};

/**
 ** EScript-Binding for Util::Color
 **   [E_Color4f] ---|> [ReferenceObject] ---|> [Object]
 **/
class E_Color4f : public EScript::ReferenceObject<Util::Color4f> {
		ES_PROVIDES_TYPE_NAME(Color4f)
	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Color4f(args&&... params) :
			ReferenceObject_t(E_Color4f::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Color4f() {}

		E_Color4f * clone() const override		{	return new E_Color4f(ref());	}
		std::string toString()const override;
};

}

ES_CONV_EOBJ_TO_OBJ(E_Util::E_Color4f,				Util::Color4f*,			&(**eObj))
ES_CONV_EOBJ_TO_OBJ(E_Util::E_Color4ub,				Util::Color4ub*,		&(**eObj))
ES_CONV_OBJ_TO_EOBJ(const Util::Color4f&, 			E_Util::E_Color4f,		new E_Util::E_Color4f(obj))
ES_CONV_OBJ_TO_EOBJ(Util::Color4f&&, 				E_Util::E_Color4f,		new E_Util::E_Color4f(obj))
ES_CONV_OBJ_TO_EOBJ(const Util::Color4ub&, 			E_Util::E_Color4ub,		new E_Util::E_Color4ub(obj))
ES_CONV_OBJ_TO_EOBJ(Util::Color4ub&&, 				E_Util::E_Color4ub,		new E_Util::E_Color4ub(obj))

namespace EScript{ // automatic conversion functions
template<> Util::Color4f convertTo<Util::Color4f>(Runtime & rt,ObjPtr obj);
template<> Util::Color4ub convertTo<Util::Color4ub>(Runtime & rt,ObjPtr obj);
}
#endif // E_UTIL_COLOR_H
