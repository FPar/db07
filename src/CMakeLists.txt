set(SOURCES
	db07/StorageEngine/index.h
	db07/StorageEngine/index.cpp

	db07/QueryEngine/parser.h
	db07/QueryEngine/parser.cpp

    main.cpp
        parser/lexer.cpp parser/lexer.h parser/token_type.h parser/token.h parser/token.cpp)

add_executable(db07 ${SOURCES})
