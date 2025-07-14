#include <stdio.h>
#include <string.h>
#include <ctype.h>  // REMEBER TO BYHEART

char line[100];

int is_identifier(char token[])
{
    if (strlen(token) == 0)
        return 0;

    // let or _
    if (!(isalpha(token[0]) || token[0] == '_'))
        return 0;

    // is valid
    for (int i = 1; i < strlen(token); i++)
    {
        if (!(isalnum(token[i]) || token[i] == '_'))
            return 0;
    }
    return 1;
}

int is_number(char token[])
{
    int isflt = 0;

    if (strlen(token) == 0)
        return 0;

    for (int i = 0; i < strlen(token); i++)
    {
        if (token[i] == '.')
        {
            // No 2 dots
            if (isflt)
                return 0;
            isflt = 1;
        }
        else if (!isdigit(token[i]))
        {
            return 0;
        }
    }

    return 1;  // It's a valid number
}

int is_operator(char c)
{
    char wrd[10];
    switch (c)
    {
        case '+':   
        case '-':   
        case '*':   
        case '/':   
        case '=':   
            printf("%c - Operator\n", c);
            return 1;
    }

    return 0;
}

int is_delimiter(char c)
{
    switch (c)
    {
        case '{':
        case '}':
        case '(':
        case ')':
        case '[':
        case ']':
        case ',':
        case ';':
            printf("%c - Delimiter\n", c);
            return 1;
    }

    return 0;
}

int is_keyword(char token[])
{
    if (strcmp(token, "void") == 0 || strcmp(token, "main") == 0 ||
        strcmp(token, "int") == 0 || strcmp(token, "long") == 0 ||
        strcmp(token, "float") == 0 || strcmp(token, "double") == 0)
    { 
        return 1;
    }

    return 0;
}

void main()
{
    char c;
    FILE *f = fopen("input.txt", "r");

    while (fgets(line, sizeof(line), f))
    {
        // Single line commment '//', skip processing it
        int flag1 = 0;
        for (int i = 0; i < strlen(line); i++)
        {
            if (line[i] == '/' && line[i + 1] == '/')
            {
                flag1 = 1;
                break;
            }       
        }
        if (flag1)
            continue;        

        // Multi-line comment '/**/'
        int flag2 = 0;
        for (int i = 0; i < strlen(line); i++)
        {
            if (line[i] == '/' && line[i + 1] == '*')
            {
                // Skip all lines until '*/' has occured
                while (fgets(line, sizeof(line), f))
                {
                    for (int j = 0; j < strlen(line); j++)
                    {
                        if (line[j] == '*' && line[j + 1] == '/')
                            flag2 = 1;
                    }

                    if (flag2)
                        break;
                }
            }
        }
        if (flag2)
            continue;

        printf("\n%s\n", line);

        char token[100];
        int index = 0;
        strcpy(token, "");

        for (int i = 0; i < strlen(line); i++)
	{
	    if (is_operator(line[i]) || is_delimiter(line[i]) || line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
	    {
		// Check if the token is a number, keyword, or identifier
		if (strcmp(token, "") != 0)
		{
		    if (is_keyword(token))
		        printf("%s - Keyword\n", token);
		    else if (is_number(token))
		        printf("%s - Number\n", token);
		    else if (is_identifier(token))
		        printf("%s - Identifier\n", token);
		    else
		        printf("%s - Invalid Identifier\n", token);

		    strcpy(token, "");
		    index = 0;
		}
	    }
	    else
	    {
		token[index++] = line[i];
		token[index] = '\0';
	    }
	}
    }

    fclose(f);
}
