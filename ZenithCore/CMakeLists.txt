set(PROJECT_NAME ZenithCore)

################################################################################
# Source groups
################################################################################
set(Header_Files
	"Buffer.h"
	"Descriptor.h"
	"Device.h"
	"Model.h"
	"Pipeline.h"
	"SwapChain.h"
	"Utils.h"
	"Window.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
	"Buffer.cpp"
	"Descriptor.cpp"
	"Device.cpp"
	"Model.cpp"
	"Pipeline.cpp"
	"SwapChain.cpp"
    "Window.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

set_source_files_properties(${ALL_FILES} PROPERTIES LANGUAGE CXX)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE ZenithCore)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
	"UNICODE;"
	"_UNICODE" 
)

################################################################################
# Compile and link options
################################################################################
target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<CONFIG:Release>:
		/Oi;
		/Gy
	>
	/permissive-;
	/std:c++latest;
	/sdl;
	/W3;
	${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
	${DEFAULT_CXX_EXCEPTION_HANDLING};
	/Y-
)
target_link_options(${PROJECT_NAME} PRIVATE
	$<$<CONFIG:Release>:
		/OPT:REF;
		/OPT:ICF
	>
)

################################################################################
# Dependencies
################################################################################
include_directories("../External/")

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC External)

target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PHYSX_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC glm::glm)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC physx)