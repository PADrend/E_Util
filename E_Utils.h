/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTILS_H
#define E_UTILS_H

#include <EScript/Utils/ObjRef.h>
#include <Util/AttributeProvider.h>

#include <list>

namespace EScript {
class AttributeContainer;
class ExtObject;
class Object;
class Type;
}

namespace Util {
class AttributeProvider;
class GenericAttribute;
}

namespace E_Util {


namespace Policies{

/*! Policy that can be used for ExtRefObjects to store the EScript attributeContainer inside of an AttributeContainer's attribute.
	\note the Referenced object has to inherit from  AttributeContainer. */
class StoreAttrsInAttributeProvider{
		EUTILAPI static EScript::AttributeContainer * _getAttributeContainer(Util::AttributeProvider * attrProvider,bool create);

	protected:
		template<typename attrProviderERef>
		static inline EScript::AttributeContainer * getAttributeContainer(attrProviderERef * obj,bool create){
			return _getAttributeContainer(obj->ref().get(),create);
		}

		template<typename attrProviderERef>
		static bool areObjAttributesInitialized(attrProviderERef * obj){
			return getAttributeContainer(obj,false)!=nullptr;
		}
};

}

/// some static Helpers
class E_Utils {
	public:
		EUTILAPI static EScript::Object * convertGenericAttributeToEScriptObject(const Util::GenericAttribute * ga, bool warn = true);

		EUTILAPI static Util::GenericAttribute * convertEScriptObjectToGenericAttribute(EScript::ObjPtr obj);

		/**
		 * Abstract base class for converters between GenericAttributes and EScript objects.
		 *
		 * @author Benjamin Eikel
		 * @date 2010-04-07
		 */
		class AbstractGenericAttributeConverter {
			public:
				virtual ~AbstractGenericAttributeConverter() {}

				//! Convert the given GenericAttribute to an EScript object.
				virtual EScript::Object * convertToEScript(const Util::GenericAttribute * const attribute) = 0;

				//! Convert the given EScript object to a GenericAttribute
				virtual Util::GenericAttribute * convertFromEScript(const EScript::ObjPtr & object) = 0;
		};
		//! Default converter for reference counted objects
		template<class ObjType,class E_ObjType>
		class CountedRefAttrConverter : public AbstractGenericAttributeConverter{
			public:
				typedef typename Util::ReferenceAttribute<ObjType> attr_t;

			virtual ~CountedRefAttrConverter(){}
			E_ObjType * convertToEScript(const Util::GenericAttribute * const attribute) override {
				const attr_t * objContainer = dynamic_cast<const attr_t *> (attribute);
				return objContainer == nullptr ? nullptr : new E_ObjType(objContainer->get());
			}

			Util::GenericAttribute * convertFromEScript(const EScript::ObjPtr & object) override {
				const E_ObjType * vv = object.toType<const E_ObjType> ();
				return vv == nullptr ? nullptr : Util::GenericAttribute::createCountedReference(vv->ref().get());
			}			
		};

		/**
		 * Add a new converter to the chain of responsibility for converting GenericAttributes to EScript objects.
		 * The new converter automatically gets the highest priority.
		 *
		 * @param converter New converter object.
		 */
		EUTILAPI static void registerConverter(AbstractGenericAttributeConverter * converter);
	private:
		typedef std::list<AbstractGenericAttributeConverter *> converter_list_t;
		static converter_list_t converters;

		EUTILAPI static const converter_list_t & getConverters();
};
}

//! Macro to simplify bindings for getter/setter methods
#define ES_MGETSET(eclass, type, var)\
  ES_MFUN(typeObject,const eclass,"get" #var, 0, 0, EScript::create(thisObj->get##var()))\
  ES_MFUN(typeObject,eclass,"set" #var,1,1, (thisObj->set##var(parameter[0].to<type>(rt)),thisEObj) )\
	
#endif // E_UTILS_H
