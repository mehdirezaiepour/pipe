
set(CLIENT_SRC
        NamedPipeClient.cpp
        )

add_library(client_lib
        ${CLIENT_SRC}
        )

target_link_libraries(client_lib)