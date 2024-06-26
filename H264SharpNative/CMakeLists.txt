# This CMake is written for linux
# LLVM Clang 17 is reccomended.
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("OpenH264Wrapper2")


add_definitions(-DUNICODE -D_UNICODE)
add_compile_options(-Rpass=loop-vectorize)
# change this if your target doesnt support avx2
add_compile_options(-mavx2)
add_compile_options(-o2)


if(UNIX)
    # Set the C++ compiler only for UNIX systems (Linux and macOS)
    set(CMAKE_C_COMPILER "/usr/bin/clang-17")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++-17")
else()
    set(CMAKE_C_COMPILER "clang-cl")
    set(CMAKE_CXX_COMPILER "clang-cl")
endif()

#H264SharpNative-linux64.so

# This CMake is written for linux
add_library (CMakeProject1 SHARED 
"codec_api.h"
"codec_app_def.h"
"codec_def.h"
"codec_ver.h"
"ConverterLocal.h"
"Decoder.h"
"EncodedFrame.h"
"Encoder.h"
"ImageTypes.h"
"pch.h"
"Resource.h"
"TranscoderFactory.h"
"ConverterLocal.cpp"
"Decoder.cpp"
"dllmain.cpp"
"Encoder.cpp"
"ImageTypes.cpp"
"pch.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 17)
endif()
#output name
set_target_properties(CMakeProject1 PROPERTIES PREFIX "")
set_target_properties(CMakeProject1 PROPERTIES OUTPUT_NAME "H264SharpNative-linux64")
set_target_properties(CMakeProject1 PROPERTIES SUFFIX ".so")
# 32 bit linux
#set_target_properties(CMakeProject1 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
