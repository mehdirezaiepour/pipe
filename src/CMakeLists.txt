
add_subdirectory(Server)
add_subdirectory(Client)


add_executable(named_pipe
        sample_usage.cpp
        )

target_link_libraries(named_pipe
        server_lib
        client_lib
        )