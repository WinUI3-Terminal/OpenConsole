cmake_minimum_required(VERSION 3.30)

project(OpenConsole)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

link_directories(${PROJECT_SOURCE_DIR}/compiled)

add_compile_definitions(FMT_HEADER_ONLY)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_ITERATOR_DEBUG_LEVEL=2)
else()
    add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)
endif()

add_compile_options(-flto)
add_link_options(-s -flto -lmsvcrt)

# ------------------ BEGIN ConTSF ------------------ #

add_library(ConTSF STATIC
${PROJECT_SOURCE_DIR}/src/tsf/Handle.cpp
${PROJECT_SOURCE_DIR}/src/tsf/Implementation.cpp
# ${PROJECT_SOURCE_DIR}/src/tsf/precomp.cpp
)

target_compile_options(ConTSF PRIVATE -w)
target_compile_options(ConTSF PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConTSF PRIVATE
${PROJECT_SOURCE_DIR}/src/tsf
${PROJECT_SOURCE_DIR}/generated

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConInt ------------------ #

add_library(ConInt STATIC
${PROJECT_SOURCE_DIR}/src/internal/stubs.cpp
# ${PROJECT_SOURCE_DIR}/src/internal/precomp.cpp
)

target_compile_options(ConInt PRIVATE -w)
target_compile_options(ConInt PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConInt PRIVATE
${PROJECT_SOURCE_DIR}/src/internal

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConRenderBase ------------------ #

add_library(ConRenderBase STATIC
${PROJECT_SOURCE_DIR}/src/renderer/base/FontInfoBase.cpp
${PROJECT_SOURCE_DIR}/src/renderer/base/FontInfoDesired.cpp
${PROJECT_SOURCE_DIR}/src/renderer/base/FontResource.cpp
${PROJECT_SOURCE_DIR}/src/renderer/base/precomp.cpp
${PROJECT_SOURCE_DIR}/src/renderer/base/RenderEngineBase.cpp
${PROJECT_SOURCE_DIR}/src/renderer/base/renderer.cpp
${PROJECT_SOURCE_DIR}/src/renderer/base/RenderSettings.cpp
${PROJECT_SOURCE_DIR}/src/renderer/base/thread.cpp
${PROJECT_SOURCE_DIR}/src/renderer/base/CSSLengthPercentage.cpp
${PROJECT_SOURCE_DIR}/src/renderer/base/fontinfo.cpp
)

target_compile_options(ConRenderBase PRIVATE -w)
target_compile_options(ConRenderBase PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConRenderBase PRIVATE
${PROJECT_SOURCE_DIR}/src/renderer/base

${PROJECT_SOURCE_DIR}/generated

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConRenderGdi ------------------ #

add_library(ConRenderGdi STATIC
${PROJECT_SOURCE_DIR}/src/renderer/gdi/invalidate.cpp
${PROJECT_SOURCE_DIR}/src/renderer/gdi/math.cpp
${PROJECT_SOURCE_DIR}/src/renderer/gdi/paint.cpp
${PROJECT_SOURCE_DIR}/src/renderer/gdi/precomp.cpp
${PROJECT_SOURCE_DIR}/src/renderer/gdi/state.cpp
)

target_compile_options(ConRenderGdi PRIVATE -w)
target_compile_options(ConRenderGdi PRIVATE -DUNICODE -D_UNICODE)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(ConRenderGdi PRIVATE -DDBG)
endif()

target_include_directories(ConRenderGdi PRIVATE
${PROJECT_SOURCE_DIR}/src/renderer/gdi

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConRenderGdi FontList ------------------ #

add_executable(FontList
${PROJECT_SOURCE_DIR}/src/renderer/gdi/tool/main.cpp
)

target_compile_options(FontList PRIVATE -w)
target_compile_options(FontList PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(FontList PRIVATE
${PROJECT_SOURCE_DIR}/src/renderer/gdi

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConRenderUia ------------------ #

add_library(ConRenderUia STATIC
# ${PROJECT_SOURCE_DIR}/src/renderer/uia/precomp.cpp
${PROJECT_SOURCE_DIR}/src/renderer/uia/UiaRenderer.cpp
${PROJECT_SOURCE_DIR}/src/renderer/uia/UiaRenderer.hpp
)

target_compile_options(ConRenderUia PRIVATE -w)
target_compile_options(ConRenderUia PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConRenderUia PRIVATE
${PROJECT_SOURCE_DIR}/src/renderer/uia

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConRenderWddmCon ------------------ #

add_library(ConRenderWddmCon STATIC
# ${PROJECT_SOURCE_DIR}/src/renderer/wddmcon/precomp.cpp
${PROJECT_SOURCE_DIR}/src/renderer/wddmcon/WddmConRenderer.cpp
${PROJECT_SOURCE_DIR}/src/renderer/wddmcon/main.cxx
)

target_compile_options(ConRenderWddmCon PRIVATE -w)
target_compile_options(ConRenderWddmCon PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConRenderWddmCon PRIVATE
${PROJECT_SOURCE_DIR}/src/renderer/wddmcon

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConRenderAtlas HLSL Shaders ------------------ #

option(BUILD_ATLAS_SHADERS "Enable build Atlas HLSL Shaders" ON)
set(FXC_COMPILER_PATH "C:/Program Files (x86)/Windows Kits/10/bin/10.0.22621.0/x64/fxc.exe")

add_custom_target(AtlasShaders)

set(HLSL_SHADER_FILES
${PROJECT_SOURCE_DIR}/src/renderer/atlas/shader_vs.hlsl
${PROJECT_SOURCE_DIR}/src/renderer/atlas/shader_ps.hlsl
${PROJECT_SOURCE_DIR}/src/renderer/atlas/custom_shader_vs.hlsl
${PROJECT_SOURCE_DIR}/src/renderer/atlas/custom_shader_ps.hlsl
)


set_source_files_properties(${PROJECT_SOURCE_DIR}/src/renderer/atlas/shader_vs.hlsl PROPERTIES ShaderType "vs")
set_source_files_properties(${PROJECT_SOURCE_DIR}/src/renderer/atlas/shader_ps.hlsl PROPERTIES ShaderType "ps")
set_source_files_properties(${PROJECT_SOURCE_DIR}/src/renderer/atlas/custom_shader_vs.hlsl PROPERTIES ShaderType "vs")
set_source_files_properties(${PROJECT_SOURCE_DIR}/src/renderer/atlas/custom_shader_ps.hlsl PROPERTIES ShaderType "ps")

set_source_files_properties(${HLSL_SHADER_FILES} PROPERTIES ShaderModel "4_0")

foreach(FILE ${HLSL_SHADER_FILES})
  get_filename_component(FILE_WE ${FILE} NAME_WE)
  get_source_file_property(shadertype ${FILE} ShaderType)
  get_source_file_property(shadermodel ${FILE} ShaderModel)
  add_custom_command(TARGET AtlasShaders
                     COMMAND ${FXC_COMPILER_PATH} /nologo /Emain /WX /T${shadertype}_${shadermodel} /all_resources_bound $<IF:$<CONFIG:DEBUG>,/Od,/O1> /Zi /Fh ${PROJECT_SOURCE_DIR}/generated/atlasshader/${FILE_WE}.h /Vn ${FILE_WE} ${FILE}
                     MAIN_DEPENDENCY ${FILE}
                     COMMENT "HLSL ${FILE}"
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM)
endforeach(FILE)

# ------------------ BEGIN ConRenderAtlas ------------------ #

add_library(ConRenderAtlas STATIC
${PROJECT_SOURCE_DIR}/src/renderer/atlas/AtlasEngine.api.cpp
${PROJECT_SOURCE_DIR}/src/renderer/atlas/AtlasEngine.cpp
${PROJECT_SOURCE_DIR}/src/renderer/atlas/AtlasEngine.r.cpp
${PROJECT_SOURCE_DIR}/src/renderer/atlas/Backend.cpp
${PROJECT_SOURCE_DIR}/src/renderer/atlas/BackendD2D.cpp
${PROJECT_SOURCE_DIR}/src/renderer/atlas/BackendD3D.cpp
${PROJECT_SOURCE_DIR}/src/renderer/atlas/BuiltinGlyphs.cpp
${PROJECT_SOURCE_DIR}/src/renderer/atlas/dwrite.cpp
${PROJECT_SOURCE_DIR}/src/renderer/atlas/DWriteTextAnalysis.cpp
# ${PROJECT_SOURCE_DIR}/src/renderer/atlas/pch.cpp
${PROJECT_SOURCE_DIR}/src/renderer/atlas/stb_rect_pack.cpp
${PROJECT_SOURCE_DIR}/src/renderer/atlas/wic.cpp
)

target_compile_options(ConRenderAtlas PRIVATE -w)
target_compile_options(ConRenderAtlas PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConRenderAtlas PRIVATE
${PROJECT_SOURCE_DIR}/src/renderer/atlas

${PROJECT_SOURCE_DIR}/oss/stb
${PROJECT_SOURCE_DIR}/generated/atlasshader
${PROJECT_SOURCE_DIR}/generated

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN TerminalInput ------------------ #

add_library(TerminalInput STATIC
${PROJECT_SOURCE_DIR}/src/terminal/input/mouseInput.cpp
${PROJECT_SOURCE_DIR}/src/terminal/input/mouseInputState.cpp
# ${PROJECT_SOURCE_DIR}/src/terminal/input/precomp.cpp
${PROJECT_SOURCE_DIR}/src/terminal/input/terminalInput.cpp
)

target_compile_options(TerminalInput PRIVATE -w)
target_compile_options(TerminalInput PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(TerminalInput PRIVATE
${PROJECT_SOURCE_DIR}/src/terminal/input

${PROJECT_SOURCE_DIR}/generated

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConTermParser ------------------ #

add_library(ConTermParser STATIC
${PROJECT_SOURCE_DIR}/src/terminal/parser/tracing.cpp
${PROJECT_SOURCE_DIR}/src/terminal/parser/base64.cpp
${PROJECT_SOURCE_DIR}/src/terminal/parser/InputStateMachineEngine.cpp
${PROJECT_SOURCE_DIR}/src/terminal/parser/OutputStateMachineEngine.cpp
# ${PROJECT_SOURCE_DIR}/src/terminal/parser/precomp.cpp
${PROJECT_SOURCE_DIR}/src/terminal/parser/stateMachine.cpp
)

target_compile_options(ConTermParser PRIVATE -w)
target_compile_options(ConTermParser PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConTermParser PRIVATE
${PROJECT_SOURCE_DIR}/src/terminal/parser

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConBufferOut ------------------ #

add_library(ConBufferOut STATIC
${PROJECT_SOURCE_DIR}/src/buffer/out/cursor.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/ImageSlice.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/OutputCell.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/OutputCellIterator.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/OutputCellRect.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/OutputCellView.cpp
# ${PROJECT_SOURCE_DIR}/src/buffer/out/precomp.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/Row.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/search.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/TextAttribute.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/textBuffer.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/textBufferCellIterator.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/textBufferTextIterator.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/TextColor.cpp
${PROJECT_SOURCE_DIR}/src/buffer/out/UTextAdapter.cpp
)

target_compile_options(ConBufferOut PRIVATE -w)
target_compile_options(ConBufferOut PRIVATE -DUNICODE -D_UNICODE)
target_compile_options(ConBufferOut PRIVATE -mavx2)

target_include_directories(ConBufferOut PRIVATE
${PROJECT_SOURCE_DIR}/src/buffer/out

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConTermAdapt ------------------ #

add_library(ConTermAdapt STATIC
${PROJECT_SOURCE_DIR}/src/terminal/adapter/adaptDispatch.cpp
${PROJECT_SOURCE_DIR}/src/terminal/adapter/adaptDispatchGraphics.cpp
${PROJECT_SOURCE_DIR}/src/terminal/adapter/FontBuffer.cpp
${PROJECT_SOURCE_DIR}/src/terminal/adapter/InteractDispatch.cpp
${PROJECT_SOURCE_DIR}/src/terminal/adapter/MacroBuffer.cpp
${PROJECT_SOURCE_DIR}/src/terminal/adapter/PageManager.cpp
# ${PROJECT_SOURCE_DIR}/src/terminal/adapter/precomp.cpp
${PROJECT_SOURCE_DIR}/src/terminal/adapter/SixelParser.cpp
${PROJECT_SOURCE_DIR}/src/terminal/adapter/terminalOutput.cpp
)

target_compile_options(ConTermAdapt PRIVATE -w)
target_compile_options(ConTermAdapt PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConTermAdapt PRIVATE
${PROJECT_SOURCE_DIR}/src/terminal/adapter

${PROJECT_SOURCE_DIR}/generated

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

add_dependencies(ConTermAdapt ConTypes)

target_link_libraries(ConTermAdapt PRIVATE ConTypes)

# ------------------ BEGIN ConProps ------------------ #

add_library(ConProps STATIC
${PROJECT_SOURCE_DIR}/src/propslib/DelegationConfig.cpp
# ${PROJECT_SOURCE_DIR}/src/propslib/precomp.cpp
${PROJECT_SOURCE_DIR}/src/propslib/RegistrySerialization.cpp
${PROJECT_SOURCE_DIR}/src/propslib/ShortcutSerialization.cpp
${PROJECT_SOURCE_DIR}/src/propslib/TrueTypeFontList.cpp
)

target_compile_options(ConProps PRIVATE -w)
target_compile_options(ConProps PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConProps PRIVATE
${PROJECT_SOURCE_DIR}/src/propslib

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN MidiAudio ------------------ #

add_library(MidiAudio STATIC
${PROJECT_SOURCE_DIR}/src/audio/midi/MidiAudio.cpp
# ${PROJECT_SOURCE_DIR}/src/audio/midi/precomp.cpp
)

target_compile_options(MidiAudio PRIVATE -w)
target_compile_options(MidiAudio PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(MidiAudio PRIVATE
${PROJECT_SOURCE_DIR}/src/propslib

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConTypes ------------------ #

add_library(ConTypes STATIC
${PROJECT_SOURCE_DIR}/src/types/CodepointWidthDetector.cpp
${PROJECT_SOURCE_DIR}/src/types/ColorFix.cpp
${PROJECT_SOURCE_DIR}/src/types/colorTable.cpp
${PROJECT_SOURCE_DIR}/src/types/convert.cpp
${PROJECT_SOURCE_DIR}/src/types/GlyphWidth.cpp
# ${PROJECT_SOURCE_DIR}/src/types/precomp.cpp
${PROJECT_SOURCE_DIR}/src/types/ScreenInfoUiaProviderBase.cpp
${PROJECT_SOURCE_DIR}/src/types/sgrStack.cpp
${PROJECT_SOURCE_DIR}/src/types/TermControlUiaProvider.cpp
${PROJECT_SOURCE_DIR}/src/types/TermControlUiaTextRange.cpp
${PROJECT_SOURCE_DIR}/src/types/ThemeUtils.cpp
${PROJECT_SOURCE_DIR}/src/types/UiaTextRangeBase.cpp
${PROJECT_SOURCE_DIR}/src/types/UiaTracing.cpp
${PROJECT_SOURCE_DIR}/src/types/utils.cpp
${PROJECT_SOURCE_DIR}/src/types/viewport.cpp
)

target_compile_options(ConTypes PRIVATE -w)
target_compile_options(ConTypes PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConTypes PRIVATE
${PROJECT_SOURCE_DIR}/src/types
${PROJECT_SOURCE_DIR}/generated

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN ConhostV2Lib ------------------ #

add_library(ConhostV2Lib STATIC
${PROJECT_SOURCE_DIR}/src/host/_output.cpp
${PROJECT_SOURCE_DIR}/src/host/_stream.cpp
${PROJECT_SOURCE_DIR}/src/host/alias.cpp
${PROJECT_SOURCE_DIR}/src/host/cmdline.cpp
${PROJECT_SOURCE_DIR}/src/host/ConsoleArguments.cpp
${PROJECT_SOURCE_DIR}/src/host/consoleInformation.cpp
${PROJECT_SOURCE_DIR}/src/host/CursorBlinker.cpp
${PROJECT_SOURCE_DIR}/src/host/dbcs.cpp
${PROJECT_SOURCE_DIR}/src/host/directio.cpp
${PROJECT_SOURCE_DIR}/src/host/getset.cpp
${PROJECT_SOURCE_DIR}/src/host/globals.cpp
${PROJECT_SOURCE_DIR}/src/host/handle.cpp
${PROJECT_SOURCE_DIR}/src/host/history.cpp
${PROJECT_SOURCE_DIR}/src/host/init.cpp
${PROJECT_SOURCE_DIR}/src/host/input.cpp
${PROJECT_SOURCE_DIR}/src/host/inputBuffer.cpp
${PROJECT_SOURCE_DIR}/src/host/inputKeyInfo.cpp
${PROJECT_SOURCE_DIR}/src/host/inputReadHandleData.cpp
${PROJECT_SOURCE_DIR}/src/host/misc.cpp
${PROJECT_SOURCE_DIR}/src/host/ntprivapi.cpp
${PROJECT_SOURCE_DIR}/src/host/output.cpp
${PROJECT_SOURCE_DIR}/src/host/outputStream.cpp
# {PROJECT_SOURCE_DIR}/src/host/precomp.cpp
${PROJECT_SOURCE_DIR}/src/host/PtySignalInputThread.cpp
${PROJECT_SOURCE_DIR}/src/host/readData.cpp
${PROJECT_SOURCE_DIR}/src/host/readDataCooked.cpp
${PROJECT_SOURCE_DIR}/src/host/readDataDirect.cpp
${PROJECT_SOURCE_DIR}/src/host/readDataRaw.cpp
${PROJECT_SOURCE_DIR}/src/host/registry.cpp
${PROJECT_SOURCE_DIR}/src/host/renderData.cpp
${PROJECT_SOURCE_DIR}/src/host/renderFontDefaults.cpp
${PROJECT_SOURCE_DIR}/src/host/screenInfo.cpp
${PROJECT_SOURCE_DIR}/src/host/scrolling.cpp
${PROJECT_SOURCE_DIR}/src/host/selection.cpp
${PROJECT_SOURCE_DIR}/src/host/selectionInput.cpp
${PROJECT_SOURCE_DIR}/src/host/selectionState.cpp
${PROJECT_SOURCE_DIR}/src/host/settings.cpp
${PROJECT_SOURCE_DIR}/src/host/srvinit.cpp
${PROJECT_SOURCE_DIR}/src/host/stream.cpp
${PROJECT_SOURCE_DIR}/src/host/tracing.cpp
${PROJECT_SOURCE_DIR}/src/host/utils.cpp
${PROJECT_SOURCE_DIR}/src/host/VtInputThread.cpp
${PROJECT_SOURCE_DIR}/src/host/VtIo.cpp
${PROJECT_SOURCE_DIR}/src/host/writeData.cpp
)

target_compile_options(ConhostV2Lib PRIVATE -w)
target_compile_options(ConhostV2Lib PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConhostV2Lib PRIVATE
${PROJECT_SOURCE_DIR}/src/host
${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/fmt/include
${PROJECT_SOURCE_DIR}/oss/intervaltree

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

target_link_libraries(ConhostV2Lib PUBLIC
ConTSF
ConTypes
)

add_dependencies(ConhostV2Lib
ConTSF
ConTypes
)

# ------------------ BEGIN OpenConsoleProxy ------------------ #

#[[
add_library(OpenConsoleProxy SHARED
${PROJECT_SOURCE_DIR}/generated/dynamic/dlldata.c
${PROJECT_SOURCE_DIR}/generated/dynamic/IConsoleHandoff_i.c
${PROJECT_SOURCE_DIR}/generated/dynamic/IConsoleHandoff_p.c
${PROJECT_SOURCE_DIR}/generated/dynamic/ITerminalHandoff_i.c
${PROJECT_SOURCE_DIR}/generated/dynamic/ITerminalHandoff_p.c
)

target_compile_options(OpenConsoleProxy PRIVATE -w)
target_compile_options(OpenConsoleProxy PRIVATE -DUNICODE -D_UNICODE)
# Windows Terminal Preview
target_compile_options(OpenConsoleProxy PRIVATE -DPROXY_CLSID_IS={0x1833E661,0xCC81,0x4DD0,{0x87,0xC6,0xC2,0xF7,0x4B,0xD3,0x9E,0xFA}})

target_include_directories(OpenConsoleProxy PRIVATE
${PROJECT_SOURCE_DIR}/generated/dynamic
)
]]

# ------------------ BEGIN ConServer ------------------ #

add_library(ConServer STATIC
${PROJECT_SOURCE_DIR}/src/server/ApiDispatchers.cpp
${PROJECT_SOURCE_DIR}/src/server/ApiDispatchersInternal.cpp
${PROJECT_SOURCE_DIR}/src/server/ApiMessage.cpp
${PROJECT_SOURCE_DIR}/src/server/ApiMessageState.cpp
${PROJECT_SOURCE_DIR}/src/server/ApiSorter.cpp
${PROJECT_SOURCE_DIR}/src/server/ConDrvDeviceComm.cpp
${PROJECT_SOURCE_DIR}/src/server/ConsoleShimPolicy.cpp
${PROJECT_SOURCE_DIR}/src/server/DeviceHandle.cpp
${PROJECT_SOURCE_DIR}/src/server/Entrypoints.cpp
${PROJECT_SOURCE_DIR}/src/server/IoDispatchers.cpp
${PROJECT_SOURCE_DIR}/src/server/IoSorter.cpp
${PROJECT_SOURCE_DIR}/src/server/ObjectHandle.cpp
${PROJECT_SOURCE_DIR}/src/server/ObjectHeader.cpp
# ${PROJECT_SOURCE_DIR}/src/server/precomp.cpp
${PROJECT_SOURCE_DIR}/src/server/ProcessHandle.cpp
${PROJECT_SOURCE_DIR}/src/server/ProcessList.cpp
${PROJECT_SOURCE_DIR}/src/server/ProcessPolicy.cpp
${PROJECT_SOURCE_DIR}/src/server/WaitBlock.cpp
${PROJECT_SOURCE_DIR}/src/server/WaitQueue.cpp
${PROJECT_SOURCE_DIR}/src/server/WinNTControl.cpp
)

target_compile_options(ConServer PRIVATE -w)
target_compile_options(ConServer PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(ConServer PRIVATE
${PROJECT_SOURCE_DIR}/src/server

${PROJECT_SOURCE_DIR}/generated

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN TerminalInputeractivityBaseLib ------------------ #

add_library(TerminalInputeractivityBaseLib STATIC
${PROJECT_SOURCE_DIR}/src/interactivity/base/ApiDetector.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/base/EventSynthesis.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/base/HostSignalInputThread.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/base/InteractivityFactory.cpp
# ${PROJECT_SOURCE_DIR}/src/interactivity/base/precomp.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/base/PseudoConsoleWindowAccessibilityProvider.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/base/RemoteConsoleControl.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/base/ServiceLocator.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/base/VtApiRedirection.cpp
)

target_compile_options(TerminalInputeractivityBaseLib PRIVATE -w)
target_compile_options(TerminalInputeractivityBaseLib PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(TerminalInputeractivityBaseLib PRIVATE
${PROJECT_SOURCE_DIR}/src/interactivity/base
${PROJECT_SOURCE_DIR}/generated

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN TerminalInputeractivityOneCoreLib ------------------ #

add_library(TerminalInputeractivityOneCoreLib STATIC
${PROJECT_SOURCE_DIR}/src/interactivity/onecore/AccessibilityNotifier.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/onecore/BgfxEngine.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/onecore/ConIoSrvComm.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/onecore/ConsoleControl.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/onecore/ConsoleInputThread.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/onecore/ConsoleWindow.cpp
# ${PROJECT_SOURCE_DIR}/src/interactivity/onecore/precomp.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/onecore/SystemConfigurationProvider.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/onecore/WindowMetrics.cpp
)

target_compile_options(TerminalInputeractivityOneCoreLib PRIVATE -w)
target_compile_options(TerminalInputeractivityOneCoreLib PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(TerminalInputeractivityOneCoreLib PRIVATE
${PROJECT_SOURCE_DIR}/src/interactivity/onecore
${PROJECT_SOURCE_DIR}/generated

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

# ------------------ BEGIN TerminalInputeractivityWin32Lib ------------------ #

add_library(TerminalInputeractivityWin32Lib STATIC
${PROJECT_SOURCE_DIR}/src/interactivity/win32/AccessibilityNotifier.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/Clipboard.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/ConsoleControl.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/ConsoleInputThread.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/consoleKeyInfo.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/find.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/icon.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/menu.cpp
# ${PROJECT_SOURCE_DIR}/src/interactivity/win32/precomp.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/screenInfoUiaProvider.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/SystemConfigurationProvider.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/uiaTextRange.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/window.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/windowdpiapi.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/windowio.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/WindowMetrics.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/windowproc.cpp
${PROJECT_SOURCE_DIR}/src/interactivity/win32/windowUiaProvider.cpp
)

target_compile_options(TerminalInputeractivityWin32Lib PRIVATE -w)
target_compile_options(TerminalInputeractivityWin32Lib PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(TerminalInputeractivityWin32Lib PRIVATE
${PROJECT_SOURCE_DIR}/src/interactivity/win32
${PROJECT_SOURCE_DIR}/generated

${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

target_link_libraries(TerminalInputeractivityWin32Lib PUBLIC ConTSF)
add_dependencies(TerminalInputeractivityWin32Lib ConTSF)

# ------------------ BEGIN OpenConsole ------------------ #

add_executable(OpenConsole WIN32
${PROJECT_SOURCE_DIR}/src/host/exe/CConsoleHandoff.cpp
${PROJECT_SOURCE_DIR}/src/host/exe/exemain.cpp
# ${PROJECT_SOURCE_DIR}/src/host/precomp.cpp
)

target_compile_options(OpenConsole PRIVATE -w)
target_compile_options(OpenConsole PRIVATE -DUNICODE -D_UNICODE)

target_include_directories(OpenConsole PRIVATE

# OpenConsoleProxy
${PROJECT_SOURCE_DIR}/generated

${PROJECT_SOURCE_DIR}/src/host
${PROJECT_SOURCE_DIR}/src/host/exe
${PROJECT_SOURCE_DIR}/oss/wil/include
${PROJECT_SOURCE_DIR}/oss/GSL/include
${PROJECT_SOURCE_DIR}/oss/fmt/include

${PROJECT_SOURCE_DIR}/src/inc
${PROJECT_SOURCE_DIR}/dep
${PROJECT_SOURCE_DIR}/dep/Console
${PROJECT_SOURCE_DIR}/dep/Win32K
${PROJECT_SOURCE_DIR}/oss/chromium
${PROJECT_SOURCE_DIR}/oss/interval_tree
${PROJECT_SOURCE_DIR}/oss/pcg/include
)

target_link_directories(OpenConsole PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(OpenConsole
ConRenderWddmCon
ConRenderAtlas
ConRenderBase
ConRenderGdi
ConRenderUia
ConProps
ConBufferOut
ConTermParser
ConTermAdapt
TerminalInput
MidiAudio
ConInt
TerminalInputeractivityBaseLib
TerminalInputeractivityOneCoreLib
TerminalInputeractivityWin32Lib
ConhostV2Lib
ConServer
ConTypes

winmm
imm32
ntdll
runtimeobject
Synchronization
Uiautomationcore
Bcrypt
Shcore
icuuc
icuin
Propsys
usp10
# bad
Shlwapi
Pathcch
)

add_dependencies(OpenConsole
ConRenderWddmCon
ConRenderAtlas
ConRenderBase
ConRenderGdi
ConRenderUia
ConProps
ConBufferOut
ConTermParser
ConTermAdapt
TerminalInput
MidiAudio
ConInt
ConTypes
TerminalInputeractivityBaseLib
TerminalInputeractivityOneCoreLib
TerminalInputeractivityWin32Lib
ConhostV2Lib
ConServer
)
