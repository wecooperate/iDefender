enable_precompile()
enable_qt_support()

set(PROJECT_NAME base_ui)

file(GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp" "*.rc" "*.def" "*.qrc" "*.ui")

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::WinExtras)

file(GLOB_RECURSE AUTO_GEN_FILES ${CMAKE_CURRENT_BINARY_DIR}/*.cpp)

set_source_files_properties(${AUTO_GEN_FILES} PROPERTIES SKIP_PRECOMPILE_HEADERS "ON")

#
# 部分qt的生成文件需要移除预处理，在编译前文件还没有生成，导致设置属性失败。
# 如果出现预编译头相关的编译失败，重新编译一次即可。
#
# 硬编码添加未生成的文件。
#
set(MOC_FILES "${CMAKE_CURRENT_BINARY_DIR}/base_ui_autogen/mocs_compilation_Debug.cpp")
list(APPEND MOC_FILES "${CMAKE_CURRENT_BINARY_DIR}/base_ui_autogen/mocs_compilation_Release.cpp")
list(APPEND MOC_FILES "${CMAKE_CURRENT_BINARY_DIR}/base_ui_autogen/EWIEGA46WW/qrc_base.cpp")
set_source_files_properties(${MOC_FILES} PROPERTIES SKIP_PRECOMPILE_HEADERS "ON")
