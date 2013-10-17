/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Color.h"

#include <EScript/EScript.h>

using namespace Util;

namespace EScript{
template<> Util::Color4f convertTo<Util::Color4f>(Runtime & rt,ObjPtr obj){
	E_Util::E_Color4f * ec = obj.toType<E_Util::E_Color4f>();
	if(ec)
		return **ec;
	return Util::Color4f(**assertType<E_Util::E_Color4ub>(rt,obj));
}
template<> Util::Color4ub convertTo<Util::Color4ub>(Runtime & rt,ObjPtr obj){
	E_Util::E_Color4ub * ec = obj.toType<E_Util::E_Color4ub>();
	if(ec)
		return **ec;
	return Util::Color4ub(**assertType<E_Util::E_Color4f>(rt,obj));
}

}

namespace E_Util {

//--------------------------------------------------------------------------------------------------
// E_Color4ub

EScript::Type * E_Color4ub::getTypeObject() {
	// E_Matrix3x3 ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_Color4ub::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] Color4ub new Color4ub(Color4ub | Color4f | Array | Number, Number, Number[, Number])
	ES_CONSTRUCTOR(typeObject,0,4,{
		if(parameter.count()==1){

			/// copy constructor
			E_Color4ub * cub = parameter[0].toType<E_Color4ub>();
			if(cub)
				return EScript::create(**cub);

			/// converting copy constructor
			E_Color4f * cf = parameter[0].toType<E_Color4f>();
			if(cf)
				return EScript::create(Color4ub(**cf));

			/// Array Constructor
			EScript::Array * ar = parameter[0].to<EScript::Array*>(rt);
			const uint32_t alpha = ar->count()>=4 ? ar->at(3).to<uint32_t>(rt) : 255;
			return new E_Color4ub( ar->at(0).to<uint32_t>(rt),ar->at(1).to<uint32_t>(rt),ar->at(2).to<uint32_t>(rt),alpha );
		}

		/// 3/4 value constructor
		assertParamCount(rt, parameter.count(),3,4);
		return new E_Color4ub( parameter[0].to<uint32_t>(rt),parameter[1].to<uint32_t>(rt),parameter[2].to<uint32_t>(rt),parameter[3].toUInt(255));
	})


	//! [ESMF] Number Color4ub.r() || thisObj Color4ub.r(Number)
	ES_MFUNCTION(typeObject,Color4ub,"r", 0, 1, {
		if(parameter.count()==0)
			return static_cast<uint32_t>(thisObj->getR());
		thisObj->setR(parameter[0].to<uint32_t>(rt));
		return thisEObj;
	})

	//! [ESMF] Number Color4ub.g() || thisObj Color4ub.g(Number)
	ES_MFUNCTION(typeObject,Color4ub,"g", 0, 1, {
		if(parameter.count()==0)
			return static_cast<uint32_t>(thisObj->getG());
		thisObj->setG(parameter[0].to<uint32_t>(rt));
		return thisEObj;
	})

	//! [ESMF] Number Color4ub.b() || thisObj Color4ub.b(Number)
	ES_MFUNCTION(typeObject,Color4ub,"b", 0, 1, {
		if(parameter.count()==0)
			return static_cast<uint32_t>(thisObj->getB());
		thisObj->setB(parameter[0].to<uint32_t>(rt));
		return thisEObj;
	})

	//! [ESMF] Number Color4ub.a() || thisObj Color4ub.a(Number)
	ES_MFUNCTION(typeObject,Color4ub,"a", 0, 1, {
		if(parameter.count()==0)
			return static_cast<uint32_t>(thisObj->getA());
		thisObj->setA(parameter[0].to<uint32_t>(rt));
		return thisEObj;
	})

	//! [ESMF Number Color4ub.getAsUInt()
	ES_MFUN(typeObject,const Color4ub,"getAsUInt",0,0,static_cast<uint32_t>(thisObj->getAsUInt()) )

	//! [ESMF Array Color4ub.toArray()
	ES_MFUNCTION(typeObject,const Color4ub,"toArray",0,0,{
		const Color4ub & c=(*thisObj);
		EScript::Array *a = EScript::Array::create();
		a->pushBack(EScript::create(static_cast<uint32_t>(c.getR())));
		a->pushBack(EScript::create(static_cast<uint32_t>(c.getG())));
		a->pushBack(EScript::create(static_cast<uint32_t>(c.getB())));
		a->pushBack(EScript::create(static_cast<uint32_t>(c.getA())));
		return a;
	})
}

//---


//! ---|> [Object]
std::string E_Color4ub::toString()const{
	std::stringstream s;
	s<< ref().toString();
	return s.str();
}



//--------------------------------------------------------------------------------------------------
// E_Color4f

//! (static)
EScript::Type * E_Color4f::getTypeObject() {
	// E_Color4f ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_Color4f::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] Color4f new Color4f.(Color4ub | Color4f | Array | Number, Number, Number[, Number] | Color4f,Color4f,Number )
	ES_CONSTRUCTOR(typeObject,0,4,{
		if(parameter.count()==1){

			/// copyconstructor (Color4f)
			E_Color4f * cf = parameter[0].toType<E_Color4f>();
			if(cf)
				return EScript::create(**cf);

			/// converting copy constructor (Color4ub)
			E_Color4ub * cub = parameter[0].toType<E_Color4ub>();
			if(cub)
				return EScript::create(Color4f(**cub));

			/// Array Constructor (Array)
			const EScript::Array * ar = parameter[0].to<EScript::Array*>(rt);
			const float alpha = ar->count()>=4 ? ar->at(3)->toFloat() : 1.0f;
			return new E_Color4f( ar->at(0).toFloat(),ar->at(1).toFloat(),ar->at(2).toFloat(),alpha );

		} /// mixing constructor (Color4f,Color4f,Number)
		else if( parameter.count()==3 && parameter[0].toType<E_Color4f>() ){
			return new E_Color4f( parameter[0].to<Color4f>(rt),parameter[1].to<Color4f>(rt),parameter[2].toFloat() );
		}

		/// 3/4 value constructor
		assertParamCount(rt, parameter.count(),3,4);
		return new E_Color4f( parameter[0].toFloat(),parameter[1].toFloat(),parameter[2].toFloat(),parameter[3].toFloat(1.0f) );
	})


	//! [ESMF] Number Color4f.r() || thisObj Color4f.r(Number)
	ES_MFUNCTION(typeObject,Color4f,"r", 0, 1, {
		if(parameter.count()==0)
			return thisObj->getR();
		thisObj->setR(parameter[0].toFloat());
		return thisEObj;
	})

	//! [ESMF] Number Color4f.g() || thisObj Color4f.g(Number)
	ES_MFUNCTION(typeObject,Color4f,"g", 0, 1, {
		if(parameter.count()==0)
			return thisObj->getG();
		thisObj->setG(parameter[0].toFloat());
		return thisEObj;
	})

	//! [ESMF] Number Color4f.b() || thisObj Color4f.b(Number)
	ES_MFUNCTION(typeObject,Color4f,"b", 0, 1, {
		if(parameter.count()==0)
			return thisObj->getB();
		thisObj->setB(parameter[0].toFloat());
		return thisEObj;
	})

	//! [ESMF] Number Color4f.a() || thisObj Color4f.a(Number)
	ES_MFUNCTION(typeObject,Color4f,"a", 0, 1, {
		if(parameter.count()==0)
			return thisObj->getA();
		thisObj->setA(parameter[0].toFloat());
		return thisEObj;
	})

	//! [ESMF] Color4f Color4f."+"( Color4f )
	ES_MFUN(typeObject,const Color4f,"+", 1, 1, EScript::create( (*thisObj) + parameter[0].to<Color4f>(rt) ) )

	//! [ESMF] thisObj Color4f."+="( Color4f )
	ES_MFUN(typeObject,Color4f,"+=", 1, 1, ( ((*thisObj) += parameter[0].to<Color4f>(rt)),thisEObj))

	//! [ESMF] Color4f Color4f."-"( Color4f )
	ES_MFUN(typeObject,const Color4f,"-", 1, 1, EScript::create( (*thisObj) - parameter[0].to<Color4f>(rt) ) )

	//! [ESMF] thisObj Color4f."-="( Color4f )
	ES_MFUN(typeObject,Color4f,"-=", 1, 1, ( ((*thisObj) -= parameter[0].to<Color4f>(rt)),thisEObj))

	//! [ESMF] Color4f Color4f."*"( Number )
	ES_MFUN(typeObject,const Color4f,"*", 1, 1, EScript::create( (*thisObj) * parameter[0].toFloat() ) )

	//! [ESMF] thisObj Color4f."*="( Number )
	ES_MFUN(typeObject,Color4f,"*=", 1, 1, ( ((*thisObj) *= parameter[0].toFloat()),thisEObj))

	//! [ESMF] Color4f Color4f."/"( Number )
	ES_MFUN(typeObject,const Color4f,"/", 1, 1, EScript::create( (*thisObj) / parameter[0].toFloat() ) )

	//! [ESMF] thisObj Color4f."/="( Number )
	ES_MFUN(typeObject,Color4f,"/=", 1, 1, ( ((*thisObj) /= parameter[0].toFloat()),thisEObj))

	//! [ESMF Array Color4f.toArray()
	ES_MFUNCTION(typeObject,const Color4f,"toArray",0,0,{
		const Color4f & c=(*thisObj);
		EScript::Array *a = EScript::Array::create();
		a->pushBack(EScript::create(c.getR()));
		a->pushBack(EScript::create(c.getG()));
		a->pushBack(EScript::create(c.getB()));
		a->pushBack(EScript::create(c.getA()));
		return a;
	})
}

//---

//! ---|> [Object]
std::string E_Color4f::toString()const{
	std::stringstream s;
	s<< ref().toString();
	return s.str();
}

}
