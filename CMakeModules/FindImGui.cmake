find_path(IMGUI_INCLUDE_DIR
  NAMES imgui.h
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui
)

if (IMGUI_INCLUDE_DIR)
    set(IMGUI_FOUND TRUE)
endif ()

if (IMGUI_FOUND)
    if (NOT ImGui_FIND_QUIETLY)
        message(STATUS "Found ImGui: ${IMGUI_LIBRARY}")
    endif ()
else ()
    if (ImGui_FIND_REQUIRED)
        message(FATAL_ERROR "ImGui not found")
    endif ()
endif ()

mark_as_advanced(IMGUI_INCLUDE_DIR IMGUI_LIBRARY)
