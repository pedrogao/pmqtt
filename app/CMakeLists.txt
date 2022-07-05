include_directories(../lib)

# Executable
add_executable(pmq pmqtt.c)

target_link_libraries(pmq pmqtt_shared)