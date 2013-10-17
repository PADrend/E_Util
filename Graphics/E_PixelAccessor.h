/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_PIXELACCESSOR_H
#define E_UTIL_PIXELACCESSOR_H

#include <EScript/Objects/ReferenceObject.h>
#include <Util/References.h>
#include <Util/Graphics/PixelAccessor.h>

namespace E_Util{

/**
 ** EScript-Binding for Util::Color
 **   [E_PixelAccessor] ---|> [ReferenceObject] ---|> [Object]
 **/
class E_PixelAccessor : public EScript::ReferenceObject<Util::Reference<Util::PixelAccessor> >{
		ES_PROVIDES_TYPE_NAME(PixelAccessor)
	public:
		static EScript::Type* getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_PixelAccessor(args&&... params) :
			ReferenceObject_t(E_PixelAccessor::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_PixelAccessor();
};
}

ES_CONV_EOBJ_TO_OBJ(E_Util::E_PixelAccessor,				Util::PixelAccessor&,		*(**eObj).get())
ES_CONV_EOBJ_TO_OBJ(E_Util::E_PixelAccessor,				Util::PixelAccessor*,		(**eObj).get())
ES_CONV_OBJ_TO_EOBJ(Util::PixelAccessor*, 					E_Util::E_PixelAccessor,	new E_Util::E_PixelAccessor(obj))
ES_CONV_OBJ_TO_EOBJ(Util::Reference<Util::PixelAccessor>, 	E_Util::E_PixelAccessor,	new E_Util::E_PixelAccessor(obj))

#endif // E_UTIL_PIXELACCESSOR_H
