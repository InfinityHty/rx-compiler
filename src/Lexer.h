
// Generated from Lexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace rx {


class  Lexer : public antlr4::Lexer {
public:
  enum {
    AS = 1, BREAK = 2, CONST = 3, CONTINUE = 4, CRATE = 5, ELSE = 6, FALSE = 7, 
    FN = 8, IF = 9, IMPL = 10, LET = 11, LOOP = 12, MUT = 13, RETURN = 14, 
    SELF_VALUE = 15, SELF_TYPE = 16, STATIC = 17, STRUCT = 18, SUPER = 19, 
    TRUE = 20, USE = 21, WHERE = 22, WHILE = 23, RESERVED_KEYWORD = 24, 
    DERIVE = 25, COPY = 26, CLONE = 27, PARTIAL_EQ = 28, EQ = 29, UNDERSCORE = 30, 
    IDENTIFIER = 31, INVALID_LIFETIME = 32, INVALID_CHARACTER_LITERAL = 33, 
    LIFETIME = 34, INTEGER_LITERAL = 35, INVALID_NUMBER = 36, GT = 37, LT = 38, 
    LE = 39, EQEQ = 40, NE = 41, ANDAND = 42, OROR = 43, NOT = 44, PLUS = 45, 
    MINUS = 46, STAR = 47, SLASH = 48, PERCENT = 49, CARET = 50, AMP = 51, 
    PIPE = 52, SHL = 53, ASSIGN = 54, PLUS_ASSIGN = 55, MINUS_ASSIGN = 56, 
    STAR_ASSIGN = 57, SLASH_ASSIGN = 58, PERCENT_ASSIGN = 59, CARET_ASSIGN = 60, 
    AMP_ASSIGN = 61, PIPE_ASSIGN = 62, SHL_ASSIGN = 63, DOT = 64, COMMA = 65, 
    SEMI = 66, COLON = 67, PATHSEP = 68, ARROW = 69, HASH = 70, LBRACE = 71, 
    RBRACE = 72, LBRACKET = 73, RBRACKET = 74, LPAREN = 75, RPAREN = 76, 
    WHITESPACE = 77, LINE_COMMENT = 78, BLOCK_COMMENT = 79, UNTERMINATED_BLOCK_COMMENT = 80, 
    ERROR_CHAR = 81, GT_SECOND = 82, GE_EQ = 83, SHR_EQ = 84
  };

  enum {
    AFTER_GT = 1, AFTER_SECOND_GT = 2
  };

  explicit Lexer(antlr4::CharStream *input);

  ~Lexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

}  // namespace rx
