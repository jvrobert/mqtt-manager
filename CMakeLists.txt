idf_component_register(SRCS "src/MqttManager.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES
                    mqtt)

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-missing-field-initializers)