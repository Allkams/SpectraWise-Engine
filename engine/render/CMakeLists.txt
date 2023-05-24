SET(files_render
	temp.cc
	temp.h
    )
SOURCE_GROUP("render" FILES ${files_render})
	
#SET(files_pch ../config.h ../config.cc)
#SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(render STATIC ${files_render} ${files_pch})
TARGET_PCH(render ../)
#ADD_DEPENDENCIES(render)
TARGET_LINK_LIBRARIES(render PUBLIC engine exts)