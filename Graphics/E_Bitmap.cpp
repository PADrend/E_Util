/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Bitmap.h"

#include <EScript/EScript.h>

#include <Util/Graphics/Bitmap.h>
#include <Util/Graphics/BitmapUtils.h>
#include <sstream>

namespace E_Util {

EScript::Type * E_Bitmap::typeObject = nullptr;
EScript::Type * E_Bitmap::E_PixelFormat::pfTypeObject = nullptr;

//!	initMembers
void E_Bitmap::init(EScript::Namespace & lib) {
	// E_Bitmap ----|> Object
	typeObject = new EScript::Type(Object::getTypeObject());
	declareConstant(&lib,getClassName(),typeObject);
	using namespace Util;

	//!	[ESF] Bitmap new Bitmap(width,height,E_PixelFormat format)
	ES_CTOR(typeObject,3,3,
			new Bitmap( parameter[0].to<uint32_t>(rt),parameter[1].to<uint32_t>(rt), parameter[2].to<const AttributeFormat&>(rt)))

	//!	[ESMF] thisObj Bitmap.flipVertically()
	ES_MFUN(typeObject, Bitmap, "flipVertically", 0, 0, (thisObj->flipVertically(),thisEObj))

	//!	[ESMF] Number Bitmap.getWidth()
	ES_MFUN(typeObject, const Bitmap, "getWidth", 0, 0, thisObj->getWidth())

	//!	[ESMF] Number Bitmap.getHeight()
	ES_MFUN(typeObject, const Bitmap, "getHeight", 0, 0, thisObj->getHeight())

	//!	[ESMF] Number Bitmap.getDataSize()
	ES_MFUN(typeObject, const Bitmap, "getDataSize", 0, 0, static_cast<uint32_t>(thisObj->getDataSize()))

	//!	[ESMF] Number Bitmap.getChannelCount()
	ES_MFUN(typeObject, const Bitmap, "getChannelCount", 0, 0, thisObj->getPixelFormat().getComponentCount())

	//!	[ESMF] TypeConstant Bitmap.getChannelType()
	ES_MFUN(typeObject, const Bitmap, "getChannelType", 0, 0, static_cast<uint32_t>(thisObj->getPixelFormat().getDataType()))

	//!	[ESMF] Number Bitmap.getBytesPerPixel()
	ES_MFUN(typeObject, const Bitmap, "getBytesPerPixel", 0, 0, static_cast<uint32_t>(thisObj->getPixelFormat().getDataSize()))

	/// E_PixelFormat ----|> Object
	E_PixelFormat::pfTypeObject = new EScript::Type(Object::getTypeObject());
	declareConstant(typeObject,E_PixelFormat::getClassName(),E_PixelFormat::pfTypeObject);

	declareConstant(typeObject,"RGB",		EScript::create(PixelFormat::RGB));
	declareConstant(typeObject,"RGB_FLOAT",	EScript::create(PixelFormat::RGB_FLOAT));
	declareConstant(typeObject,"BGR",		EScript::create(PixelFormat::BGR));
	declareConstant(typeObject,"BGR_FLOAT",	EScript::create(PixelFormat::BGR_FLOAT));
	declareConstant(typeObject,"RGBA",		EScript::create(PixelFormat::RGBA));
	declareConstant(typeObject,"RGBA_FLOAT",EScript::create(PixelFormat::RGBA_FLOAT));
	declareConstant(typeObject,"BGRA",		EScript::create(PixelFormat::BGRA));
	declareConstant(typeObject,"BGRA_FLOAT",EScript::create(PixelFormat::BGRA_FLOAT));
	declareConstant(typeObject,"MONO",		EScript::create(PixelFormat::MONO));
	declareConstant(typeObject,"MONO_FLOAT",EScript::create(PixelFormat::MONO_FLOAT));
	declareConstant(typeObject,"UNKNOWN",	EScript::create(PixelFormat::UNKNOWN));

}

//---

E_Bitmap::E_Bitmap(Util::Reference<Util::Bitmap> bitmap) : 
	ReferenceObject_t(typeObject, std::move(bitmap)) {
}

E_Bitmap::~E_Bitmap() {
}

//!	---|> [Object]
std::string E_Bitmap::toString() const {
	std::stringstream s;
	auto b = ref();
	s << "Bitmap(width=" << b->getWidth() << ", height=" << b->getHeight() << ", bytes=" << b->getPixelFormat().getDataSize()<<")" ; // \todo add format<< ", reverse=" << b->getReverseBytes()
//			<< ")";
	return s.str();
}

//!	---|> [Object]
E_Bitmap * E_Bitmap::clone()const{
	return new E_Bitmap( new Util::Bitmap(*(ref().get()) ));
}

}
