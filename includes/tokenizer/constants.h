#ifndef TOKENIZER_CONSTANTS_H
#define TOKENIZER_CONSTANTS_H

const int MAX_COLUMNS = 256;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 200;

const char ALFA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
const char DIGITS[] = "0123456789";
const char OPERATORS[] = "><=!+-%&|";
const char SPACES[] = {' ', '\t', '\n', '\0'};
const char LEFT_PARENTH = '(';
const char RIGHT_PARENTH = ')';
const char COMMA = ',';
const char ASTERISK = '*';
const char QUOTE = '\"';

// token types
enum STRING_TOKEN_TYPES {
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_SPACE,
  TOKEN_OPERATOR,
  TOKEN_ASTERISK,
  TOKEN_COMMA,
  TOKEN_QUOTE,
  TOKEN_LEFT_PARENTH,
  TOKEN_RIGHT_PARENTH,
  INSERT,
  CREATE,
  SELECT,
  INTO,
  TABLE,
  ASTERISK_TYPE,
  COMMA_TYPE,
  VALUES,
  FIELDS,
  STRINGS,
  SPACE,
  LEFT_PARENTHESIS,
  RIGHT_PARENTHESIS,
  AND,
  OR,
  WHERE,
  NOT,
  NUMBER,
  FROM,
  OPERATOR,
  TOKEN_UNKNOWN = -1
};

#endif // TOKENIZER_CONSTANTS_H
