enable_precompile()

set(PROJECT_NAME iDefenderService)

file(GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp" "*.rc")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE base_core sqlite3 ws2_32)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
