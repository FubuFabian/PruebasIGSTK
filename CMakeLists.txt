CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

PROJECT(HolaMundoQT)

FIND_PACKAGE(IGSTK)
IF(IGSTK_FOUND)
	INCLUDE(${IGSTK_USE_FILE})
ELSE(IGSTK_FOUND)
	MESSAGE(FATAL_ERROR
		"IGSTK NOT FOUND. PLEASE SET IGSTK_DIR.")
ENDIF(IGSTK_FOUND)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE( ${QT_USE_FILE} )

# support for out-of-source build
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR} #this is where ui_ImageViewerUI.h is generated
  ${CMAKE_CURRENT_SOURCE_DIR}
)

#HolaMundoQt.cpp PolarisTrackerTest.cpp
SET(AppSrcs PolarisTracker.cpp HolaMundoQT.cpp HolaMundoQTGUI.cpp igstkNeedleObject.cpp igstkNeedleObjectRepresentation.cpp) 
     
SET(AppHeaders PolarisTracker.h HolaMundoQTGUI.h igstkNeedleObject.h igstkNeedleObjectRepresentation.h)

SET(AppUI HolaMundoQTGUI.ui)

# for generate qt aditional files 
QT4_WRAP_UI(UISrcs ${AppUI})
QT4_WRAP_CPP(MOCSrcs ${AppHeaders} )

# Packaging source code in same files 
SOURCE_GROUP("Resources" FILES
  ${AppUI}
)
 
SOURCE_GROUP("Generated" FILES
  ${UISrcs}
  ${MOCSrcs}
)


ADD_EXECUTABLE(HolaMundoQT ${AppSrcs} ${AppHeaders} ${UISrcs} ${MOCSrcs})

TARGET_LINK_LIBRARIES(HolaMundoQT QVTK IGSTK)