file(GLOB_RECURSE BASE_SRC "*.cpp" "*.hpp" "*.h")
file(GLOB_RECURSE BASE_HEADERS "*.hpp" "*.h")

set(RENDERDOC_API_SRC "RenderDoc.hpp")

add_library(renderdoc_api STATIC ${BASE_SRC})
set_target_properties(renderdoc_api PROPERTIES LINKER_LANGUAGE CXX)