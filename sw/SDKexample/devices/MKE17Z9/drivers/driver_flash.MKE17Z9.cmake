# Add set(CONFIG_USE_driver_flash true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/fsl_ftfx_controller.c
  ${CMAKE_CURRENT_LIST_DIR}/fsl_ftfx_flash.c
  ${CMAKE_CURRENT_LIST_DIR}/fsl_ftfx_cache.c
  ${CMAKE_CURRENT_LIST_DIR}/fsl_ftfx_flexnvm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "driver_flash.MKE17Z9 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()