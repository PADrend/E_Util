/*
	This file is part of the E_Util library.
	Copyright (C) 2014 Claudius Jähn <claudius@uni-paderborn.de>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_IOStream.h"
#include "../E_FileName.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

namespace E_Util {

//! (static)
EScript::Type * E_IOStream::getTypeObject() {
	// E_IOStream ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! (static) init members
void E_IOStream::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_IOStream::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);
	
	using namespace Util;


	//! [ESMF] String|void IOStream._get( )
	ES_MFUNCTION(typeObject, std::iostream, "_get", 0, 0,	{
		int c = thisObj->get();
		if( c ==std::char_traits<char>::eof() )
			return EScript::create(nullptr);
		else
			return EScript::create(std::string("")+static_cast<char>(c));
	})

	//! [ESMF] thisEObj IOStream.write( String )
	ES_MFUNCTION(typeObject, std::iostream, "write", 1, 1,	{
		const std::string s = parameter[0].toString();
		thisObj->write(s.c_str(),s.length());
		return thisEObj;
	})

	//! [ESMF] Bool IOStream.good( )
	ES_MFUN(typeObject, const std::iostream, "good", 0, 0,	 thisObj->good())

	//! [ESMF] Bool IOStream.eof( )
	ES_MFUN(typeObject, const std::iostream, "eof", 0, 0,	 thisObj->eof())

	//! [ESMF] Bool IOStream.fail( )
	ES_MFUN(typeObject, const std::iostream, "fail", 0, 0,	 thisObj->fail())

	//! [ESMF] thisEObj IOStream.flush( )
	ES_MFUN(typeObject, std::iostream, "flush", 0, 0,	 (thisObj->flush(),thisEObj))

	//! [ESMF] thisEObj IOStream.clear( )
	ES_MFUN(typeObject, std::iostream, "clear", 0, 0,	 (thisObj->clear(),thisEObj))

}

}
