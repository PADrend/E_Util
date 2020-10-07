/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __EDestructionMonitor_H
#define __EDestructionMonitor_H

#include <EScript/Objects/Object.h>
#include <string>
#include <vector>
#include <set>

namespace E_Util {


/**
 * Class for managing "destruction markers" that can be attached to an Objects to
 * detect if the Object is ever destroyed.
 *
 *  E_DestructionMonitor ---|> [EScript::Object]
 *
 * Usage example (EScript):
 * \code
 * GLOBALS.myDestructionMonitor = new Util.DestructionMonitor();
 *
 * {
 *		var someObject = new ExtObject();
 * 		// attach marker to the object whose destruction should be noticed.
 *		someObject.__destructionMarker := myDestructionMonitor.createMarker("someObject is no more...");
 *
 *		print_r( myDestructionMonitor.extractMarkers() ); // ---> []  (someObject still exists)
 * } // someObject was stored in a local variable. It should be released when leaving the block.
 *
 * print_r( myDestructionMonitor.extractMarkers() ); // ---> ["someObject is no more..."]
 * print_r( myDestructionMonitor.extractMarkers() ); // ---> []  (every marker is only reported once.)
 * \endcode
 */
class E_DestructionMonitor : public EScript::Object {
		ES_PROVIDES_TYPE_NAME(DestructionMonitor)
	public:
		EUTILAPI static EScript::Type * getTypeObject();
		EUTILAPI static void init(EScript::Namespace & lib);

		E_DestructionMonitor() : EScript::Object(getTypeObject()) {}
		virtual ~E_DestructionMonitor()	{}

		//! DestructionMarker---|>
		class DestructionMarker : public EScript::Object {
				ES_PROVIDES_TYPE_NAME(DestructionMarker)
				EScript::ERef<E_DestructionMonitor> monitor;
				std::string name;

				DestructionMarker(E_DestructionMonitor * _monitor,const std::string & _name) :
					EScript::Object(),monitor(_monitor),name(_name){}

				friend class E_DestructionMonitor;
			public:
				virtual ~DestructionMarker()		{	monitor->releaseMarker(this);	}
				const std::string & getName()const	{	return name;	}
		};
		friend class DestructionMarker;

		EUTILAPI DestructionMarker * createMarker(const std::string & markerName="");
		EUTILAPI void extractMarkers(std::vector<std::string> & result);

		const std::set<DestructionMarker*> & getPendingMarkers()const		{	return pendingMarkers;	}
		size_t getPendingMarkersCount()const								{	return pendingMarkers.size();	}
		bool markersAvailable()const										{	return	!releasedMarkers.empty();	}

	private:
		EUTILAPI void releaseMarker(DestructionMarker * marker);

		std::vector<std::string> releasedMarkers;
		std::set<DestructionMarker*> pendingMarkers;
};
}
#endif // __EDestructionMonitor_H
