CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT( Roi3DF )

SET( BUILD_EXAMPLES ON CACHE BOOL "Build example projects. For this project several subcategories exist.")
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

INCLUDE(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP(TARGETS)

INCLUDE_DIRECTORIES(
	../include
)

SET( INCLUDE_FILES_VECTOR_TYPES
	../include/check_function_existence.h
	../include/vec_template.h
	../include/vec_cuda.h
	../include/vec_eigen.h
	../include/vec_geometricOperations.h
	../include/vec_osg.h
	../include/vec_qt.h
)

SET( INCLUDE_FILES_ROI_TYPES
	../include/Roi3DF_eigen.h
	../include/Roi3DF_osg.h
	../include/Roi3DF_cuda.h
	../include/Roi3DF_qt.h
)

SET( INCLUDE_FILES_OTHER
	../include/Roi3DF.h
	../include/Roi3DF_geometricFunctions.h
	../include/FixedSizeVector.h
	../include/cuda_host_device.h
)

SET( INCLUDE_FILES 
	${INCLUDE_FILES_VECTOR_TYPES}
	${INCLUDE_FILES_ROI_TYPES}
	${INCLUDE_FILES_OTHER}
)

SET( SOURCE_FILES
	../src/Roi3DF.cpp
)

ADD_LIBRARY ( ${PROJECT_NAME} STATIC
	${INCLUDE_FILES}
	${SOURCE_FILES}
)

SET_PROPERTY( TARGET ${PROJECT_NAME} PROPERTY FOLDER "Algorithms")

SOURCE_GROUP( "Header Files\\Vector Types" FILES ${INCLUDE_FILES_VECTOR_TYPES} )
SOURCE_GROUP( "Header Files\\Roi Types" FILES ${INCLUDE_FILES_ROI_TYPES} )

IF( BUILD_EXAMPLES )
	ADD_SUBDIRECTORY( ../test ${CMAKE_CURRENT_BINARY_DIR}/test )
ENDIF()