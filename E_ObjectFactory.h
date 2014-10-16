/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_UTIL_E_OBJECTFACTORY_H_
#define E_UTIL_E_OBJECTFACTORY_H_

#include <Util/StringIdentifier.h>
#include <Util/Factory/WrapperFactory.h>
#include <cstdint>
#include <functional>
#include <iostream>

namespace E_Util {

namespace FactoryFallbackPolicies {
/**
 * @brief Fallback policy used for E_ObjectFactory.
 * @see Like Util::FallbackPolicies::DefaultCreatorFallback, but with meaningfull warning message.
 */
template <class ObjectType, typename IdentifierType>
class DefaultCreatorFallbackWithClassId {
	private:
		IdentifierType defaultIdentifier;
		std::ostream & output;
	public:
		DefaultCreatorFallbackWithClassId(const IdentifierType & id, std::ostream & outputStream) :
			defaultIdentifier(id), output(outputStream) {
		}

		//! Type of a function object that encapsulates a call to the factory that uses this fallback.
		typedef std::function<ObjectType (const IdentifierType &)> FactoryCall;

		/**
		 * Use the given function object calling the create function of the factory.
		 * Give the default identifier to the create function to create a default object.
		 */
		ObjectType onUnknownType(FactoryCall functor, const IdentifierType & id) {
			output << "Warning: Using standard object factory for \"" << id.toString() << "\"." << std::endl;
			return functor(defaultIdentifier);
		}
};

}

/**
 * Class for an E_Object factory system, which creates E_Objects of an appropriate type for a given C++ Object.
 * A static object of this class should be stored inside the E_ObjectBaseType.
 * @note Subtypes of E_ObjectBaseType need to have a constructor taking an subtype of ObjectBaseType as parameter.
 * @note The following functions have to be implemented for ObjectBaseType and all subtypes, and have to return the same value:
 * - @codestatic Util::StringIdentifier getClassId()@endcode
 * - @codevirtual Util::StringIdentifier getTypeId() const@endcode
 * @see PROVIDES_TYPE_NAME
 */
template<class ObjectBaseType, class E_ObjectBaseType>
class E_ObjectFactory: public Util::WrapperFactory<
								ObjectBaseType *,
								E_ObjectBaseType *,
								Util::StringIdentifier,
								std::function<E_ObjectBaseType * (ObjectBaseType *)>,
								FactoryFallbackPolicies::DefaultCreatorFallbackWithClassId> {
	public:
		E_ObjectFactory() :
			Util::WrapperFactory<
				ObjectBaseType *,
				E_ObjectBaseType *,
				Util::StringIdentifier,
				std::function<E_ObjectBaseType * (ObjectBaseType *)>,
				FactoryFallbackPolicies::DefaultCreatorFallbackWithClassId>(
					FactoryFallbackPolicies::DefaultCreatorFallbackWithClassId<E_ObjectBaseType *, Util::StringIdentifier>(ObjectBaseType::getClassId(), std::cerr)) {
		}
};

}

#endif /* E_UTIL_E_OBJECTFACTORY_H_ */
