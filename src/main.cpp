#include "Lexer.h"
#include "Parser.h"
#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"

#include <iostream>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "usage: rx <source-file>\n";
        return 2;
    }

    antlr4::ANTLRFileStream input;
    try {
        input.loadFromFile(argv[1]);
    } catch (const std::exception &e) {
        std::cerr << "cannot open " << argv[1] << ": " << e.what() << "\n";
        return 2;
    }

    rx::Lexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    rx::Parser parser(&tokens);

    rx::Parser::CrateContext *tree = parser.crate(); // 程序入口crate
    (void)tree;  // TODO: 交给 AstBuilder（继承 ParserBaseVisitor）构建 AST

    // SEMANTIC 约定：退出 0 = 接受，退出 1 = 拒绝。
    // 目前只做到语法层面；语义检查写好后在这里汇总错误。
    return parser.getNumberOfSyntaxErrors() == 0 ? 0 : 1;
}
