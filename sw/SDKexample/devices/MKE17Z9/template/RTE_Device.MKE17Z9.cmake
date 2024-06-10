# Add set(CONFIG_USE_RTE_Device true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_DEVICE_ID STREQUAL MKE17Z512xxx9) AND CONFIG_USE_driver_dmamux AND CONFIG_USE_driver_edma)

add_config_file(${CMAKE_CURRENT_LIST_DIR}/RTE_Device.h "" RTE_Device.MKE17Z9)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "RTE_Device.MKE17Z9 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
