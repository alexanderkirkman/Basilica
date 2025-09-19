# Sandbox executable that links Basilica
add_executable(Sandbox
  src/main.cpp
)

target_compile_features(Sandbox PRIVATE cxx_std_20)
target_set_warnings(Sandbox)

# Sandbox's own headers (if any)
target_include_directories(Sandbox PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Link to the lib via alias
target_link_libraries(Sandbox PRIVATE Basilica::Basilica)

# Helpful debug define
target_compile_definitions(Sandbox PRIVATE $<$<CONFIG:Debug>:BASC_DEBUG=1>)

# Ensure Sandbox can locate Basilica dylib from build tree on macOS
if(APPLE)
  if(CMAKE_CONFIGURATION_TYPES)
    foreach(cfg IN LISTS CMAKE_CONFIGURATION_TYPES)
      string(TOUPPER "${cfg}" CFG)
      set(rp "${CMAKE_BINARY_DIR}/lib/${cfg}")
      set_property(TARGET Sandbox APPEND_STRING PROPERTY
                   BUILD_RPATH "$<IF:$<CONFIG:${cfg}>,${rp};,>")
    endforeach()
  else()
    set_property(TARGET Sandbox APPEND PROPERTY BUILD_RPATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
  endif()

  # After install/bundle, search relative to the executable
  set_target_properties(Sandbox PROPERTIES
    INSTALL_RPATH "@executable_path/../lib;@loader_path/../lib"
  )
endif()
