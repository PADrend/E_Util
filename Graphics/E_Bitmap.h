/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_BITMAP_H_
#define E_BITMAP_H_

#include <EScript/Objects/ReferenceObject.h>
#include <Util/Graphics/Bitmap.h>
#include <Util/Graphics/PixelFormat.h>
#include <Util/References.h>

namespace E_Util {

/**
 * EScript binding for Util::Bitmap.
 * [E_Bitmap] ---|> [ReferenceObject] ---|> [Object]
 */
class E_Bitmap : public EScript::ReferenceObject<Util::Reference<Util::Bitmap>> {
	ES_PROVIDES_TYPE_NAME(Bitmap)
	public:
		static EScript::Type * typeObject;
		static void init(EScript::Namespace & lib);

		E_Bitmap(Util::Reference<Util::Bitmap> bitmap);
		virtual ~E_Bitmap();

		std::string toString() const override;
		E_Bitmap * clone() const override;

	// -------

		//!	[E_PixelFormat] ---|> [ReferenceObject] ---|> [Object]
		class E_PixelFormat : public EScript::ReferenceObject<Util::PixelFormat> {
			ES_PROVIDES_TYPE_NAME(PixelFormat)
		public:
			static EScript::Type * pfTypeObject;
			E_PixelFormat(const Util::PixelFormat & f) : ReferenceObject_t(f,pfTypeObject) {}
			virtual ~E_PixelFormat() {}
		};
};

}

ES_CONV_EOBJ_TO_OBJ(E_Util::E_Bitmap,					Util::Reference<Util::Bitmap>,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Util::E_Bitmap,					Util::Bitmap &,						*(**eObj).get())
ES_CONV_EOBJ_TO_OBJ(E_Util::E_Bitmap::E_PixelFormat,	Util::PixelFormat &,				**eObj)
ES_CONV_OBJ_TO_EOBJ(Util::Reference<Util::Bitmap>,		E_Util::E_Bitmap,					new E_Util::E_Bitmap(obj))
ES_CONV_OBJ_TO_EOBJ(const Util::PixelFormat &, 			E_Util::E_Bitmap::E_PixelFormat,	new E_Util::E_Bitmap::E_PixelFormat(obj))

#endif /* E_BITMAP_H_ */
