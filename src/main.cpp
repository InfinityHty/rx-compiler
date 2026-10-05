#include "Lexer.h"
#include "Parser.h"
#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "AST.h"
#include "Semantic.h"

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
    SemanticCheck checker;
    if(checker.hasSemanticError(ASTtree)){
        delete ASTtree;
        return 1;
    }
    // SEMANTIC check：0 = Accept，1 = Reject。
    delete ASTtree;
    return 0;
}
