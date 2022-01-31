set(CURRENT_PROJECT_FOLDER base)

add_subdirectory(core)
if(USE_BASE_UI)
	add_subdirectory(ui)
endif()
