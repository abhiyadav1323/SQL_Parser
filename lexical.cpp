#include <bits/stdc++.h>
#include "ass2.h"

using namespace std;

#define MAX 100000

extern void parse(void);

vector<pair<int,string> > tokens;

const char *sql_keywords[] = {"add", "all", "alter", "and", "by", "between", "char", "column", "create", "decimal", 
"delete", "distinct", "double", "drop", "foreign", "from", "in", "insert", "int", "into", "key", "not", "null", "or", 
"primary", "references", "select", "set", "table", "unique", "update", "values", "varchar", "where", NULL};

map<string,int> dict = {
	make_pair("or", 1),
	make_pair("and", 2),
	make_pair("not", 3),
	make_pair("add", 4),
	make_pair("all", 5),
	make_pair("alter", 6),
	make_pair("between", 7),
	make_pair("by", 8),
	make_pair("char", 9),
	make_pair("column", 10),
	make_pair("create", 11),
	make_pair("decimal", 12),
	make_pair("delete", 13),
	make_pair("distinct", 14),
	make_pair("double", 15),
	make_pair("drop", 16),
	make_pair("foreign", 17),
	make_pair("from", 18),
	make_pair("in", 19),
	make_pair("insert", 20),
	make_pair("int", 21),
	make_pair("into", 22),
	make_pair("key", 23),
	make_pair("null", 24),
	make_pair("primary", 25),
	make_pair("references", 26),
	make_pair("select", 27),
	make_pair("set", 28),
	make_pair("table", 29),
	make_pair("unique", 30),
	make_pair("update", 31),
	make_pair("values", 32),
	make_pair("varchar", 33),
	make_pair("where", 34)
};



const char delim[] = {' ', '\t', '\n', '\r', '\0'};
const char operators[] = {'<','>','.','\0'};
const char left_bracket = '(';
const char right_bracket = ')';
const char comma = ',';
const char semi_colon = ';';
const char plus_sign = '+';
const char minus_sign = '-';
const char star = '*';
const char slash = '/';
const char equal_sign = '=';
const char gt = '>';
const char lt = '<';

void print_char_error(char token, int query_count)
{
	printf("Error found in < %c > in line no. %d.\n", token, query_count);
}

void print_str_error(char *token, int query_count)
{
	printf("Error found in < %s > in line no. %d.\n", token, query_count);
}

bool is_ident(char ch)
{
	if(isalpha(ch)||isdigit(ch)||ch=='_'||ch=='.')
		return true;
	return false;
}

bool is_delimeter(char ch)
{
	int i=0;
	for(i=0;delim[i];i++)
		if(delim[i] == ch)
			return true;
	return false;
}

int is_keyword(char *token)
{
	int i;
	for(i=0;sql_keywords[i];i++)
	{
		if(!strcmp(token,sql_keywords[i]))
		{
			string temp(token,token + strlen(token));
			return dict[token];
		}
	}
	return 0;
}

bool is_identifier(char *token)
{
	int i,c=0;
	int f=0;
	if(!isalpha(token[0])&&token[0]!='_')
		return false;
	for(i=0;token[i];i++)
	{
		if(token[i]=='.')
		{
			c++;
			if(c==1)
			{
				if(!token[i+1]||(!isalpha(token[i+1]) && token[i+1]!='_'))
					f=1;
			}
		}
	}
	if(c>1||f)
		return false;
	return true;
}

bool is_num(char *token)
{
	int i,c=0;
	for(i=0;token[i];i++)
	{
		if(isdigit(token[i]) || token[i]=='.')
		{
			if(token[i]=='.')
				c++;
		}
		else
			return false;
	}
	if(c>1)
		return false;
	return true;
}

void error(char *token, int len, int *query_count)
{
	char ch;
	ch = getc(stdin);
	while(ch!=EOF&&ch!=';')
	{
		token[len++] = ch;
		ch = getc(stdin);
	}
	if(ch==';')
	{
		token[len++] = ch;
		token[len] = '\0';
		print_str_error(token, *query_count);
		(*query_count)++;
	}
	else
	{
		token[len] = '\0';
		print_str_error(token, *query_count);
		(*query_count)++;
	}
}

void lexical()
{
	char ch;
	int query_count = 1;
	int tok_cnt;
	string tok;
	ch = getc(stdin);
	while(ch != EOF)
	{
		if(ch == left_bracket)
		{
			tok.clear();
			tok.push_back(ch);
			tokens.push_back(make_pair(LEFT_BRACKET,tok));
		}		
		else if(ch == right_bracket)
		{
			tok.clear();
			tok.push_back(ch);
			tokens.push_back(make_pair(RIGHT_BRACKET,tok));
		}
		else if(ch == comma)
		{
			tok.clear();
			tok.push_back(ch);
			tokens.push_back(make_pair(COMMA,tok));
		}
		else if(ch == semi_colon)
		{
			tok.clear();
			tok.push_back(ch);
			tokens.push_back(make_pair(SEMICOLON,tok));
			query_count++;
			
			parse();
			
			tokens.clear();
		}
		else if(is_ident(ch))
		{
			char *token = (char *)malloc(MAX*sizeof(char));
			char *token_copy = (char *)malloc(MAX*sizeof(char));
			int len=0;	
			while(is_ident(ch))
			{
				token[len] = tolower(ch);
				token_copy[len] = ch;
				len++;
				ch = getc(stdin);
			}
			ungetc(ch,stdin);
			token[len] = token_copy[len] = '\0';
			
			if((tok_cnt=is_keyword(token))!=0)
			{
				tok.clear();
				tok.assign(token_copy,token_copy+len);
				tokens.push_back(make_pair(tok_cnt,tok));
			}
			else if(is_identifier(token))
			{
				tok.clear();
				tok.assign(token_copy,token_copy+len);
				tokens.push_back(make_pair(IDENTIFIER,tok));
			}
			else if(is_num(token))
			{
				tok.clear();
				tok.assign(token_copy,token_copy+len);
				tokens.push_back(make_pair(NUMBER,tok));
			}
			else 
			{
				error(token_copy,len,&query_count);
				tokens.clear();
			}
			free(token_copy);
			free(token);
		}
		else if(ch == gt||ch == lt)
		{
			char ch_new = getc(stdin);
			if((ch_new == equal_sign) || (ch == lt && ch_new == gt))
			{
				tok.clear();
				tok.push_back(ch);
				tok.push_back(ch_new);
				tokens.push_back(make_pair(OPERATOR,tok));
			}	
			else
			{
				ungetc(ch_new,stdin);
				tok.clear();
				tok.push_back(ch);
				tokens.push_back(make_pair(OPERATOR,tok));
			}
		}
		else if(ch == equal_sign)
		{
			tok.clear();
			tok.push_back(ch);
			tokens.push_back(make_pair(EQUAL,tok));
		}
		else if(ch == plus_sign)
		{
			tok.clear();
			tok.push_back(ch);
			tokens.push_back(make_pair(PLUS,tok));
		}
		else if(ch == minus_sign)
		{
			tok.clear();
			tok.push_back(ch);
			tokens.push_back(make_pair(MINUS,tok));
		}
		else if(ch == star)
		{
			tok.clear();
			tok.push_back(ch);
			tokens.push_back(make_pair(STAR,tok));
		}
		else if(ch == slash)
		{
			tok.clear();
			tok.push_back(ch);
			tokens.push_back(make_pair(SLASH,tok));
		}
		else if(ch=='"')
		{
			char *token = (char *)malloc(MAX*sizeof(char));
			int len = 0;
			token[len++] = ch;
			ch = getc(stdin);
			while(ch!='"'&&ch!=EOF)
			{
				token[len++] = ch;
				ch = getc(stdin);
			}
			if(ch==EOF)
			{
				token[len] = '\0';
				print_str_error(token,query_count);
				query_count++;
				tokens.clear();
			}
			else
			{
				token[len++] = ch;
				token[len] = '\0';
				tok.clear();
				tok.assign(token,token+len);
				tokens.push_back(make_pair(STRING,tok));
			}
			free(token);
		}
		else if(ch=='\'')
		{
			char *token = (char *)malloc(MAX*sizeof(char));
			int len = 0;
			token[len++] = ch;
			ch = getc(stdin);
			while(ch!='\''&&ch!=EOF)
			{
				token[len++] = ch;
				ch = getc(stdin);
			}
			if(ch==EOF)
			{
				token[len] = '\0';
				print_str_error(token,query_count);
				(query_count)++;
				tokens.clear();
			}
			else
			{
				token[len++] = ch;
				token[len] = '\0';
				tok.clear();
				tok.assign(token,token+len);
				tokens.push_back(make_pair(STRING,tok));
			}
			free(token);
		}
		else if(is_delimeter(ch))
		{

		}
		else
		{
			char *token = (char *)malloc(MAX*sizeof(char));
			int len = 0;
			ungetc(ch,stdin);
			error(token,len,&query_count);
			free(token); 			
			tokens.clear();
		}
		ch = getc(stdin);
	}
}  
