/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012,2015 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "ELibUtil.h"
#include <sstream>

#include <Util/Encoding.h>
#include <Util/LibRegistry.h>
#include <Util/IO/FileName.h>
#include <Util/IO/FileUtils.h>
#include <Util/Serialization/Serialization.h>
#include <Util/StringUtils.h>
#include <Util/TypeConstant.h>
#include <Util/Utils.h>
#include <Util/LoadLibrary.h>
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include "E_MicroXMLReader.h"
#include "Graphics/E_Bitmap.h"
#include "Graphics/E_BitmapUtils.h"
#include "Graphics/E_Color.h"
#include "Graphics/E_PixelAccessor.h"
#include "E_DestructionMonitor.h"
#include "E_ProgressIndicator.h"
#include "E_Timer.h"
#include "E_FileName.h"
#include "E_UpdatableHeap.h"
#include "IO/E_FileLocator.h"
#include "IO/E_IOStream.h"
#include "IO/E_TemporaryDirectory.h"

// [Network support]
#include "Network/E_Network.h"

#include "UI/E_UI.h"

using namespace EScript;
using namespace Util;

static bool isBigEndian(){
	union {
		uint32_t i;
		uint8_t c[4];
	} bint = {0x01020304};
	return bint.c[0] == 1; 
}

template<typename T>
static double readNumber(const char* source){
	return static_cast<double>( *reinterpret_cast<const T*>(source) );
}
template<typename T>
static double readNumber_SwitchEndianness(const char* source){
	T number;
	char* target = reinterpret_cast<char*>(&number)+sizeof(T)-1;
	for(uint_fast8_t i=0;i<sizeof(T); ++i, ++source, --target)
		*target = *source;
	return number;
}
static double readNumber(const Util::TypeConstant type, const std::string& s, uint32_t index){
	if( index + Util::getNumBytes(type)>s.size() )
		throw std::out_of_range("readBinaryNumberFromString: invalid data index.");
	double result;
	switch(type){
		case Util::TypeConstant::UINT8:		result = readNumber<uint8_t>(s.data()+index);	break;
		case Util::TypeConstant::UINT16:	result = readNumber<uint16_t>(s.data()+index);	break;
		case Util::TypeConstant::UINT32:	result = readNumber<uint32_t>(s.data()+index);	break;
		case Util::TypeConstant::UINT64:	result = readNumber<uint64_t>(s.data()+index);	break;
		case Util::TypeConstant::INT8:		result = readNumber<int8_t>(s.data()+index);	break;
		case Util::TypeConstant::INT16:		result = readNumber<int16_t>(s.data()+index);	break;
		case Util::TypeConstant::INT32:		result = readNumber<int32_t>(s.data()+index);	break;
		case Util::TypeConstant::INT64:		result = readNumber<int64_t>(s.data()+index);	break;
		case Util::TypeConstant::FLOAT:		result = readNumber<float>(s.data()+index);		break;
		case Util::TypeConstant::DOUBLE:	result = readNumber<double>(s.data()+index);	break;
		default: throw std::out_of_range("readBinaryNumberFromString: invalid data type constant.");
	}
	return result;
}
static double readNumber_SwitchEndianness(const Util::TypeConstant type, const std::string& s, uint32_t index){
	if( index + Util::getNumBytes(type)>s.size() )
		throw std::out_of_range("readBinaryNumberFromString: invalid data index.");
	double result;
	switch(type){
		case Util::TypeConstant::UINT8:		result = readNumber_SwitchEndianness<uint8_t>(s.data()+index);	break;
		case Util::TypeConstant::UINT16:	result = readNumber_SwitchEndianness<uint16_t>(s.data()+index);	break;
		case Util::TypeConstant::UINT32:	result = readNumber_SwitchEndianness<uint32_t>(s.data()+index);	break;
		case Util::TypeConstant::UINT64:	result = readNumber_SwitchEndianness<uint64_t>(s.data()+index);	break;
		case Util::TypeConstant::INT8:		result = readNumber_SwitchEndianness<int8_t>(s.data()+index);	break;
		case Util::TypeConstant::INT16:		result = readNumber_SwitchEndianness<int16_t>(s.data()+index);	break;
		case Util::TypeConstant::INT32:		result = readNumber_SwitchEndianness<int32_t>(s.data()+index);	break;
		case Util::TypeConstant::INT64:		result = readNumber_SwitchEndianness<int64_t>(s.data()+index);	break;
		case Util::TypeConstant::FLOAT:		result = readNumber_SwitchEndianness<float>(s.data()+index);	break;
		case Util::TypeConstant::DOUBLE:	result = readNumber_SwitchEndianness<double>(s.data()+index);	break;
		default: throw std::out_of_range("readBinaryNumberFromString: invalid data type constant.");
	}
	return result;
}

template<typename T>
static void writeNumber(std::string& target, uint32_t index, double value){
	const T value2 = static_cast<T>(value);
	for(uint_fast8_t i=0;i<sizeof(T); ++i,++index)
		target[index] = reinterpret_cast<const char*>(&value2)[i];
}
template<typename T>
static void writeNumber_SwitchEndianness(std::string& target, uint32_t index, double value){
	const T value2 = static_cast<T>(value);
	index += sizeof(T)-1;
	for(uint_fast8_t i=0;i<sizeof(T); ++i,--index)
		target[index] = reinterpret_cast<const char*>(&value2)[i];
}
static std::string writeBinaryNumber(const Util::TypeConstant type, std::string s, uint32_t index, double value){
	if( index + Util::getNumBytes(type)>s.size() )
		throw std::out_of_range("writeBinaryNumber: invalid data index.");
	switch(type){
		case Util::TypeConstant::UINT8:		writeNumber<uint8_t>(s,index,value);	break;
		case Util::TypeConstant::UINT16:	writeNumber<uint16_t>(s,index,value);	break;
		case Util::TypeConstant::UINT32:	writeNumber<uint32_t>(s,index,value);	break;
		case Util::TypeConstant::UINT64:	writeNumber<uint64_t>(s,index,value);	break;
		case Util::TypeConstant::INT8:		writeNumber<int8_t>(s,index,value);		break;
		case Util::TypeConstant::INT16:		writeNumber<int16_t>(s,index,value);	break;
		case Util::TypeConstant::INT32:		writeNumber<int32_t>(s,index,value);	break;
		case Util::TypeConstant::INT64:		writeNumber<int64_t>(s,index,value);	break;
		case Util::TypeConstant::FLOAT:		writeNumber<float>(s,index,value);		break;
		case Util::TypeConstant::DOUBLE:	writeNumber<double>(s,index,value);		break;
		default: throw std::out_of_range("writeBinaryNumber: invalid data type constant.");
	}
	return std::move(s);
}
static std::string writeBinaryNumber_SwitchEndianness(const Util::TypeConstant type, std::string s, uint32_t index, double value){
	if( index + Util::getNumBytes(type)>s.size() )
		throw std::out_of_range("writeBinaryNumber: invalid data index.");
	switch(type){
		case Util::TypeConstant::UINT8:		writeNumber_SwitchEndianness<uint8_t>(s,index,value);	break;
		case Util::TypeConstant::UINT16:	writeNumber_SwitchEndianness<uint16_t>(s,index,value);	break;
		case Util::TypeConstant::UINT32:	writeNumber_SwitchEndianness<uint32_t>(s,index,value);	break;
		case Util::TypeConstant::UINT64:	writeNumber_SwitchEndianness<uint64_t>(s,index,value);	break;
		case Util::TypeConstant::INT8:		writeNumber_SwitchEndianness<int8_t>(s,index,value);	break;
		case Util::TypeConstant::INT16:		writeNumber_SwitchEndianness<int16_t>(s,index,value);	break;
		case Util::TypeConstant::INT32:		writeNumber_SwitchEndianness<int32_t>(s,index,value);	break;
		case Util::TypeConstant::INT64:		writeNumber_SwitchEndianness<int64_t>(s,index,value);	break;
		case Util::TypeConstant::FLOAT:		writeNumber_SwitchEndianness<float>(s,index,value);		break;
		case Util::TypeConstant::DOUBLE:	writeNumber_SwitchEndianness<double>(s,index,value);	break;
		default: throw std::out_of_range("writeBinaryNumber: invalid data type constant.");
	}
	return std::move(s);
}


namespace E_Util {
// ---------------------------------------------------------

void init(EScript::Namespace * globals) {
	auto lib=new Namespace;
	declareConstant(globals,"Util",lib);

	//---------------------------------------------------------------------------
	// IO

	//! [ESF] Bool Util.copyFile(String, String)
	ES_FUN(lib, "copyFile", 2, 2, Bool::create(FileUtils::copyFile(FileName(parameter[0].toString()), FileName(parameter[1].toString()))))

	//! [ESF] Bool Util.createDir(String)
	ES_FUN(lib, "createDir", 1, 1, Bool::create(FileUtils::createDir(FileName(parameter[0].toString()))))
	
	//! [ESF] Bool Util.removeFile(String, [recursive = false])
	ES_FUN(lib, "removeFile", 1, 2, Bool::create(FileUtils::remove(FileName(parameter[0].toString()), parameter[1].toBool(false))))

	declareConstant(lib,"DIR_FILES",Number::create(FileUtils::DIR_FILES));
	declareConstant(lib,"DIR_DIRECTORIES",Number::create(FileUtils::DIR_DIRECTORIES));
	declareConstant(lib,"DIR_RECURSIVE",Number::create(FileUtils::DIR_RECURSIVE));
	declareConstant(lib,"DIR_HIDDEN_FILES",Number::create(FileUtils::DIR_HIDDEN_FILES));

	//! [ESF] false|Array Util.dir(path, [flags=Util.DIR_FILES] );
	ES_FUNCTION(lib, "dir", 1, 2, {
		std::list<FileName> entries;
		bool b = FileUtils::dir(FileName::createDirName(parameter[0].toString()), entries, static_cast<uint8_t>(parameter[1].toInt(FileUtils::DIR_FILES)));
		if(!b) {
			return Bool::create(false);
		}
		Array * a = Array::create();
		for(const auto & entry: entries) {
			a->pushBack(String::create(entry.toString()));
		}
		return a;
	})

	//! [ESF] number Util.fileSize( path  );
	ES_FUN(lib,"fileSize",1,1,Number::create(FileUtils::fileSize(FileName(parameter[0].toString()))))

	//! [ESF] Void Util.flush(String fileSystem)
	ES_FUN(lib, "flush", 1, 1, (FileUtils::flush(FileName(parameter[0].toString())), EScript::create(nullptr)))

	//! [ESF] String generateNewRandFilename (dir, prefix, postfix, length)
	ES_FUN(lib, "generateNewRandFilename", 4, 4, new E_FileName(
			FileUtils::generateNewRandFilename(
				Util::FileName::createDirName(parameter[0].toString()),
				parameter[1].toString(),
				parameter[2].toString(),
				parameter[3].toInt()
			)
	))

	//! [ESF] bool Util.isFile( path  );
	ES_FUN(lib,"isFile",1,1,Bool::create(FileUtils::isFile(FileName(parameter[0].toString()))))

	//! [ESF] bool Util.isDir( path  );
	ES_FUN(lib,"isDir",1,1,Bool::create(FileUtils::isDir(FileName::createDirName(parameter[0].toString()))))

	//! [ESF] string|false Util.loadFile( path );
	ES_FUNCTION(lib, "loadFile", 1, 1, {
		const std::string fileContents = FileUtils::getFileContents(FileName(parameter[0].toString()));
		if(fileContents.empty()) {
			return Bool::create(false);
		}
		return String::create(fileContents);
	})


	//! [ESF] IOStream|void Util.openFile( path );
	ES_FUNCTION(lib, "openFile", 1, 1, {
		std::unique_ptr<std::iostream> stream( FileUtils::open(FileName(parameter[0].toString())));
		if(!stream)
			return nullptr;
		return new E_IOStream( std::move(stream) );
	})

	//! [ESF] bool Util.saveFile( path , string [,bool overwrite=true] );
	ES_FUNCTION(lib, "saveFile", 2, 3, {
		const std::string fileContents = parameter[1].toString();
		return Bool::create(FileUtils::saveFile(
				FileName(parameter[0].toString()),
				std::vector<uint8_t>(fileContents.begin(), fileContents.end()),
				parameter[2].toBool(true)));
	})

	// --------------------------------------------------------------------------
	// misc

	//! [ESF] void disableInfo()
	ES_FUN(lib,"disableInfo",0,0,(Util::disableInfo(),EScript::create(nullptr)))

	//! [ESF] void enableInfo()
	ES_FUN(lib,"enableInfo",0,0,(Util::enableInfo(),EScript::create(nullptr)))

	//! [ESF] void info( infoOutput* )
	ES_FUNCTION(lib,"info",0,-1,{
		for(size_t i=0;i<parameter.count();++i){
			Util::info<<parameter[i].toString();
		}
		return EScript::create(nullptr);
	})

	//! [ESF] Bitmap Util.loadBitmap(String)
	ES_FUN(lib, "loadBitmap", 1, 1,
		EScript::create(Util::Serialization::loadBitmap(Util::FileName(parameter[0].toString()))));
	//! [ESF] Void Util.saveBitmap(Bitmap, String)
	ES_FUN(lib, "saveBitmap", 2, 2,
		(Util::Serialization::saveBitmap(parameter[0].to<Util::Bitmap &>(rt), Util::FileName(parameter[1].toString())), EScript::create(nullptr)));


	//! [ESF]
	ES_FUN(lib,"toFormattedString",1,1,String::create(Util::StringUtils::toFormattedString(parameter[0].toFloat())))

	//! [ESF]
	ES_FUN(lib,"outputProcessMemory", 0, 0, (Util::Utils::outputProcessMemory(), EScript::create(nullptr)))

	//! [ESF] Number Util.getResidentSetMemorySize()
	ES_FUN(lib, "getResidentSetMemorySize", 0, 0, Number::create(Util::Utils::getResidentSetMemorySize()))

	//! [ESF] Number Util.getVirtualMemorySize()
	ES_FUN(lib, "getVirtualMemorySize", 0, 0, Number::create(Util::Utils::getVirtualMemorySize()))

	//! [ESF] Number Util.getAllocatedMemorySize()
	ES_FUN(lib, "getAllocatedMemorySize", 0, 0, Number::create(Util::Utils::getAllocatedMemorySize()))

	//! [ESF] Number Util.getCPUUsage(Number)
	ES_FUN(lib, "getCPUUsage", 1, 1, Number::create(Util::Utils::getCPUUsage(parameter[0].to<uint32_t>(rt))))

	//! [ESF] String Util.createTimeStamp()
	ES_FUN(lib, "createTimeStamp", 0, 0, Util::Utils::createTimeStamp())

	//! [ESF] void Util.sleep(ms)
	ES_FUN(lib, "sleep", 1, 1, (Util::Utils::sleep(parameter[0].to<uint32_t>(rt)),EScript::create(nullptr)))

	//! [ESF] string Util.encodeString_base64(string)
	ES_FUNCTION(lib, "encodeString_base64", 1, 1, {
		const std::string s = parameter[0].toString();
		return Util::encodeBase64(std::vector<uint8_t>(s.begin(), s.end()));
	})
	//! [ESF] string Util.decodeString_base64(string)
	ES_FUNCTION(lib, "decodeString_base64", 1, 1, {
		const std::vector<uint8_t> data = Util::decodeBase64( parameter[0].toString() );
		return std::string(data.begin(), data.end());
	})

	//! Map Util.getLibVersionStrings()
	ES_FUNCTION(lib, "getLibVersionStrings", 0, 0, {
		EScript::ERef<Map> m = new EScript::Map;
		for( const auto& p : Util::LibRegistry::getLibVersionStrings()){
			m->setValue( EScript::create(p.first), EScript::create(p.second) );
		}
		return m.detachAndDecrease();
	});
	
	//! [ESF] void Util.registerLibVersionString(lib,versionString)
	ES_FUN(lib, "registerLibVersionString", 2, 2, (Util::LibRegistry::registerLibVersionString(parameter[0].toString(),parameter[1].toString()),EScript::create(nullptr)))
	
	Namespace* E_TypeConstant = new Namespace;
	declareConstant( lib,			 "TypeConstant",		E_TypeConstant );
	declareConstant( E_TypeConstant, "UINT8",				static_cast<uint32_t>(Util::TypeConstant::UINT8) );
	declareConstant( E_TypeConstant, "UINT16",				static_cast<uint32_t>(Util::TypeConstant::UINT16) );
	declareConstant( E_TypeConstant, "UINT32",				static_cast<uint32_t>(Util::TypeConstant::UINT32) );
	declareConstant( E_TypeConstant, "UINT64",				static_cast<uint32_t>(Util::TypeConstant::UINT64) );
	declareConstant( E_TypeConstant, "INT8",				static_cast<uint32_t>(Util::TypeConstant::INT8) );
	declareConstant( E_TypeConstant, "INT16",				static_cast<uint32_t>(Util::TypeConstant::INT16) );
	declareConstant( E_TypeConstant, "INT32",				static_cast<uint32_t>(Util::TypeConstant::INT32) );
	declareConstant( E_TypeConstant, "INT64",				static_cast<uint32_t>(Util::TypeConstant::INT64) );
	declareConstant( E_TypeConstant, "FLOAT",				static_cast<uint32_t>(Util::TypeConstant::FLOAT) );
	declareConstant( E_TypeConstant, "DOUBLE",				static_cast<uint32_t>(Util::TypeConstant::DOUBLE) );

	//! [ESF] Number Util.getNumBytes(Util.TypeConstant)
	ES_FUN(lib, "getNumBytes", 1, 1, Number::create(Util::getNumBytes(static_cast<Util::TypeConstant>(parameter[0].to<uint32_t>(rt)))))

	// --------------------------------------------------------------------------

	//! Number Util.readBinaryNumberFromString(type,string,byteIndex)
	ES_FUN(lib, "readBinaryNumberFromString", 3, 3, 
				readNumber(	static_cast<Util::TypeConstant>(parameter[0].toUInt()),assertType<EScript::String>(rt,parameter[1])->getString(),parameter[2].toUInt()) )
	
	if(isBigEndian()){
		//! Number Util.readBinaryNumberFromString_LittleEndian(type,string,byteIndex)
		ES_FUN(lib, "readBinaryNumberFromString_LittleEndian", 3, 3, 
					readNumber_SwitchEndianness(	static_cast<Util::TypeConstant>(parameter[0].toUInt()),assertType<EScript::String>(rt,parameter[1])->getString(),parameter[2].toUInt()) )

		//! Number Util.readBinaryNumberFromString_BigEndian(type,string,byteIndex)
		ES_FUN(lib, "readBinaryNumberFromString_BigEndian", 3, 3, 
					readNumber(		static_cast<Util::TypeConstant>(parameter[0].toUInt()),assertType<EScript::String>(rt,parameter[1])->getString(),parameter[2].toUInt()) )
	}else{
		//! Number Util.readBinaryNumberFromString_LittleEndian(type,string,byteIndex)
		ES_FUN(lib, "readBinaryNumberFromString_LittleEndian", 3, 3, 
					readNumber(		static_cast<Util::TypeConstant>(parameter[0].toUInt()),assertType<EScript::String>(rt,parameter[1])->getString(),parameter[2].toUInt()) )

		//! Number Util.readBinaryNumberFromString_BigEndian(type,string,byteIndex)
		ES_FUN(lib, "readBinaryNumberFromString_BigEndian", 3, 3, 
					readNumber_SwitchEndianness(	static_cast<Util::TypeConstant>(parameter[0].toUInt()),assertType<EScript::String>(rt,parameter[1])->getString(),parameter[2].toUInt()) )
	}
	//! Number Util.writeBinaryNumberToString(type,string,byteIndex, value)
	ES_FUN(lib, "writeBinaryNumberToString", 4, 4,
				writeBinaryNumber(	static_cast<Util::TypeConstant>(parameter[0].toUInt()),assertType<EScript::String>(rt,parameter[1])->getString(),parameter[2].toUInt(),parameter[3].toDouble()))
	
	if(isBigEndian()){
		//! String Util.writeBinaryNumberToString_LittleEndian(type,string,byteIndex, value)
		ES_FUN(lib, "writeBinaryNumberToString_LittleEndian", 4, 4,
					std::move(writeBinaryNumber_SwitchEndianness(	static_cast<Util::TypeConstant>(parameter[0].toUInt()),assertType<EScript::String>(rt,parameter[1])->getString(),parameter[2].toUInt(),parameter[3].toDouble()) ))

		//! String Util.writeBinaryNumberToString_BigEndian(type,string,byteIndex, value)
		ES_FUN(lib, "writeBinaryNumberToString_BigEndian", 4, 4,
					std::move(writeBinaryNumber(		static_cast<Util::TypeConstant>(parameter[0].toUInt()),assertType<EScript::String>(rt,parameter[1])->getString(),parameter[2].toUInt(),parameter[3].toDouble()) ))
	}else{
		//! String Util.writeBinaryNumberToString_LittleEndian(type,string,byteIndex, value)
		ES_FUN(lib, "writeBinaryNumberToString_LittleEndian", 4, 4,
					std::move(writeBinaryNumber(		static_cast<Util::TypeConstant>(parameter[0].toUInt()),assertType<EScript::String>(rt,parameter[1])->getString(),parameter[2].toUInt(),parameter[3].toDouble()) ))

		//! String Util.writeBinaryNumberToString_BigEndian(type,string,byteIndex, value)
		ES_FUN(lib, "writeBinaryNumberToString_BigEndian", 4, 4,
					std::move(writeBinaryNumber_SwitchEndianness(	static_cast<Util::TypeConstant>(parameter[0].toUInt()),assertType<EScript::String>(rt,parameter[1])->getString(),parameter[2].toUInt(),parameter[3].toDouble()) ))
	}
	
	//! Bool Util.loadELibrary(filename, [Namespace])
	ES_FUNCTION(lib, "loadELibrary", 1, 2, {
		auto libraryId = loadLibrary(parameter[0].toString());
		if(libraryId.getValue() != 0) {
			void* fnHandle = loadFunction(libraryId, "initLibrary");
			if(fnHandle) {
				auto * ns = parameter[1].toType<EScript::Namespace>();
				reinterpret_cast<libInitFunction*>(fnHandle)(ns ? ns : rt.getGlobals());
				return EScript::create(true);
			}
		}
		return EScript::create(false);
	})
	
	
	/* Shouldn't be used!
	//! void Util.unloadELibrary(filename)
	ES_FUNCTION(lib, "unloadELibrary", 1, 1, {
		Util::StringIdentifier libraryId(parameter[0].toString());
		unloadLibrary(libraryId);
		return EScript::create(nullptr);
	})*/
	// --------------------------------------------------------------------------
	// Objects

	E_DestructionMonitor::init(*lib);
	E_FileLocator::init(*lib);
	E_IOStream::init(*lib);
	E_MicroXMLReader::init(*lib);
	E_Bitmap::init(*lib);
	E_BitmapUtils::init(*lib);
	E_FileName::init(*lib);
	E_PixelAccessor::init(*lib);
	E_Color4ub::init(*lib);
	E_Color4f::init(*lib);
	E_ProgressIndicator::init(*lib);
	E_Timer::init(*lib);
	E_TemporaryDirectory::init(*lib);
	E_UpdatableHeap::init(*lib);

	Network::E_Network::init(*lib);

	E_UI::init(lib);
}

}
