#include <iostream>
#include <sstream>
#include <vector>
#include <optional>
#include <string>
#include <cmath>
#include <iomanip>

class Tokeniser
{
public:

    enum class Type
    {
        add,
        subtract,
        multiply,
        divide,
        
        unknown,
    };
    
    struct TokenList
    {
        double lhs;
        double rhs;
        Type type;
    };

    std::optional <TokenList> tokenise(std::string input) const
    {
        // Removing leading and trailing whitespace from input
        input = trim(input);
        
        // First, we find the type of operation in input
        auto type = findType(input);
        if (type == Type::unknown)
            return {};
        
        // Second, we determine lhs and rhs of operation
        auto lhs = findLHS(input, type);
        if (! lhs.has_value())
            return {};
        
        auto rhs = findRHS(input, type);
        if (! rhs.has_value())
            return {};
    
        // Assinging the variabls to the a TokenList object
        TokenList tokens;
        tokens.lhs = *lhs;
        tokens.rhs = *rhs;
        tokens.type = type;
        
        return tokens;
    }
    
private:

    std::string trim(std::string& str) const
    {
        // This function removes leading and trailing whitespace
        size_t first = str.find_first_not_of(" \n\t\v\f\r");
        if (first == std::string::npos)
            return "";
        size_t last = str.find_last_not_of (" \n\t\v\f\r");
        return str.substr(first, (last - first + 1));
    }
    
    bool find(std::string input, std::string character) const
    {
        return input.find(character) != std::string::npos;
    }
    
    std::optional <double> findAndExtractLHS(std::string input, std::string character) const
    {
        auto pos = input.find(character);
        
        // Checking if -ve is first
        if (character == "-" && pos == 0)
        {
            pos = input.substr(1).find(character) + 1;
        }
        
        if (pos != std::string::npos)
        {
            // LHS is everything from start of string to position of character
            std::string sub = input.substr(0, pos);
            
            // Removing leading and trailing whitespace - this makes inputs like "\t \t 6 + 2" viable
            std::string lhs = trim(sub);
            
            // Checking for pi
            if (lhs == "pi")
            {
                return M_PI;
            }
            
            // Checking for a valid input to std::stod
            try {
                size_t idx;
                std::stod(lhs, &idx);
                
                // pos returns index of the last character used for conversion.
                // here we check for inputs like '2refd' which would normally be valid.
                if (idx != lhs.size())
                {
                    throw (lhs);
                }
            } catch (std::invalid_argument) {
                // If input not valid, we say so, and continue processing
                std::cout << lhs << " is not a valid lhs input" << std::endl;
                return {};
            } catch (std::string str) {
                std::cout << lhs << " is not a valid lhs input" << std::endl;
                return {};
            }
            
            // Returning the std::stod evaluation of the lhs argument
            return std::stod(lhs);
        }
        
        return {};
    }
    
    std::optional <double> findAndExtractRHS(std::string input, std::string character) const
    {
        auto pos = input.find(character);
        
        // Checking if -ve is first
        if (character == "-" && pos == 0)
        {
            pos = input.substr(1).find(character) + 1;
        }
        
        if (pos != std::string::npos)
        {
            // RHS is everything from position of character onwards
            std::string sub = input.substr(pos + 1);
            
            // Removing leading and trailing whitespace
            std::string rhs = trim(sub);
            
            // Checking for pi
            if (rhs == "pi")
            {
                return M_PI;
            }
            
            // Checking for a valid input to std::stod
            try {
                size_t idx;
                std::stod(rhs, &idx);
                
                // pos returns index of the last character used for conversion.
                // here we check for inputs like '2refd' which would normally be valid.
                if (idx != rhs.size())
                {
                    throw (rhs);
                }
            } catch (std::invalid_argument) {
                // If input not valid, we say so, and continue processing
                std::cout << rhs << " is not a valid rhs input" << std::endl;
                return {};
            } catch (std::string str) {
                std::cout << rhs << " is not a valid rhs input" << std::endl;
                return {};
            }
            
            // Returning the std::stod evaluation of the rhs argument
            return std::stod(rhs);
        }
        
        return {};
    }

    Type findType(std::string input) const
    {
        // Here, we check if the first number is -ve. This adds support for operations like -2*-20
        if (find(input.substr(0,1), "-"))
        {
            // If it is, with this order of operations checks for - last
            if (find(input.substr(1), "+")) return Type::add;
            if (find(input.substr(1), "*")) return Type::multiply;
            if (find(input.substr(1), "/")) return Type::divide;
            if (find(input.substr(1), "-")) return Type::subtract;
        }
        
        // Possible types of operations
        if (find(input, "+")) return Type::add;
        if (find(input, "*")) return Type::multiply;
        if (find(input, "/")) return Type::divide;
        if (find(input, "-")) return Type::subtract;
        
        return Type::unknown;
    }
    
    std::optional <double> findLHS(std::string input, Type type) const
    {
        switch (type)
        {
            case Type::add:
            {
                auto result = findAndExtractLHS(input, "+");
                return result;
            }
            case Type::subtract:
            {
                auto result = findAndExtractLHS(input, "-");
                return result;
            }
            case Type::multiply:
            {
                auto result = findAndExtractLHS(input, "*");
                return result;
            }
            case Type::divide:
            {
                auto result = findAndExtractLHS(input, "/");
                return result;
            }
            default:
                break;
        }
        return {};
    }
    
    std::optional <double> findRHS(std::string input, Type type) const
    {
        switch (type)
        {
            case Type::add:
            {
                auto result = findAndExtractRHS(input, "+");
                return result;
            }
            case Type::subtract:
            {
                auto result = findAndExtractRHS(input, "-");
                return result;
            }
            case Type::multiply:
            {
                auto result = findAndExtractRHS(input, "*");
                return result;
            }
            case Type::divide:
            {
                auto result = findAndExtractRHS(input, "/");
                return result;
            }
            default:
                break;
        }
        return {};
    }
};

class Calculator
{
public:

    Calculator () = default;
    ~Calculator () = default;
    
    double calculate(Tokeniser::TokenList tokens) const
    {
        // Depending on type of operation foudn in tokens object, return the appropriate result
        switch (tokens.type)
        {
            case Tokeniser::Type::add:
                return tokens.lhs + tokens.rhs;
            case Tokeniser::Type::subtract:
                return tokens.lhs - tokens.rhs;
            case Tokeniser::Type::multiply:
                return tokens.lhs * tokens.rhs;
            case Tokeniser::Type::divide:
                if (tokens.rhs == 0) { std::cout << "Warning: Divison by zero" << std::endl; }
                return tokens.lhs / tokens.rhs;
            default:
                break;
        }
        
        return 0;
    }
};

class InputProcessor
{
public:
    
    enum class InputRequest
    {
        quitProcessing,
        continueProcessing,
    };
    

    InputRequest requestInput() const
    {
        std::cout << "Please enter a calculation (Type Q to quit)" << std::endl;
        
        std::string input;
        std::getline (std::cin, input);
        
        if (input == "Q" || input == "q")
            return InputRequest::quitProcessing;
        
        processInput (input);
    
        return InputRequest::continueProcessing;
    }

private:

    void processInput(std::string input) const
    {
        std::cout << std::setprecision(7);
        // input is tokenised
        if (auto tokens = Tokeniser().tokenise(input))
            // calculations are run on the tokens received from tokenise
            std::cout << "Answer: " << Calculator().calculate(*tokens) << std::endl;
        else
            std::cout << "There was an error in the input string, please try again..." << std::endl;
    }
};

class ResultChecker
{
public:

    static void check(double value, double expected, double range = 1e-3)
    {
        // checking whether result of operation and expected answer are within range
        std::cout << "Value : " << value << "; Expected: " << expected << "; Abs: " << std::abs(value-expected) << std::endl;
        return assert (std::abs(value - expected) <= range);
    }
};

void test()
{
    auto result = Tokeniser().tokenise("6*9");
    assert (result.has_value());
    ResultChecker::check(result->lhs, 6);
    ResultChecker::check(result->rhs, 9);
    assert (result->type == Tokeniser::Type::multiply);
    
    result = Tokeniser().tokenise("6 * 9");
    assert (result.has_value());
    ResultChecker::check(result->lhs, 6);
    ResultChecker::check(result->rhs, 9);
    assert (result->type == Tokeniser::Type::multiply);
    
    result = Tokeniser().tokenise("25 * 4");
    assert (result.has_value ());
    ResultChecker::check(result->lhs, 25);
    ResultChecker::check(result->rhs, 4);
    assert (result->type == Tokeniser::Type::multiply);

    ResultChecker::check(Calculator().calculate({ 10, 4, Tokeniser::Type::multiply }), 40);
    ResultChecker::check(Calculator().calculate({ 25.3, 18.6, Tokeniser::Type::add }), 43.9);
    ResultChecker::check(Calculator().calculate({ 3, 5.6, Tokeniser::Type::subtract }), -2.6); // expected result of: 3 - 5.6 = -2.6
}

void run()
{
    // Create processoer
    InputProcessor processor;
    // Continue running while requestInput returns continueProcessing
    while (processor.requestInput() == InputProcessor::InputRequest::continueProcessing);
}

int main(int argc, const char * argv[])
{
    if (argc > 1 && std::string (argv[1]) == "--test")
        test();
    else
        run();
    
    return 0;
}
