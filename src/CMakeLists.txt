set(TARGET_NAME lua)
add_executable(${TARGET_NAME}
    lstate.c
    lapi.c
    ltm.c
    lmem.c
    ldo.c
    lfunc.c
    lgc.c
    llex.c
    lstring.c
    ltable.c
    lobject.c
    lzio.c
    ldebug.c
    ldump.c
    lvm.c
    lparser.c
    lundump.c
    lctype.c
    lopcodes.c
    lcode.c
    #
    main.cpp
    )
    target_compile_definitions(${TARGET_NAME} PRIVATE
    _CRT_SECURE_NO_WARNINGS
    )
