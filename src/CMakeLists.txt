set(SOURCES
	parser/lexer.cpp
    parser/lexer.h
    parser/token_type.h
    parser/token.h
    parser/token.cpp
    parser/token_evaluator.h
    parser/token_recognizer.cpp
    parser/token_recognizer.h

    main.cpp
)

add_executable(db07 ${SOURCES})
