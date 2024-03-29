
set(CPACK_COMPONENTS_GROUPING ONE_PER_GROUP)
set(CPACK_TGZ_COMPONENT_INSTALL ON)

set(CPACK_PACKAGE_NAME row-tiqtaq)
set(CPACK_VERBATIM_VARIABLES TRUE)

set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)

include(CPackComponent)

cpack_add_component(row_tiqtaq_Development GROUP development)
cpack_add_component(row_tiqtaq_Runtime GROUP runtime)

cpack_add_component_group(development)
cpack_add_component_group(runtime)

include(CPack)
