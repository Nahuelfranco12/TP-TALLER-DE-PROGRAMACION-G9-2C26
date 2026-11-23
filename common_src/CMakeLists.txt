target_sources(taller_common
    PRIVATE
    # .cpp files
    foo.cpp
    liberror.cpp
    protocol.cpp
    resolver.cpp
    resolvererror.cpp
    socket.cpp
    game_dtos_builder.cpp
    PUBLIC
    # .h files
    foo.h
    liberror.h
    protocol.h
    resolver.h
    resolvererror.h
    socket.h
    queue.h
    thread.h
    constants.h
    game_dtos.h
    game_dtos_builder.h
    )
    