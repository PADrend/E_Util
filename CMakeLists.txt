#
# This file is part of the E_Util library.
# Copyright (C) 2009-2013 Benjamin Eikel <benjamin@eikel.org>
#	Copyright (C) 2015-2019 Sascha Brandt <sascha@brandt.graphics>
#
# This library is subject to the terms of the Mozilla Public License, v. 2.0.
# You should have received a copy of the MPL along with this library; see the 
# file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.1.0)
project(E_Util VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set up install directories
include(GNUInstallDirs)
set(CMAKE_INSTALL_CMAKECONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/E_Util)

add_library(E_Util
	E_DestructionMonitor.cpp
	E_FileName.cpp
	E_MicroXMLReader.cpp
	E_ProgressIndicator.cpp
	E_Timer.cpp
	E_UpdatableHeap.cpp
	E_Utils.cpp
	ELibUtil.cpp
	Graphics/E_Bitmap.cpp
	Graphics/E_BitmapUtils.cpp
	Graphics/E_Color.cpp
	Graphics/E_PixelAccessor.cpp
	IO/E_FileLocator.cpp
	IO/E_IOStream.cpp
	IO/E_TemporaryDirectory.cpp
	Network/E_ClockSynchronizer.cpp
	Network/E_DataBroadcaster.cpp
	Network/E_DataConnection.cpp
	Network/E_Network.cpp
	Network/E_NetworkTCP.cpp
	Network/E_NetworkUDP.cpp
	UI/E_Event.cpp
	UI/E_EventContext.cpp
	UI/E_EventQueue.cpp
	UI/E_SplashScreen.cpp
	UI/E_UI.cpp
	UI/E_Window.cpp
)

# Dependency to EScript
if(NOT TARGET EScript)
	find_package(EScript 0.6.7 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_Util LINK_PUBLIC EScript)

# Dependency to Util
if(NOT TARGET Util)
	find_package(Util 0.3.0 REQUIRED NO_MODULE)
endif()
target_link_libraries(E_Util LINK_PUBLIC Util)

# Set version of library
set_target_properties(E_Util PROPERTIES VERSION ${E_Util_VERSION}
                                        SOVERSION ${E_Util_VERSION_MAJOR})

# Install the header files
file(GLOB E_UTIL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Graphics/*.h")
install(FILES ${E_UTIL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_Util/Graphics COMPONENT headers)
file(GLOB E_UTIL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/IO/*.h")
install(FILES ${E_UTIL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_Util/IO COMPONENT headers)
file(GLOB E_UTIL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Network/*.h")
install(FILES ${E_UTIL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_Util/Network COMPONENT headers)
file(GLOB E_UTIL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/UI/*.h")
install(FILES ${E_UTIL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_Util/UI COMPONENT headers)
file(GLOB E_UTIL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${E_UTIL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/E_Util COMPONENT headers)

# Install the library
install(TARGETS E_Util EXPORT LibraryExport
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtimelibraries
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT runtimelibraries
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT developmentlibraries
)

# Set include directories for users of this library
target_include_directories(E_Util
                           INTERFACE
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
                           "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")

# Library export
install(EXPORT LibraryExport DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR} FILE E_UtilTargets.cmake COMPONENT developmentlibraries)

# Create the configuration files
include(CMakePackageConfigHelpers)
configure_package_config_file(E_UtilConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/E_UtilConfig.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR}
                              PATH_VARS CMAKE_INSTALL_CMAKECONFIGDIR
                              NO_SET_AND_CHECK_MACRO
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/E_UtilConfigVersion.cmake
                                 VERSION ${E_Util_VERSION}
                                 COMPATIBILITY SameMajorVersion)

# Install the configuration files
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/E_UtilConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/E_UtilConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_CMAKECONFIGDIR} COMPONENT developmentlibraries)

# Packaging
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "libutil${E_Util_VERSION_MAJOR}-escript")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "E_Util library")
set(CPACK_PACKAGE_VENDOR "Benjamin Eikel; Claudius Jaehn; Ralf Petring; Sascha Brandt")
set(CPACK_PACKAGE_CONTACT "Benjamin Eikel <benjamin@eikel.org>")
set(CPACK_PACKAGE_VERSION_MAJOR ${E_Util_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${E_Util_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${E_Util_VERSION_PATCH})
set(CPACK_PACKAGE_FILE_NAME "libE_Util")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_STRIP_FILES ON)

include(CPack)
