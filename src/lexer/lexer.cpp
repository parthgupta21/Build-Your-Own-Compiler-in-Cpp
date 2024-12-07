#include <iostream>
#include <string>
#include <vector>
#include <cctype> // For isdigit() and isalpha()

using namespace std;

enum class TokenType
{
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    NUMBER,
    END,
    ERROR
};

struct Token
{
    TokenType type;
    string value;
};

class Lexer
{
private:
    string source;
    size_t pos;

    string readNumber()
    {
        size_t start = pos;
        while ((pos < source.length()) && (isdigit(source[pos])))
        {
            pos++;
        }

        return source.substr(start, pos - start);
    }

    string readIdentifier()
    {
        size_t start = pos;
        while ((pos < source.length()) && (isalnum(source[pos])))
        {
            pos++;
        }

        return source.substr(start, pos - start);
    }

public:
    explicit Lexer(const std::string &source) : source(source), pos(0) {}

    vector<Token> tokenize()
    {
        vector<Token> tokens;
        while (pos < source.length())
        {
            char ch = source[pos];

            if (isspace(ch))
            {
                pos++;
                continue;
            }

            if (isdigit(ch)){
                tokens.push_back({TokenType::NUMBER, readNumber()});
            }
            else if (isalpha(ch))
            {
                tokens.push_back({TokenType::IDENTIFIER, readIdentifier()});
            }
            else
            {
                tokens.push_back({TokenType::ERROR, std::string(1, ch)});
                ++pos;
            }
        }

        tokens.push_back({TokenType::END, ""});
        return tokens;
    }
};


int main(){
    string input = " int x = 5; int ans = 5 + x;";

    Lexer lexer(input);

    auto tokens = lexer.tokenize();
    for (auto token: tokens){
        std::cout << "Token: " << token.value << " Type: ";
        switch (token.type)
        {
        case TokenType::KEYWORD:
            std::cout << "KEYWORD";
            break;
        case TokenType::IDENTIFIER:
            std::cout << "IDENTIFIER";
            break;
        case TokenType::OPERATOR:
            std::cout << "OPERATOR";
            break;
        case TokenType::NUMBER:
            std::cout << "NUMBER";
            break;
        case TokenType::ERROR:
            std::cout << "ERROR";
            break;
        case TokenType::END:
            std::cout << "END";
            break;
        }
        std::cout << std::endl;
    }
    return 0;
}
