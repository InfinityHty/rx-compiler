#!/usr/bin/env bash
# Regenerate the ANTLR lexer/parser from grammar/ into src/.
#
# The generated classes are named Lexer/Parser, which collide with
# antlr4::Lexer/antlr4::Parser in the C++ runtime. -package rx wraps the
# headers in namespace rx, but ANTLR 4.13.2 still emits member definitions
# at global scope in the .cpp files, so we qualify them with rx:: by hand
# (every `Parser::` / `Lexer::` in those files refers to the generated class).
set -euo pipefail
cd "$(dirname "$0")/.."

ANTLR_JAR=${ANTLR_JAR:-$HOME/tools/antlr/antlr-4.13.2-complete.jar}
OUT=$(mktemp -d)

java -jar "$ANTLR_JAR" -Dlanguage=Cpp -package rx -visitor \
    -o "$OUT" grammar/Lexer.g4 grammar/Parser.g4

sed -i 's/\bParser::/rx::Parser::/g' "$OUT/Parser.cpp"
sed -i 's/\bLexer::/rx::Lexer::/g' "$OUT/Lexer.cpp"
# The 1-arg constructors delegate to antlr4::Lexer/antlr4::Parser (base class);
# the template hardcodes the base name, which the class-name collision breaks.
sed -i 's/) : Lexer(input) {/) : antlr4::Lexer(input) {/' "$OUT/Lexer.cpp"
sed -i 's/) : Parser(input) {/) : antlr4::Parser(input) {/' "$OUT/Parser.cpp"

cp "$OUT"/*.cpp "$OUT"/*.h src/
cp "$OUT"/*.interp "$OUT"/*.tokens src/appendix/
rm -rf "$OUT"
