#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

int precedence(char op)
{
    switch (op)
    {
    case '^':
        return 3;
    case '*':
    case '/':
    case '%':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == string::npos || last == string::npos)
        return ""; // If the string contains only whitespace characters
    return str.substr(first, last - first + 1);
}

string convertInfixIntoPostfix(string infixExp)
{
    infixExp = trim(infixExp); // trimming, i.e. removing white-spaces from both left and right sides

    stack<char> operatorStack;

    string postfixExp = "";
    operatorStack.push('(');
    infixExp += ")";

    for (int i = 0; i < infixExp.length(); i++)
    {
        char c = infixExp[i]; // current character
        if (isspace(c))
            continue;
        else if (isalpha(c))
        { // checking whether c is an alphabet or not
            postfixExp += c;
            postfixExp += " ";
        }
        else if (isdigit(c)) // checking whether c is a number or not
        {
            string number = "";
            number += c;
            while (i < infixExp.length() && isdigit(infixExp[i + 1]))
            { // for multi-digit numbers
                number += infixExp[i + 1];
                i++;
            }
            postfixExp += number;
            postfixExp += " ";
        }
        else if (c == '(')
            operatorStack.push(c);
        else if (isOperator(c))
        {
            if (c == '-' && (i == 0 || infixExp[i - 1] == '(')) // Handling negative operands
            {
                operatorStack.push(c);
                continue;
            }
            while (!operatorStack.empty() && operatorStack.top() != '(' && precedence(operatorStack.top()) >= precedence(c))
            {
                postfixExp += operatorStack.top();
                postfixExp += " ";
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
        else if (c == ')')
        {
            while (!operatorStack.empty() && operatorStack.top() != '(')
            {
                postfixExp += operatorStack.top();
                postfixExp += " ";
                operatorStack.pop();
            }
            if (!operatorStack.empty())
                operatorStack.pop();
        }
    }
    return postfixExp;
}

bool validateInfix(string infixExp)
{
    infixExp = trim(infixExp); // trimming, i.e. removing white-spaces from both left and right sides
    if (infixExp.empty())
        return false;

    bool previousCharWasOperator = false;
    bool previousCharWasOpeningBracket = false;

    stack<char> parentheses; // for checking proper parentheses opening and closings

    for (int i = 0; i < infixExp.length(); i++)
    {
        char currentChar = infixExp[i];

        if (isspace(currentChar))
            continue;
        else if (isalnum(currentChar))
        { // operand
            previousCharWasOperator = false;
            previousCharWasOpeningBracket = false;

            if (isalpha(currentChar))
            {
                if (i + 1 < infixExp.length() && isalpha(infixExp[i + 1]))
                    return false; // as one operand is not seperated by another
            }
            else // isdigit
            {
                while (i < infixExp.length() && isdigit(infixExp[i + 1])) // for muti-digit number
                    i++;
            }
        }
        else if (currentChar == '(')
        {
            parentheses.push(currentChar);
            previousCharWasOpeningBracket = true;
        }
        else if (currentChar == ')')
        {
            if (parentheses.empty()) // closing parentheses without an opening bracket
                return false;
            else if ((currentChar == ')' && parentheses.top() == '('))
                parentheses.pop();
            else
                return false; // Mismatched parentheses, wrong order/arrangement of parentheses
        }
        else if (currentChar == '-' && (i == 0 || infixExp[i - 1] == '(')) // for handling negative operands
            continue;                                                      // Will handle it in convertInfixIntoPostfix(), if exp is valid
        else if (isOperator(currentChar))
        {
            if (previousCharWasOperator)
                return false;               // Two operators in a row
            previousCharWasOperator = true; // We expect an operand next
        }
        else
            return false; // Invalid character
    }

    return parentheses.empty() && !previousCharWasOperator; // the expression is invalid if there's unmatched parentheses or it ends with an operator
}

int main()
{
    string infixExp = ""; // infix expression
    cout << "Enter an infix-expression: ";
    getline(cin, infixExp);

    if (validateInfix(infixExp))
    {
        string postfixExp = convertInfixIntoPostfix(infixExp);
        cout << infixExp << " in postfix form: " << postfixExp << endl;
    }
    else
        cout << "Invalid input! Kindly enter an infix expression.\n";

    return 0;
}