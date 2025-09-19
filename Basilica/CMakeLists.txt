# Basilica shared library used by Sandbox
add_library(Basilica SHARED
  src/Basilica/Core/Application.cpp
)

# Nice alias consumers can link against
add_library(Basilica::Basilica ALIAS Basilica)

# C++ standard & features
target_compile_features(Basilica PUBLIC cxx_std_20)

# Public headers are under Basilica/src for now
target_include_directories(Basilica
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Build flags / defines
target_set_warnings(Basilica)
target_compile_definitions(Basilica PRIVATE $<$<CONFIG:Debug>:BASC_DEBUG=1>)

# (Optional) if you add an export macro header, define BASILICA_BUILD for this target
# target_compile_definitions(Basilica PRIVATE BASILICA_BUILD)

# Unity builds toggle (off by default)
if(BUILD_UNITY)
  set_target_properties(Basilica PROPERTIES UNITY_BUILD ON)
endif()

# macOS dylib rpath for running from build tree
if(APPLE)
  set_target_properties(Basilica PROPERTIES
    MACOSX_RPATH ON
    INSTALL_NAME_DIR "@rpath"
  )
endif()

# (Future) vendor deps will be linked here so Sandbox stays clean, e.g.:
# add_subdirectory(${CMAKE_SOURCE_DIR}/Basilica/vendor/glfw)
# target_link_libraries(Basilica PUBLIC glfw)
