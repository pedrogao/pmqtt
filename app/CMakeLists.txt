include_directories(../lib)

# Executable
add_executable(pmqtt pmqtt.c)

target_link_libraries(pmqtt pmqtt_shared)