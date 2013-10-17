/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Utils.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <Util/AttributeProvider.h>
#include <Util/GenericAttribute.h>
#include <Util/Macros.h>
#include <Util/StringIdentifier.h>

#include <cstddef>
#include <map>
#include <cstdint>
#include <string>
#include <utility>

using namespace EScript;
using namespace Util;

namespace E_Util {

E_Utils::converter_list_t E_Utils::converters;

void E_Utils::registerConverter(AbstractGenericAttributeConverter * converter) {
	// Make sure that the standard converter is inserted first.
	getConverters();

	if (converter != nullptr) {
		// Append to the front to assign highest priority.
		converters.push_front(converter);
	}
}

/*!	[static] GenericAttribute ---> EScript::Object	*/
EScript::Object * E_Utils::convertGenericAttributeToEScriptObject(const GenericAttribute * ga, bool warn /*=true*/) {
	if(ga == nullptr) {
		return EScript::create(nullptr);
	}

	for(const auto & converter : getConverters()) {
		EScript::Object * result = converter->convertToEScript(ga);
		if(result != nullptr) {
			return result;
		}
	}
	if(warn) {
		WARN(std::string("Unable to convert GenericAttribute to EScript object."));
	}
	return EScript::create(nullptr);
}

/*!	[static] GenericAttributeList ---> EScript::Array	*/
static EScript::Array * genericAttributeList2EScriptArray(const Util::GenericAttributeList * gal) {
	EScript::Array * esa = EScript::Array::create();
	if(!gal) {
		return esa;
	}

	for(const auto & listEntry : *gal) {
		esa->pushBack(E_Utils::convertGenericAttributeToEScriptObject(listEntry.get()));
	}
	return esa;
}

/*!	[static] GenericAttributeMap ---> EScript::Map	*/
static EScript::Map * genericAttributeMap2EScriptMap(const Util::GenericAttributeMap * gam) {
	EScript::Map * esm = EScript::Map::create();
	if(!gam) {
		return esm;
	}

	for(const auto & mapEntry : *gam) {
		const std::string key = mapEntry.first.toString();
		// Do not show warnings for keys that begin and end with '_'
		bool warn = !(key.front() == '_' && key.back() == '_');
		esm->setValue(String::create(key), E_Utils::convertGenericAttributeToEScriptObject(mapEntry.second.get(), warn));
	}
	return esm;
}

const E_Utils::converter_list_t & E_Utils::getConverters() {
	class GenericAttributeConverter : public AbstractGenericAttributeConverter {
		public:
			virtual ~GenericAttributeConverter() {
			}

			Object * convertToEScript(const Util::GenericAttribute * const attribute) override {
				if(attribute == nullptr)
					return nullptr;
				
				// is container for EScript objects?
				const auto objContainer = attribute->toType<const Util::ReferenceAttribute<Object>>(); // this is evil! Mixing of EScript::ObjRef and Util::Reference!
				if (objContainer) {
					return objContainer->get();
				}
				const auto extObjContainer = attribute->toType<const Util::ReferenceAttribute<ExtObject>>(); // this is evil! Mixing of EScript::ObjRef and Util::Reference!
				if (extObjContainer) {
					return extObjContainer->get();
				}

				// is a boolean?
				if(attribute->isA<Util::BoolAttribute>()) {
					return Bool::create(attribute->toBool());
				}

				// is a map?
				const auto map = attribute->toType<const Util::GenericAttributeMap>();
				if(map != nullptr) {
					return genericAttributeMap2EScriptMap(map);
				}

				// is a list?
				const auto list = attribute->toType<const Util::GenericAttributeList>();
				if(list != nullptr) {
					return genericAttributeList2EScriptArray(list);
				}

				// is a number?
				if(attribute->isA<Util::GenericNumberAttribute>()) {
					return Number::create(attribute->toDouble());
				}

				// is a string?
				if(attribute->isA<Util::GenericStringAttribute>()) {
					return String::create(attribute->toString());
				}

				return nullptr;
			}

			Util::GenericAttribute * convertFromEScript(const EScript::ObjPtr & object) override {
				// is a Number?
				EScript::Number * n = dynamic_cast<EScript::Number *> (object.get());
				if (n != nullptr) {
					return GenericAttribute::createNumber(n->getValue());
				}

				// is a Bool?
				EScript::Bool * b = dynamic_cast<EScript::Bool *> (object.get());
				if (b != nullptr) {
					return GenericAttribute::createBool(b->toBool());
				}

				// is a String?
				EScript::String * s = dynamic_cast<EScript::String *> (object.get());
				if (s != nullptr) {
					return GenericAttribute::createString(s->getString());
				}

				// is an Array?
				EScript::Array * a = dynamic_cast<EScript::Array *> (object.get());
				if (a != nullptr) {
					auto gl = new Util::GenericAttributeList;
					for (ERef<EScript::Iterator> i = a->getIterator(); !i->end(); i->next()) {
						ObjRef value = i->value();
						gl->push_back(convertEScriptObjectToGenericAttribute(value));
					}
					return gl;
				}
				// is a Map?
				EScript::Map * m = dynamic_cast<EScript::Map *> (object.get());
				if (m != nullptr) {
					auto gm = new Util::GenericAttributeMap;
					for (ERef<EScript::Iterator> i = m->getIterator(); !i->end(); i->next()) {
						ObjRef key = i->key();
						ObjRef value = i->value();
						gm->setValue(key->toString(), convertEScriptObjectToGenericAttribute(value));
					}
					return gm;
				}

				return nullptr;
			}
	};

	if (converters.empty()) {
		converters.push_back(new GenericAttributeConverter);
	}
	return converters;
}

/*!	[static] EScript::Object ---> GenericAttribute	*/
Util::GenericAttribute * E_Utils::convertEScriptObjectToGenericAttribute(EScript::ObjPtr obj) {
	if(obj.isNull() || dynamic_cast<const EScript::Void *>(obj.get()) != nullptr) {
		return nullptr;
	}

	for(const auto & converter : getConverters()) {
		Util::GenericAttribute * result = converter->convertFromEScript(obj);
		if(result != nullptr) {
			return result;
		}
	}

	WARN("Unable to convert EScript object to GenericAttribute.");
	return nullptr;
}

// ------------------------------------------------------



namespace Policies{
/*! EScriptAttributeWrapper ---|> Util::GenericAttribute
	An EScriptAttributeWrapper internally contains an ExtObject which can hold arbitrary EScript attributes.
	\note For this purpose, a Util::ReferenceAttribute<EScript::ExtObject> can NOT be used, as when an an object
		of this type is cloned, the same object would be referenced twice. The desired behavior is, that when an EScriptAttributeWrapper
		is cloned, so is internal ExtObject.	*/
class EScriptAttributeWrapper:public Util::WrapperAttribute<EScript::AttributeContainer>{
	public:
		typedef EScriptAttributeWrapper attr_t;
				
		EScriptAttributeWrapper() = default;
		EScriptAttributeWrapper(const EScriptAttributeWrapper &) = default;
		virtual ~EScriptAttributeWrapper() = default;

		//! ---|> GenericAttribute
		attr_t * clone()const override 	{	return new attr_t(*this); }
};


EScript::AttributeContainer * StoreAttrsInAttributeProvider::_getAttributeContainer(Util::AttributeProvider * attrProvider,bool create){
	static const Util::StringIdentifier containerId( "$cis$_EScript_"); // private attribute
	EScriptAttributeWrapper * attributeContainerWrapper = dynamic_cast<EScriptAttributeWrapper * >(attrProvider->getAttribute(containerId));
	if(attributeContainerWrapper==nullptr && create){
		attributeContainerWrapper = new EScriptAttributeWrapper();
		attrProvider->setAttribute(containerId,attributeContainerWrapper);
	}
	return attributeContainerWrapper != nullptr ? &attributeContainerWrapper->ref() : nullptr;
}

}

}
