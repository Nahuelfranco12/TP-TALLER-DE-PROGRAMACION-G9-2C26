target_sources(taller_client
    PRIVATE
    # .cpp files
    main.cpp
    audio.cpp
    personaje.cpp
    tasa_constante.cpp
    interfaz.cpp
    mapa.cpp
    granja.cpp
    client.cpp
    client_protocol.cpp
    client_receiver.cpp
    client_sender.cpp
    caverna.cpp
    inventario.cpp
    alrededores.cpp
    PUBLIC
    # .h files
    client.h
    audio.h
    personaje.h
    direccion.h
    tasa_constante.h
    interfaz.h
    mapa.h
    granja.h
    client_protocol.h
    client_receiver.h
    client_sender.h
    caverna.h
    inventario.h
    alrededores.h
    )
    