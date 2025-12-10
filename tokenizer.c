/* 负责分割命令 */
#include "include/dict.h"
#include "include/parse.h"
#include "include/bin.h"

#define TOK ' '
#define END ';'
#define QOT '\"'

// Token 定义
typedef enum
{
    Identifier = 0,
    Text,
    Number,
    Operator,
    Word,
    Start,
    End,
    VeryEnd,
    SB
} Token_Type;

typedef struct
{
    Token_Type type;
    double     number;
    int        bool;
    char      *string;
    char      *raw
} Token;

// 懒
int eq(const char *str1, const char *str2)
{
    if(strcmp(str1, str2) == 0)
        return 1;
    else
        return 0;
}
int size_of_raw = 0;
void clear(char *tmp)
{
    memset(tmp, 0, size_of_raw);
}

// 比较是否同类
int similar(Token token1, Token token2)
{
    return token1.type == token2.type;
}

// 比较是否是同一个
int same(Token token1, Token token2)
{
    return (token1.type == token2.type) && eq(token1.raw, token2.raw);
}

const Token error_token = { SB };

Bin *token_bin;

// 别忘了管理垃圾桶
Token *tokenize(const char *line)
{
    token_bin = bin_create();
    char *raw = parse(line);
    int quote_on = 0;

    // ...    

    for(int i=0, k=0; i<strlen(raw); i++)
    {
        char ch = raw[i];
        char *tmp = calloc(strlen(raw)+1, sizeof(char));
        tmp[strlen(raw)] = '\0';
        size_of_raw = strlen(raw);
        //char **parts = calloc(strlen(raw)/2, sizeof(char));
        bin_drop(token_bin, tmp);

        /* 示例指令
         * print "wow" ; input ; print "end input" ;
        */

        tmp[k] = raw[i];
        if(ch = QOT) quote_on = !quote_on;

        


        
    }
    bin_empty(token_bin);
}