include_guard()
message("device_MCXN947_startup component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/gcc/startup_MCXN947_cm33_core0.S
)


include(device_MCXN947_system_MCXN947_cm33_core0)

