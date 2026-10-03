#include "Lexer.h"
#include "Parser.h"
#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "AST.h"

#include <iostream>

int main(int argc, char** argv) {
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

    rx::Parser::CrateContext* tree = parser.crate(); // build CST
    if(parser.getNumberOfSyntaxErrors() > 0) return 1;
    CrateNode* ASTtree = new CrateNode(Crate,tree); // build AST

    // SEMANTIC 约定：退出 0 = 接受，退出 1 = 拒绝。
    delete ASTtree;
    return 0;
}
