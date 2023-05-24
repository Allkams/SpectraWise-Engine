SET(files_core
	temp.cc
	temp.h
    )
SOURCE_GROUP("core" FILES ${files_core})
	
SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(core STATIC ${files_core} ${files_pch})
TARGET_PCH(core ../)
#ADD_DEPENDENCIES(core glew enet)
TARGET_LINK_LIBRARIES(core PUBLIC engine exts)