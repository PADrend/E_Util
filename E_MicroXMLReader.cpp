/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_MicroXMLReader.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Util/IO/FileName.h>
#include <Util/IO/FileUtils.h>
#include <Util/MicroXML.h>
#include <functional>

using namespace EScript;

namespace E_Util {

static ExtObject * visitorCreateETag(const std::string & tagName) {
	auto o = new ExtObject;

	static const EScript::StringId nameId("name");
	o->setAttribute(nameId, String::create(tagName));

	auto m = new EScript::Map;

	static const EScript::StringId attributesId("attributes");
	o->setAttribute(attributesId, m);
	return o;
}
static ExtObject * visitorCreateETag(const std::string & tagName, const Util::MicroXML::attributes_t & attributes) {
	auto o = new ExtObject;

	static const EScript::StringId nameId("name");
	o->setAttribute(nameId, String::create(tagName));

	auto m = new EScript::Map;

	static const EScript::StringId attributesId("attributes");
	o->setAttribute(attributesId, m);
	for(const auto & attrib : attributes) {
		m->setValue(String::create(attrib.first), String::create(attrib.second));
	}
	return o;
}

static bool visitorEnter(EScript::Runtime & rt, E_MicroXMLReader & reader, const std::string & tagName, const Util::MicroXML::attributes_t & attributes) {
	static const EScript::StringId attrName("enter");
	ObjRef resultObj = callMemberFunction(rt, &reader, attrName, ParameterValues(visitorCreateETag(tagName, attributes)));
	return resultObj.toBool();
}

static bool visitorLeave(EScript::Runtime & rt, E_MicroXMLReader & reader, const std::string & tagName) {
	static const EScript::StringId attrName("leave");
	ObjRef resultObj = callMemberFunction(rt, &reader, attrName, ParameterValues(visitorCreateETag((tagName))));
	return resultObj.toBool();
}

static bool visitorData(EScript::Runtime & rt, E_MicroXMLReader & reader, const std::string & tagName, const std::string & data) {
	static const EScript::StringId attrName("data");
	ObjRef resultObj = callMemberFunction(rt, &reader, attrName, ParameterValues(visitorCreateETag(tagName), String::create(data)));
	return resultObj.toBool();
}

static bool visitorParse(EScript::Runtime & rt, E_MicroXMLReader & reader, const std::string & filename){
	const Util::FileName fileName(filename);

	auto in = Util::FileUtils::openForReading(fileName);
	if(!in) {
		return false;
	}

	using namespace std::placeholders;
	Util::MicroXML::Reader::traverse(*(in.get()),
									 std::bind(visitorEnter, std::ref(rt), std::ref(reader), _1, _2),
									 std::bind(visitorLeave, std::ref(rt), std::ref(reader), _1),
									 std::bind(visitorData, std::ref(rt), std::ref(reader), _1, _2));

	return true;
}

//! (static)
EScript::Type * E_MicroXMLReader::getTypeObject() {
	// E_MicroXMLReader ---|> ExtObject
	static EScript::ERef<EScript::Type> typeObject = new EScript::Type(EScript::ExtObject::getTypeObject());
	return typeObject.get();
}

//! [E_MicroXMLReader] initMembers
void E_MicroXMLReader::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	//! [ESF] MicroXMLReader new Util.MicroXMLReader()
	ES_CTOR(typeObject,0,0,new E_MicroXMLReader())

	//! [ESMF] bool Util.MicroXMLReader.data(tag,data)
	ES_FUN(typeObject,"data",2,2,true)

	//! [ESMF] bool Util.MicroXMLReader.enter(tag)
	ES_FUN(typeObject,"enter",1,1,true)

	//! [ESMF] bool Util.MicroXMLReader.leave(tag)
	ES_FUN(typeObject,"leave",1,1,true)

	//! [ESMF] bool  Util.MicroXMLReader.parse(Filename)
	ES_MFUN(typeObject,E_MicroXMLReader,"parse",1,1,
			visitorParse(rt, *thisObj, parameter[0].toString()))

}

E_MicroXMLReader::E_MicroXMLReader(EScript::Type * type) :
	ExtObject(type?type:getTypeObject()){
}

E_MicroXMLReader::~E_MicroXMLReader() = default;

}
