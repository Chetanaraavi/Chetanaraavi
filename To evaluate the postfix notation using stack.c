#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50

int stack[MAX];
int top = -1;

int pop()
{
    if (top == -1)
    {
        printf("\nStack is empty !!\n");
        return -1;
    }
    else
        return stack[top--];
}

void push(int x)
{
    if (top == MAX - 1)
    {
        printf("\nStack is full !!!\n");
    }
    else
    {
        stack[++top] = x;
    }
}

bool check_operator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
}

int evaluating(char expr[])
{
    int item1, item2;

    for (int i = 0; expr[i] != '\0'; i++)
    {
        if (check_operator(expr[i]))
        {
            item1 = pop();
            item2 = pop();

            switch (expr[i])
            {
                case '+':
                    push(item2 + item1);
                    break;
                case '-':
                    push(item2 - item1);
                    break;
                case '*':
                    push(item2 * item1);
                    break;
                case '/':
                    if (item1 == 0)
                    {
                        printf("Division by zero error!\n");
                        return -1;
                    }
                    push(item2 / item1);
                    break;
                case '%':
                    if (item1 == 0)
                    {
                        printf("Modulo by zero error!\n");
                        return -1;
                    }
                    push(item2 % item1);
                    break;
                default:
                    printf("Invalid Statement !!\n");
                    return -1;
            }
        }
        else
            push(expr[i] - '0');
    }

    return pop();
}

int main()
{
    char expr[50];

    printf("Enter a postfix expression: ");
    scanf("%s", expr);

    int result = evaluating(expr);
    if (result != -1)
    {
        printf("The answer for the postfix expression is: %d\n", result);
    }

    return 0;
}
