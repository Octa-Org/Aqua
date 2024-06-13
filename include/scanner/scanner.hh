#pragma once

#include "tokens.hh"
#include <error/error.hh>
#include <reader/reader.hh>
#include <string>
#include <stdlib.h>
#include <map>

#include <unordered_map>
#include <vector>

using namespace rift::reader;
typedef rift::scanner::Token Token;
typedef rift::scanner::TokenType Type;
namespace rift
{
    namespace scanner
    {
        struct Scanner : public Reader<char>
        {
            std::vector<char> source;
            std::vector<Token> tokens;
            std::unordered_map<std::string, Type> keywords;
            static unsigned start, curr, line;

            Scanner(const std::vector<char>& source);
            ~Scanner(){}

            /// @fn scan_token
            /// @brief Scans the source code and returns a list of tokens
            void scan_token();

            /// @fn scan_tokens
            /// @brief Scans the source code and returns a list of tokens
            /// @param cnt The number of tokens to scan
            void scan_tokens(unsigned cnt);

            /// @fn scan_source
            /// @brief Scans the source code and returns a list of tokens
            void scan_source();
        private:

            #pragma mark - Token Management

            void addToken(Type type) { addToken(type, ""); };
            void addToken(Type type, std::string literal) {
                tokens.push_back(Token(type, std::string(source.begin()+start, source.begin()+curr), literal, line));
            }

            #pragma mark - Helper Functions (Inline)

            inline bool isDigit(char c) { return c>='0' && c<='9'; }
            inline bool isAlpha(char c) { return (c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_'; }
            inline bool isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }

            #pragma mark - Token Scanners

            /// @brief Scans a string literal
            void string();
            /// @brief Scans a numeric literal
            void num();
            /// @brief Scans an identifier
            void identifier();
        };
    };
}