# Add set(CONFIG_USE_device_MKE17Z9_startup true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_device_MKE17Z9_system)

if(CONFIG_TOOLCHAIN STREQUAL iar)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/iar/startup_MKE17Z9.s "" device_MKE17Z9_startup.MKE17Z9)
endif()

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/gcc/startup_MKE17Z9.S "" device_MKE17Z9_startup.MKE17Z9)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mdk)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/arm/startup_MKE17Z9.S "" device_MKE17Z9_startup.MKE17Z9)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mcux)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/mcuxpresso/startup_mke17z9.c "" device_MKE17Z9_startup.MKE17Z9)
  add_config_file(${CMAKE_CURRENT_LIST_DIR}/mcuxpresso/startup_mke17z9.cpp "" device_MKE17Z9_startup.MKE17Z9)
endif()

else()

message(SEND_ERROR "device_MKE17Z9_startup.MKE17Z9 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
