# Add set(CONFIG_USE_DEVICES_Project_Template_MKE17Z9 true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_lpuart_adapter AND (CONFIG_DEVICE_ID STREQUAL MKE17Z512xxx9) AND CONFIG_USE_device_MKE17Z9_startup AND CONFIG_USE_driver_adc12 AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_common AND CONFIG_USE_driver_gpio AND CONFIG_USE_driver_lpi2c AND CONFIG_USE_driver_lpuart AND CONFIG_USE_driver_port AND CONFIG_USE_driver_smc AND ((CONFIG_USE_component_serial_manager AND CONFIG_USE_utility_assert AND CONFIG_USE_utility_debug_console) OR (CONFIG_USE_utility_assert_lite AND CONFIG_USE_utility_debug_console_lite)))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/board.h "" DEVICES_Project_Template_MKE17Z9.MKE17Z9)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/board.c "" DEVICES_Project_Template_MKE17Z9.MKE17Z9)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/clock_config.h "" DEVICES_Project_Template_MKE17Z9.MKE17Z9)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/clock_config.c "" DEVICES_Project_Template_MKE17Z9.MKE17Z9)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/pin_mux.h "" DEVICES_Project_Template_MKE17Z9.MKE17Z9)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/pin_mux.c "" DEVICES_Project_Template_MKE17Z9.MKE17Z9)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/peripherals.h "" DEVICES_Project_Template_MKE17Z9.MKE17Z9)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/peripherals.c "" DEVICES_Project_Template_MKE17Z9.MKE17Z9)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "DEVICES_Project_Template_MKE17Z9.MKE17Z9 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
