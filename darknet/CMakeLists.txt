cmake_minimum_required(VERSION 2.8)
project(darknet C)

OPTION(GPU "whether use gpu" ON)
OPTION(CUDNN "whether use cudnn" ON)
OPTION(OPENCV "whether use opencv" ON)

option(ENV_WINDOWS "Is using windows now?" ON)
option(LINK_STATIC "whether use STATIC link?" ON)

SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_C_FLAGS "-Ofast -fPIC")
set(CMAKE_CXX_FLAGS "-g -std=c++11")

SET(CONTRIB_DIR "D:/ykma/sur/contrib")
SET(ARCH "-gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35 -gencode arch=compute_50,code=[sm_50,compute_50] -gencode arch=compute_52,code=[sm_52,compute_52] -gencode arch=compute_61,code=[sm_61,compute_61]")

IF(${OPENCV})
	find_package(OpenCV REQUIRED)
    add_definitions(-DOPENCV)
    include_directories(${OpenCV_INCLUDE_DIRS})
    link_libraries(${OpenCV_LIBS})
ENDIF(${OPENCV})

IF(GPU)
	find_package(CUDA REQUIRED)
    add_definitions(-DGPU)
	include_directories(${CUDA_INCLUDE_DIRS})
    link_libraries(${CUDA_LIBRARIES} ${CUDA_CUBLAS_LIBRARIES} ${CUDA_curand_LIBRARY})
ENDIF(GPU)

IF(CUDNN)
	add_definitions(-DCUDNN)
    link_libraries(cudnn)
ENDIF(CUDNN)

include_directories(${CONTRIB_DIR}/darknet/src ${CONTRIB_DIR}/darknet/include ${CONTRIB_DIR}/darknet/3rdparty/include)

aux_source_directory(${CONTRIB_DIR}/darknet/src SOURCE)
list(REMOVE_ITEM SOURCE ${CONTRIB_DIR}/darknet/src/compare.c)

IF(GPU)
    file(GLOB CUDASRC "src/*.cu")
    if(ENV_WINDOWS OR LINK_STATIC)
    	cuda_compile(CUDASRC_O ${CUDASRC} STATIC OPTIONS ${ARCH})
    	add_library(darknet STATIC ${SOURCE} ${CUDASRC_O})
    else()
    	cuda_compile(CUDASRC_O ${CUDASRC} SHARED OPTIONS ${ARCH})
    	add_library(darknet SHARED ${SOURCE} ${CUDASRC_O})
    endif()
ELSE(GPU)
    if(ENV_WINDOWS OR LINK_STATIC)
        add_library(darknet STATIC ${SOURCE})
    else()
        add_library(darknet SHARED ${SOURCE})
    endif()
ENDIF(GPU)

