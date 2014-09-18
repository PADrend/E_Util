/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_PixelAccessor.h"
#include "E_Bitmap.h"
#include "E_Color.h"

#include <EScript/EScript.h>

#include <Util/Macros.h>

using namespace Util;
using namespace EScript;

namespace E_Util {

//--------------------------------------------------------------------------------------------------
// E_PixelAccessor

//! (static)
EScript::Type * E_PixelAccessor::getTypeObject() {
	// E_PixelAccessor ---|> Object
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::Object::getTypeObject());
	return typeObject.get();
}

//! initMembers
void E_PixelAccessor::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESF] (static) PixelAccessor|Void Util.PixelAccessor.create(Bitmap)
	ES_FUNCTION(typeObject,"create",1,1,{
		Util::Reference<PixelAccessor> acc = Util::PixelAccessor::create( parameter[0].to<Reference<Bitmap>>(rt) );
		if(acc!=nullptr)
			return EScript::create(acc);
		else
			return EScript::create(nullptr);
	})


	//! [ESMF] Bitmap PixelAccessor.getBitmap()
	ES_MFUN(typeObject,PixelAccessor,"getBitmap",0,0,EScript::create(thisObj->getBitmap() ))

	//! [ESMF] Number PixelAccessor.getWidth()
	ES_MFUN(typeObject,const PixelAccessor,"getWidth",0,0,thisObj->getWidth() )

	//! [ESMF] Number PixelAccessor.getHeight()
	ES_MFUN(typeObject,const PixelAccessor,"getHeight",0,0,thisObj->getHeight() )

	//! [ESMF] Color4f PixelAccessor.readColor4f(x,y)
	ES_MFUN(typeObject,const PixelAccessor,"readColor4f",2,2,
				EScript::create(thisObj->readColor4f(parameter[0].to<uint32_t>(rt),parameter[1].to<uint32_t>(rt)) ))

	//! [ESMF] Color4ub PixelAccessor.readColor4ub(x,y)
	ES_MFUN(typeObject,const PixelAccessor,"readColor4ub",2,2,
				EScript::create(thisObj->readColor4ub(parameter[0].to<uint32_t>(rt),parameter[1].to<uint32_t>(rt)) ))

	//! [ESMF] thisObj PixelAccessor.writeColor(x,y, (Color4ub|Color4f) )
	ES_MFUNCTION(typeObject,PixelAccessor,"writeColor",3,3,{
		thisObj->writeColor(parameter[0].to<uint32_t>(rt),parameter[1].to<uint32_t>(rt), parameter[2].to<Color4f>(rt));
		return thisEObj;
	})

	//! [ESMF] thisObj PixelAccessor.writeSingleValueFloat(x,y, Number )
	ES_MFUN(typeObject,PixelAccessor,"writeSingleValueFloat",3,3,
		(thisObj->writeSingleValueFloat(parameter[0].to<uint32_t>(rt),parameter[1].to<uint32_t>(rt), parameter[2].to<float>(rt)),thisEObj))

	//! [ESMF] thisObj PixelAccessor.fill(x,y,width,height, (Color4ub|Color4f) )
	ES_MFUNCTION(typeObject,PixelAccessor,"fill",5,5,{
		thisObj->fill(parameter[0].to<uint32_t>(rt),parameter[1].to<uint32_t>(rt),parameter[2].to<uint32_t>(rt),parameter[3].to<uint32_t>(rt),parameter[4].to<Color4f>(rt));
		return thisEObj;
	})
}


E_PixelAccessor::~E_PixelAccessor() {
}

}
