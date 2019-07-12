set(SERVER_SRC
        NamedPipeSever.cpp
        )

add_library(server_lib
        ${SERVER_SRC}
        )

target_link_libraries(server_lib)