/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __EFileName_H
#define __EFileName_H

#include <EScript/Objects/ReferenceObject.h>
#include <EScript/Objects/Values/String.h>
#include <Util/IO/FileName.h>

namespace E_Util {

/**
 *  E_FileName ---|> [EScript::ReferenceObject]
 *     						|
 *     						------> Util::E_FileName
 */
class E_FileName : public EScript::ReferenceObject<Util::FileName> {
		ES_PROVIDES_TYPE_NAME(FileName)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		E_FileName() : ReferenceObject_t(Util::FileName(),getTypeObject()) {}
		E_FileName(const Util::FileName & q) : ReferenceObject_t(q,getTypeObject()) {}
		virtual ~E_FileName()	{}

		E_FileName * clone() const override		{	return new E_FileName(ref());	}
		std::string toString() const override		{	return ref().toString();	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_Util::E_FileName, Util::FileName*, &(**eObj))
ES_CONV_EOBJ_TO_OBJ(E_Util::E_FileName, Util::FileName&, **eObj)
ES_CONV_EOBJ_TO_OBJ(EScript::String, Util::FileName, Util::FileName(eObj->toString()))
ES_CONV_OBJ_TO_EOBJ(const Util::FileName &, E_Util::E_FileName, new E_Util::E_FileName(obj))

#endif // __EFileName_H
