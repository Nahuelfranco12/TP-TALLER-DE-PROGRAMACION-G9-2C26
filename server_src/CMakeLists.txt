target_sources(taller_server
    PRIVATE
    # .cpp files
    server_main.cpp
    acceptor.cpp
    client_handler.cpp
    client_queues.cpp
    gameloop.cpp
    server.cpp
    server_protocol.cpp
    server_receiver.cpp
    server_sender.cpp
    PUBLIC
    # .h files
    acceptor.h
    client_command.h
    client_handler.h
    client_queues.h
    gameloop.h
    server.h
    server_protocol.h
    server_receiver.h
    server_sender.h
    )
    