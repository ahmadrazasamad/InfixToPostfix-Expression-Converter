# Infix to Postfix Expression Converter
This project implements a C++ program that converts an infix expression into its corresponding postfix notation. The program ensures that the input infix expression is valid before conversion and handles different scenarios, including multi-digit numbers, negative operands, and proper operator precedence.
## Features
- <b>Infix Expression Validation:</b> The program checks the validity of the infix expression, ensuring proper use of parentheses, operators, and operands.
- <b>Operator Precedence Handling:</b> The program considers the precedence of operators ('^', '*', '/', '%', '+', '-') while converting the expression.
- <b>Support for Multi-digit Numbers:</b> The program can handle multi-digit numbers within the expression.
- <b>Handling Negative Operands:</b> The program supports negative numbers by correctly interpreting and converting them into postfix form.
## Usage
1. <b>Input:</b> The program prompts the user to input a valid infix expression. The expression can include:
- Operands (letters and digits)
- Operators (+, -, *, /, %, ^)
- Parentheses for grouping
2. <b>Validation:</b> The program first validates the infix expression to check for any errors.
3. <b>Conversion:</b> If the expression is valid, it converts the infix expression into postfix notation.
4. <b>Output:</b> The converted postfix expression is displayed.
## Example
Input:
```
A * (B + C) / D
```
Output:
```
A B C + * D /
```
## Contributing
Contributions are welcome! If you find any issues or want to enhance the functionality, feel free to create a pull request.
