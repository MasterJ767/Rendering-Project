set(PROJECT_NAME External)

################################################################################
# Source groups
################################################################################
set(STB_Files
	"stb/stb_image.h"
)
source_group("stb" FILES ${STB_Files})

set(Tiny_Object_Loader_Files
	"tinyobjectloader/tiny_obj_loader.h"
)
source_group("Tiny Object Loader" FILES ${Tiny_Object_Loader_Files})

set(ALL_FILES
	${STB_Files}
    ${Tiny_Object_Loader_Files}
)

set_source_files_properties(${ALL_FILES} PROPERTIES LANGUAGE CXX)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE External)

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