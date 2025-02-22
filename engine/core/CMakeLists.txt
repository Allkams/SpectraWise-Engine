SET(files_core_core
	entitymanager.cc
	entitymanager.h
	resourcemanager.cc
	resourcemanager.h
    )
SOURCE_GROUP("core" FILES ${files_core})

SET(files_core_input
	input/gamepad.h
	input/gamepad.cc
	input/inputManager.h
	input/inputManager.cc
	input/key.h
	input/key.cc
	input/keyboard.h
	input/mouse.h
	)
SOURCE_GROUP("input" FILES ${files_core_input})



SET(files_core
	${files_core_core}
	${files_core_input})
	
SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(core STATIC ${files_core} ${files_pch})
TARGET_PCH(core ../)
ADD_DEPENDENCIES(core glew)
TARGET_LINK_LIBRARIES(core PUBLIC engine exts glew soloud)