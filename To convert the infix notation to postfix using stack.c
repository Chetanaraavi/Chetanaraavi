#include <stdio.h>
#include <stdbool.h>

#define max 100

char stack[max];

int top = -1;

void push(char x)
{
    if (top == max - 1)
    {
        printf("overflow");
    }
    else
    {
        stack[++top] = x;
    }
}

int precedence(char ch)
{
    if (ch == '+' || ch == '-')
    {
        return 1;
    }
    if (ch == '/' || ch == '*')
    {
        return 2;
    }
    if (ch == '^')
    {
        return 3;
    }
    else
    {
        return -1;
    }
}

char peek()
{
    if (top == -1)
    {
        printf("Underflow");
    }
    else
    {
        return stack[top];
    }
}

char pop()
{
    if (top == -1)
    {
        printf("Underflow");
    }
    else
    {
        return stack[top--];
    }
}

bool check_operator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void expression(char expr[])
{

    for (int i = 0; expr[i] != '\0'; i++)
    {
        if (expr[i] == '(')
        {
            push(expr[i]);
        }
        else if (expr[i] == ')')
        {
            while (stack[top] != '(')
            {
                printf("%c", pop());
            }
            pop();
        }
        else
        {
            if (check_operator(expr[i]))
            {
                while (top != -1 && precedence(peek()) >= precedence(expr[i]))
                {
                    printf("%c", pop());
                }
                push(expr[i]);
            }
            else
            {
                printf("%c", expr[i]);
            }
        }
    }
    
    while (top != -1)
    {
        printf("%c", pop());
    }
}

int main()
{

    char expr[20];
    printf("Enter the expression : ");
    scanf("%s", expr);

    printf("\nThe Postfix expression is : ");
    expression(expr);
}
