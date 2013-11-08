/*
	This file is part of the E_Util library.
	Copyright (C) 2009-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2009-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2009-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "ELibUtil.h"
#include <sstream>
#include <EScript/Utils/DeprecatedMacros.h>
#include <Util/Encoding.h>
#include <Util/IO/FileName.h>
#include <Util/IO/FileUtils.h>
#include <Util/Serialization/Serialization.h>
#include <Util/StringUtils.h>
#include <Util/Utils.h>

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
#include "IO/E_TemporaryDirectory.h"

// [Network support]
#include "Network/E_Network.h"

#include "UI/E_UI.h"

using namespace EScript;
using namespace Util;

namespace E_Util {
// ---------------------------------------------------------

void init(EScript::Namespace * globals) {
	auto lib=new Namespace();
	declareConstant(globals,"Util",lib);

	//---------------------------------------------------------------------------
	// IO

	//! [ESF] Bool Util.copyFile(String, String)
	ES_FUN(lib, "copyFile", 2, 2, Bool::create(FileUtils::copyFile(FileName(parameter[0].toString()), FileName(parameter[1].toString()))))

	//! [ESF] Bool Util.createDir(String)
	ES_FUN(lib, "createDir", 1, 1, Bool::create(FileUtils::createDir(FileName(parameter[0].toString()))))

	declareConstant(lib,"DIR_FILES",Number::create(FileUtils::DIR_FILES));
	declareConstant(lib,"DIR_DIRECTORIES",Number::create(FileUtils::DIR_DIRECTORIES));
	declareConstant(lib,"DIR_RECURSIVE",Number::create(FileUtils::DIR_RECURSIVE));
	declareConstant(lib,"DIR_HIDDEN_FILES",Number::create(FileUtils::DIR_HIDDEN_FILES));

	//! [ESF] false|Array Util.dir(path, [flags=Util.DIR_FILES] );
	ES_FUNCTION2(lib, "dir", 1, 2, {
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
	ES_FUNCTION2(lib, "loadFile", 1, 1, {
		const std::string fileContents = FileUtils::getFileContents(FileName(parameter[0].toString()));
		if(fileContents.empty()) {
			return Bool::create(false);
		}
		return String::create(fileContents);
	})

	//! [ESF] bool Util.saveFile( path , string [,bool overwrite=true] );
	ES_FUNCTION2(lib, "saveFile", 2, 3, {
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
	ES_FUNCTION2(lib,"info",0,-1,{
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
	ES_FUNCTION2(lib, "encodeString_base64", 1, 1, {
		const std::string s = parameter[0].toString();
		return Util::encodeBase64(std::vector<uint8_t>(s.begin(), s.end()));
	})
	//! [ESF] string Util.decodeString_base64(string)
	ES_FUNCTION2(lib, "decodeString_base64", 1, 1, {
		const std::vector<uint8_t> data = Util::decodeBase64( parameter[0].toString() );
		return std::string(data.begin(), data.end());
	})

	// --------------------------------------------------------------------------
	// Objects

	E_DestructionMonitor::init(*lib);
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
