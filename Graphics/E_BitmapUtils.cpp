/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_BitmapUtils.h"
#include "E_Bitmap.h"
#include <Util/Graphics/Color.h>
#include <Util/Graphics/BitmapUtils.h>
#include <Util/Graphics/PixelAccessor.h>
#include <EScript/EScript.h>
#include <EScript/Utils/DeprecatedMacros.h>

namespace E_Util {
namespace E_BitmapUtils{

using namespace EScript;
using namespace Util;

//!	initMembers
void init(EScript::Namespace & lib) {
	//! BitmapUtil.convertBitmap(Bitmap source,PixelFormat format)
	ES_FUN(&lib,"convertBitmap",2,2,
			EScript::create(BitmapUtils::convertBitmap(
				parameter[0].to<Bitmap*>(rt),
				parameter[1].to<const PixelFormat&>(rt))))

	//! void BitmapUtil._mulScalar(Bitmap source,value)
	ES_FUNCTION2(&lib,"_mulScalar",2,2,{
		const float factor = parameter[1].toFloat();
		BitmapUtils::alterBitmap(	*parameter[0].to<Bitmap *>(rt), 
									[factor](const BitmapUtils::BitmapAlteringContext & ctxt) {
										return ctxt.pixels->readColor4f(ctxt.x, ctxt.y) * factor; 
									});
		return EScript::create(nullptr);
	});

	//! Bitmap BitmapUtil.blendTogether(PixelFormat,Array of Bitmaps)
	ES_FUNCTION2(&lib, "blendTogether", 2, 2, {
		EScript::Array * arr = parameter[1].to<EScript::Array*>(rt);
		std::vector<Util::Reference<Util::Bitmap>> bitmaps;
		for(auto & element : *arr) {
			bitmaps.push_back(element.to<Bitmap*>(rt));
		}
		return E_Bitmap::create(BitmapUtils::blendTogether(parameter[0].to<const PixelFormat&>(rt), bitmaps));
	})

	//! Bitmap BitmapUtil.combineInterleaved(PixelFormat,Array of Bitmaps)
	ES_FUNCTION2(&lib, "combineInterleaved", 2, 2, {
		EScript::Array * arr = parameter[1].to<EScript::Array*>(rt);
		std::vector<Util::Reference<Util::Bitmap>> bitmaps;
		for(auto & element : *arr) {
			bitmaps.push_back(element.to<Bitmap*>(rt));
		}
		return E_Bitmap::create(BitmapUtils::combineInterleaved(parameter[0].to<const PixelFormat&>(rt), bitmaps));
	})
}

}
}
