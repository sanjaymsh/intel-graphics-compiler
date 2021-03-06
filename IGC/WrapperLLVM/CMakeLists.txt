#===================== begin_copyright_notice ==================================

#Copyright (c) 2017 Intel Corporation

#Permission is hereby granted, free of charge, to any person obtaining a
#copy of this software and associated documentation files (the
#"Software"), to deal in the Software without restriction, including
#without limitation the rights to use, copy, modify, merge, publish,
#distribute, sublicense, and/or sell copies of the Software, and to
#permit persons to whom the Software is furnished to do so, subject to
#the following conditions:

#The above copyright notice and this permission notice shall be included
#in all copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
#CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
#TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
#SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#======================= end_copyright_notice ==================================

set(IGC_BUILD__PROJ__WrapperLLVM       "${IGC_BUILD__PROJ_NAME_PREFIX}WrapperLLVM")
set(IGC_BUILD__PROJ__WrapperLLVM       "${IGC_BUILD__PROJ__WrapperLLVM}" PARENT_SCOPE)


set(IGC_WrapperLLVM_HDR
    "${CMAKE_CURRENT_SOURCE_DIR}/Utils.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/ADT/STLExtras.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Analysis/CallGraph.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Analysis/InlineCost.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Analysis/MemoryLocation.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Analysis/TargetLibraryInfo.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Bitcode/BitcodeWriter.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/IRBuilder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/CallSite.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/CFG.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/DerivedTypes.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/DIBuilder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/Instructions.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/Intrinsics.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/Value.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/InstrTypes.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/InstVisitor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/Constant.h"	
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/LegacyPassManagers.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/Module.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/PatternMatch.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/IR/PassTimingInfo.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Support/KnownBits.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Support/Alignment.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Support/TypeSize.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Transforms/IPO.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Transforms/Scalar.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Transforms/Utils/Cloning.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Transforms/Utils/LoopUtils.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/llvmWrapper/Transforms/Utils.h"
  )

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${LLVM_INCLUDE_DIRS}"
    "${IGC_BUILD__IGC_COMMON_DIR}"
)

igc_sg_register(
    IGC__WrapperLLVM
    "WrapperLLVM"
    FILES
      ${IGC_WrapperLLVM_HDR}
  )

set(IGC_WrapperLLVM_HDR ${IGC_WrapperLLVM_HDR} PARENT_SCOPE)
