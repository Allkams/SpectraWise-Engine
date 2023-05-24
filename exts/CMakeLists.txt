ADD_LIBRARY(exts INTERFACE)

ADD_SUBDIRECTORY(glm)

if(WIN32)
	SET(SOLOUD_BACKEND_WINMM ON)
else()
	SET(SOLOUD_BACKEND_ALSA ON)
endif()
SET(SOLOUD_STATIC ON)

ADD_SUBDIRECTORY(soloud/contrib)
SET_TARGET_PROPERTIES(soloud PROPERTIES FOLDER "exts/soloud")
TARGET_INCLUDE_DIRECTORIES(exts INTERFACE soloud/include)

ADD_LIBRARY(imgui STATIC 
			imgui/imconfig.h
			imgui/imgui.cpp
			imgui/imgui.h
			#imgui/imgui_demo.cpp
			imgui/imgui_draw.cpp 
			imgui/imgui_impl_glfw.h
			imgui/imgui_impl_glfw.cpp
			imgui/imgui_impl_opengl3.h
			imgui/imgui_impl_opengl3.cpp
			imgui/imgui_impl_opengl3_loader.h
			imgui/imgui_internal.h
			imgui/imgui_tables.cpp
			imgui/imgui_widgets.cpp
			imgui/imstb_rectpack.h
			imgui/imstb_textedit.h
			imgui/imstb_truetype.h
			)
			


ADD_LIBRARY(nanovg STATIC
				nanovg/src/nanovg.c
				nanovg/src/nanovg.h
				nanovg/src/nanovg_gl.h
				nanovg/src/nanovg_gl_utils.h
				nanovg/src/stb_truetype.h
				nanovg/src/stb_image.h
				nanovg/src/fontstash.h
			)
TARGET_LINK_LIBRARIES(nanovg PUBLIC exts)
TARGET_INCLUDE_DIRECTORIES(nanovg PUBLIC nanovg/src)
SET_TARGET_PROPERTIES(nanovg PROPERTIES FOLDER "exts/nanovg")

TARGET_LINK_LIBRARIES(imgui PUBLIC exts)
TARGET_INCLUDE_DIRECTORIES(imgui PUBLIC imgui)
SET_TARGET_PROPERTIES(imgui PROPERTIES FOLDER "exts/imgui")

TARGET_LINK_LIBRARIES(exts INTERFACE imgui nanovg)