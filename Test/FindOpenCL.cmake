#
#  This file taken from FindOpenCL project @ http://gitorious.com/findopencl
#
# - Try to find OpenCL
# This module tries to find an OpenCL implementation on your system. It supports
# AMD / ATI, Apple and NVIDIA implementations, but shoudl work, too.
#
# Once done this will define
#  OPENCL_FOUND        - system has OpenCL
#  OPENCL_INCLUDE_DIRS  - the OpenCL include directory
#  OPENCL_LIBRARIES    - link these to use OpenCL
#
# WIN32 should work, but is untested

FIND_PACKAGE( PackageHandleStandardArgs )

SET (OPENCL_VERSION_STRING "0.2.0")
SET (OPENCL_VERSION_MAJOR 0)
SET (OPENCL_VERSION_MINOR 1)
SET (OPENCL_VERSION_PATCH 0)

IF (APPLE)

  FIND_LIBRARY(OPENCL_LIBRARIES OpenCL DOC "OpenCL lib for OSX")
  FIND_PATH(OPENCL_INCLUDE_DIRS OpenCL/cl.h DOC "Include for OpenCL on OSX")

ELSE (APPLE)

	IF (WIN32)
	
	    FIND_PATH(OPENCL_INCLUDE_DIRS CL/cl.h)
	
	    # The AMD SDK currently installs both x86 and x86_64 libraries
	    # This is only a hack to find out architecture
	    IF( ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "AMD64" )
	    	SET(OPENCL_LIB_DIR "$ENV{ATISTREAMSDKROOT}/lib/x86_64")
			SET(OPENCL_LIB_DIR "$ENV{ATIINTERNALSTREAMSDKROOT}/lib/x86_64")
	    ELSE (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "AMD64")
	    	SET(OPENCL_LIB_DIR "$ENV{ATISTREAMSDKROOT}/lib/x86")
	   		SET(OPENCL_LIB_DIR "$ENV{ATIINTERNALSTREAMSDKROOT}/lib/x86")
	    ENDIF( ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "AMD64" )

	    # find out if the user asked for a 64-bit build, and use the corresponding 
	    # 64 or 32 bit NVIDIA library paths to the search:
	    STRING(REGEX MATCH "Win64" ISWIN64 ${CMAKE_GENERATOR})
	    IF("${ISWIN64}" STREQUAL "Win64") 
	    	FIND_LIBRARY(OPENCL_LIBRARIES OpenCL.lib $ENV{CUDA_PATH}/lib/x64 ${OPENCL_LIB_DIR} )
	    ELSE("${ISWIN64}" STREQUAL "Win64") 
	    	FIND_LIBRARY(OPENCL_LIBRARIES OpenCL.lib $ENV{CUDA_PATH}/lib/Win32 ${OPENCL_LIB_DIR} )
	    ENDIF("${ISWIN64}" STREQUAL "Win64") 

	    GET_FILENAME_COMPONENT(_OPENCL_INC_CAND ${OPENCL_LIB_DIR}/../../include ABSOLUTE)
	    
	    # On Win32 search relative to the library
	    FIND_PATH(OPENCL_INCLUDE_DIRS CL/cl.h PATHS "${_OPENCL_INC_CAND}" $ENV{CUDA_INC_PATH} $ENV{CUDA_PATH}/include)
	
	ELSE (WIN32)

            # Unix style platforms
            FIND_LIBRARY(OPENCL_LIBRARIES OpenCL
              ENV LD_LIBRARY_PATH
            )

            GET_FILENAME_COMPONENT(OPENCL_LIB_DIR ${OPENCL_LIBRARIES} PATH)
            GET_FILENAME_COMPONENT(_OPENCL_INC_CAND ${OPENCL_LIB_DIR}/../../include ABSOLUTE)

            # The AMD SDK currently does not place its headers
            # in /usr/include, therefore also search relative
            # to the library
            FIND_PATH(OPENCL_INCLUDE_DIRS CL/cl.h PATHS ${_OPENCL_INC_CAND} "/opt/cuda/include" "/usr/local/cuda/include" "/opt/AMDAPP/include")

	ENDIF (WIN32)

ENDIF (APPLE)

FIND_PACKAGE_HANDLE_STANDARD_ARGS( OpenCL DEFAULT_MSG OPENCL_LIBRARIES OPENCL_INCLUDE_DIRS )

MARK_AS_ADVANCED(
  OPENCL_INCLUDE_DIRS
)

