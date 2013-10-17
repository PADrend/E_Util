/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_DestructionMonitor.h"

#include <EScript/EScript.h>

using namespace EScript;

namespace E_Util {

//! (static)
Type * E_DestructionMonitor::getTypeObject(){
	// [E_DestructionMonitor] ---|> [Object]
	static auto typeObject = new EScript::Type(Object::getTypeObject());
	return typeObject;
}

//! initMembers
void E_DestructionMonitor::init(EScript::Namespace & lib) {
	// E_DestructionMonitor ---|> [Object]
	Type * typeObject=getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESMF] DestructionMonitor new DestructionMonitor( 0 )
	ES_CTOR(typeObject,0,0,new E_DestructionMonitor())

	//! [ESMF] DestructionMarker DestructionMonitor.createMarker( [String name] )
	ES_MFUN(typeObject,E_DestructionMonitor,"createMarker",0,1,thisObj->createMarker(parameter[0].toString()))

	//! [ESMF] Array DestructionMonitor.extractMarkers()
	ES_MFUNCTION(typeObject, E_DestructionMonitor, "extractMarkers", 0, 0, {
		ERef<Array> a(Array::create());
		std::vector<std::string> results;
		thisObj->extractMarkers(results);
		for(const auto & marker : results) {
			a->pushBack(String::create(marker));
		}
		return a.detachAndDecrease();
	})

	//! [ESMF] Array DestructionMonitor.getPendingMarkersNames()
	ES_MFUNCTION(typeObject, E_DestructionMonitor, "getPendingMarkersNames", 0, 0, {
		ERef<Array> a(Array::create());
		for(const auto & marker : thisObj->getPendingMarkers()) {
			a->pushBack(String::create(marker->getName()));
		}
		return a.detachAndDecrease();
	})

	//! [ESMF] Number DestructionMonitor.getPendingMarkersCount()
	ES_MFUN(typeObject,const E_DestructionMonitor,"getPendingMarkersCount",0,0,Number::create(thisObj->getPendingMarkersCount()))

	//! [ESMF] Bool DestructionMonitor.markersAvailable()
	ES_MFUN(typeObject,const E_DestructionMonitor,"markersAvailable",0,0,Bool::create(thisObj->markersAvailable()))

}

E_DestructionMonitor::DestructionMarker * E_DestructionMonitor::createMarker(const std::string & markerName){
	auto m = new DestructionMarker(this,markerName);
	pendingMarkers.insert(m);
	return m;
}

void E_DestructionMonitor::extractMarkers(std::vector<std::string> & result){
	result.clear();
	releasedMarkers.swap(result);
}

void E_DestructionMonitor::releaseMarker(DestructionMarker * marker){
	releasedMarkers.push_back(marker->getName());
	pendingMarkers.erase( marker );
}

}
