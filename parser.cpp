//Defining the header files used in ass2.h and including that file 

#include <bits/stdc++.h>
#include "ass2.h"

using namespace std;

//Defining Macros

#define MAX 100000		//maximum length of productions
#define F first			//macro for first half of a pair
#define S second		//macro for second half of a pair


//external variables to be used across files 
extern void lexical(void);
extern vector<pair<int,string> > tokens;
extern vector<string> tree;

//utility structure to print the productions as the parse tree
struct sent 
{
	string name;
	int sz;
	struct sent *nxt[20];
};

//utility functions used as the non-terminals in the productions 
bool expression(struct sent *&t);
bool expressions(struct sent *&t);
bool where_condition(struct sent *&t);
bool where_conditions(struct sent *&t);
bool optional_where(struct sent *&t);


int ptr;		//to save temporary pointer
string log_msg;		// string to save log message

bool semicolon(struct sent* &t)
{
	t = new sent;
	if(tokens[ptr].F == SEMICOLON)
	{
		/* This part of code for all the nonterminals id to print the productions as the parse tree */	


		t->name = "SEMICOLON";
		t->sz = 0;
		return 1;
	}
	return 0;
}

bool id(struct sent* &t)
{
	int save_ptr = ptr;
	t = new sent;
	if(tokens[ptr++].F == IDENTIFIER)
	{
		t->name = "IDENTIFIER";
		t->sz = 1;
		t->nxt[0] = new sent;
		t->nxt[0]->name = tokens[ptr-1].S;
		t->nxt[0]->sz = 0;
		return 1;
	}

	ptr = save_ptr;

	/*if id is not matched with a valid identifier i.e. first part of the token , the second part of the pair token contains the expected IDENTIFIER */
	log_msg = "Next expected token is IDENTIFIER in place of " + tokens[ptr].S;
	return 0;
}

bool equal_sign(struct sent* &t)
{
	int save_ptr = ptr;
	t = new sent;
	if(tokens[ptr++].F == EQUAL)
	{
		t->name = "EQUAL";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is EQUAL in place of " + tokens[ptr].S;
	return 0;	
}

bool select(struct sent* &t)
{
	int save_ptr = ptr;
	t = new sent;
	if(tokens[ptr++].F == SELECT){
		t->name = "SELECT";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is SELECT in place of " + tokens[ptr].S;
	
	return 0;
}

bool oprator(struct sent* &t)
{
	int save_ptr = ptr;
	t = new sent;
	if(tokens[ptr++].F == OPERATOR)
	{
		t->name = "OPERATOR";
		t->sz = 1;
		t->nxt[0] = new sent;
		t->nxt[0]->name = tokens[ptr-1].S;
		t->nxt[0]->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is OPERATOR in place of " + tokens[ptr].S;
	return 0;
}

bool table(struct sent* &t)
{
	int save_ptr = ptr;
	t = new sent;
	if(tokens[ptr++].F == TABLE)
	{
		t->name = "TABLE";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is TABLE in place of " + tokens[ptr].S;
	return 0;
}

bool between(struct sent* &t)
{
	int save_ptr = ptr;
	t = new sent;
	if(tokens[ptr++].F == BETWEEN){
		t->name = "BETWEEN";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is BETWEEN in place of " + tokens[ptr].S;
	
	return 0;
}

bool in(struct sent *&t)
{
	int save_ptr = ptr;
	t = new sent;
	if(tokens[ptr++].F == IN){
		t->name = "IN";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is IN in place of " + tokens[ptr].S;
	
	return 0;
}

bool drop(struct sent* &t)
{
	int save_ptr = ptr;
	t = new sent;
	if(tokens[ptr++].F == DROP){
		t->name = "DROP";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is DROP in place of " + tokens[ptr].S;
	
	return 0;
}

bool andx(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == AND){
		t->name = "AND";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is AND in place of " + tokens[ptr].S;
	
	return 0;
}

bool orx(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == OR){
		t->name = "OR";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is OR in place of " + tokens[ptr].S;
	
	return 0;
}

bool add(struct sent *&t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == ADD){
		t->name = "ADD";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is ADD in place of " + tokens[ptr].S;
	
	return 0;
}

bool column(struct sent *&t)
{
	t =new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == COLUMN){
		t->name = "COLUMN";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is COLUMN in place of " + tokens[ptr].S;
	
	return 0;
}

bool character(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == CHAR){
		t->name = "CHAR";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is CHAR in place of " + tokens[ptr].S;
	
	return 0;
}

bool left_br(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == LEFT_BRACKET){
		t->name = "LEFT_BRACKET";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is LEFT_BRACKET in place of " + tokens[ptr].S;
	
	return 0;
}

bool right_br(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == RIGHT_BRACKET){
		t->name = "RIGHT_BRACKET";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is RIGHT_BRACKET in place of " + tokens[ptr].S;
	
	return 0;
}

bool number(struct sent * &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == NUMBER){
		t->name = "NUMBER";
		t->sz = 1;
		t->nxt[0] = new sent;
		t->nxt[0]->name = tokens[ptr-1].S;
		t->nxt[0]->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is NUMBER in place of " + tokens[ptr].S;
	
	return 0;
}

bool varchar(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == VARCHAR){
		t->name = "VARCHAR";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is VARCHAR in place of " + tokens[ptr].S;
	
	return 0;
}

bool decimal(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == DECIMAL){
		t->name = "DECIMAL";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is DECIMAL in place of " + tokens[ptr].S;
	
	return 0;
}

bool integer(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == INT){
		t->name = "INT";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is INT in place of " + tokens[ptr].S;
	
	return 0;
}

bool into(struct sent * &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == INTO){
		t->name = "INTO";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is INTO in place of " + tokens[ptr].S;
	
	return 0;	
}

bool no(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == NOT){
		t->name = "NOT";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is NOT in place of " + tokens[ptr].S;
	
	return 0;	
}

bool comma(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == COMMA){
		t->name = "COMMA";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is COMMA in place of " + tokens[ptr].S;
	
	return 0;
}


bool null(struct sent * &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == NUL){
		t->name = "NULL";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is NULL in place of " + tokens[ptr].S;
	
	return 0;
}

bool values(struct sent * &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == VALUES){
		t->name = "VALUES";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is VALUES in place of " + tokens[ptr].S;
	
	return 0;
}

bool unique(struct sent * &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == UNIQUE){
		t->name = "UNIQUE";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is UNIQUE in place of " + tokens[ptr].S;
	
	return 0;
}

bool all(struct sent * &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == ALL){
		t->name = "ALL";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is ALL in place of " + tokens[ptr].S;
	
	return 0;
}

bool distinct(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == DISTINCT){
		t->name = "DISTINCT";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is DISTINCT in place of " + tokens[ptr].S;
	
	return 0;
}

bool from(struct sent *&t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == FROM){
		t->name = "FROM";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is FROM in place of " + tokens[ptr].S;
	
	return 0;
}

bool plus_sign(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == PLUS){
		t->name = "PLUS";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is PLUS in place of " + tokens[ptr].S;
	
	return 0;
}

bool minus_sign(struct sent *&t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == MINUS){
		t->name = "MINUS";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is MINUS in place of " + tokens[ptr].S;
	
	return 0;
}

bool star(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == STAR){
		t->name = "STAR";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is STAR in place of " + tokens[ptr].S;
	
	return 0;
}

bool slash(struct sent * &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == SLASH){
		t->name = "SLASH";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is SLASH in place of " + tokens[ptr].S;
	
	return 0;
}

bool primary(struct sent *&t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == PRIMARY)
	{
		t->name = "PRIMARY";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is PRIMARY in place of " + tokens[ptr].S;
	
	return 0;
}

bool where(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == WHERE){
		t->name = "WHERE";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is WHERE in place of " + tokens[ptr].S;
	
	return 0;
}

bool setx(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == SET){
		t->name = "SET";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is SET in place of " + tokens[ptr].S;
	
	return 0;	
}

bool key(struct sent *&t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == KEY){
		t->name = "KEY";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is KEY in place of " + tokens[ptr].S;
	
	return 0;
}

bool strng(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == STRING){
		t->name = "STRING";
		t->sz = 1;
		t->nxt[0] = new sent;
		t->nxt[0]->name = tokens[ptr-1].S;
		t->nxt[0]->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is STRING in place of " + tokens[ptr].S;
	
	return 0;	
}

bool references(struct sent * &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == REFERENCES){
		t->name = "REFERENCES";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is REFERENCES in place of " + tokens[ptr].S;
	
	return 0;
}

bool doble(struct sent* &t)
{
	t = new sent;
	int save_ptr = ptr;
	if(tokens[ptr++].F == DOUBLE){
		t->name = "DOUBLE";
		t->sz = 0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is DOUBLE in place of " + tokens[ptr].S;
	
	return 0;
}
/*
Taking care of character,varchar,decimal,integer and double in the column types
*/

bool coln_type(struct sent *&t)
{
	t = new sent;
	int save_ptr = ptr;
	struct sent *t0,*t1,*t2,*t3,*t4;
	t->name = "coln_type";
	if(character(t0))
	{
		if(left_br(t1)&&number(t2)&&right_br(t3)){
			t->sz = 4;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	if(varchar(t0))
	{
		if(left_br(t1)&&number(t2)&&right_br(t3)){
			t->sz = 4;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			return 1;
		}
		ptr = save_ptr;
		return 0;	
	}
	ptr = save_ptr;
	if(decimal(t0))
	{
		if(left_br(t1)&&number(t2)&&right_br(t3)){
			t->sz = 4;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	if(integer(t0)){
		t->sz = 1;
		t->nxt[0] = t0;
		return 1;
	}
	ptr = save_ptr;
	if(doble(t0)){
		t->sz = 1;
		t->nxt[0] = t0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is column_type in place of " + tokens[ptr].S;
	
	return 0;
}

/*
 recursively takes care of the list of variables seperated by COMMA
 */

bool variables(struct sent *&t)
{
	t = new sent;
	t->name = "variables";
	struct sent *t0,*t1,*t2;
	int save_ptr = ptr;
	if(id(t0))
	{
		save_ptr = ptr;
		if(comma(t1))
		{
			if(variables(t2))
			{
				t->sz = 3;
				t->nxt[0] = t0;
				t->nxt[1] = t1;
				t->nxt[2] = t2;
				return 1;
			}
			ptr = save_ptr;
			return 0;
		}
		ptr = save_ptr;	
		t->sz = 1;
		t->nxt[0] = t0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is IDENTIFIER in place of " + tokens[ptr].S;
	
	return 0;
}

/*
To handle the types of columns constructors i.e. null,primary key,unique,foreign key
*/
bool coln_constr(struct sent * &t)
{
	t = new sent;
	t->name = "coln_constr";
	struct sent *t0,*t1,*t2,*t3,*t4;
	int save_ptr = ptr;
	if(no(t0))
	{
		int p = ptr;
		if(null(t1)&&primary(t2)&&key(t3)){
			t->sz = 4;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			return 1;
		}
		ptr = p;
		if(null(t1)&&unique(t2)){
			t->sz = 3;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			return 1;
		}
		ptr = p;
		if(null(t1)){
			t->sz = 2;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			return 1;
		}
		ptr = p;
		return 0;
	}
	ptr = save_ptr;
	if(references(t0))
	{
		if(id(t1)&&left_br(t2)&&variables(t3)&&right_br(t4)){
			t->sz = 5;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			t->nxt[4] = t4;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is NOT/REFERENCES in place of " + tokens[ptr].S;
	return 1;
}

bool drop_add(struct sent * &t)
{
	t = new sent;
	t->name = "drop_add";
	struct sent *t0,*t1,*t2,*t3;
	int save_ptr = ptr;
	if(drop(t0))
	{
		if(column(t1)&&id(t2)){
			t->sz = 3;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	if(add(t0))
	{
		if(id(t1)&&coln_type(t2)&&coln_constr(t3)){
			t->sz = 4;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is DROP/ADD in place of " + tokens[ptr].S;
	
	return 0;
}

bool table_column(struct sent * &t)
{
	t = new sent;
	t->name = "table_column";
	struct sent *t0,*t1,*t2;
	int save_ptr = ptr;
	if(id(t0))
	{
		if(coln_type(t1)&&coln_constr(t2)){
			t->sz = 3;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is IDENTIFIER in place of " + tokens[ptr].S;
	return 0;
}

bool table_columns(struct sent * &t)
{
	t = new sent;
	t->name = "table_columns";
	struct sent *t0,*t1,*t2;
	int save_ptr = ptr;
	if(table_column(t0))
	{
		save_ptr = ptr;
		if(comma(t1))
		{
			if(table_columns(t2))
			{
				t->sz = 3;
				t->nxt[0] = t0;
				t->nxt[1] = t1;
				t->nxt[2] = t2;
				return 1;
			}
			ptr = save_ptr;
			return 0;
		}
		ptr = save_ptr;	
		t->sz = 1;
		t->nxt[0] = t0;
		return 1;
	}
	ptr = save_ptr;
	return 0;
}

bool value(struct sent * &t)
{
	t = new sent;
	t->name = "value";
	struct sent *t0;
	int save_ptr = ptr;
	if(number(t0)){
		t->sz = 1;
		t->nxt[0] = t0;
		return 1;
	}
	ptr = save_ptr;
	if(strng(t0)){
		t->sz = 1;
		t->nxt[0] = t0;
		return 1;
	}
	ptr = save_ptr;
	if(null(t0)){
		t->sz = 1;
		t->nxt[0] = t0;
		return 1;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is value in place of " + tokens[ptr].S;
	return 0;
}

bool values_list(struct sent *&t)
{
	t = new sent;
	t->name = "values_list";
	struct sent *t0,*t1,*t2;
	int save_ptr = ptr;
	if(value(t0))
	{
		save_ptr = ptr;
		if(comma(t1))
		{
			if(values_list(t2))
			{
				t->sz = 3;
				t->nxt[0] = t0;
				t->nxt[1] = t1;
				t->nxt[2] = t2;
				return 1;
			}
			ptr = save_ptr;
			return 0;
		}
		ptr = save_ptr;
		t->sz = 1;
		t->nxt[0] = t0;	
		return 1;
	}
	ptr = save_ptr;
	return 0;
}

bool optional_attributes(struct sent * &t)
{
	t = new sent;
	t->name = "optional_attributes";
	struct sent *t0,*t1,*t2;
	int save_ptr = ptr;
	if(left_br(t0))
	{
		if(variables(t1)&&right_br(t2)){
			t->sz = 3;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	t->sz = 1;
	t->nxt[0] = new sent;
	t->nxt[0]->name = "epsilon";
	t->nxt[0]->sz = 0;
	return 1;
}

bool optional_distinct(struct sent *&t)
{
	t = new sent;
	t->name = "optional_distinct";
	struct sent *t0;
	int save_ptr = ptr;
	if(all(t0)){
		t->sz = 1;
		t->nxt[0] = t0;
		return 1;
	}
	ptr = save_ptr;
	if(distinct(t0)){
		t->sz = 1;
		t->nxt[0] = t0;
		return 1;
	}
	ptr = save_ptr;
	t->sz = 1;
	t->nxt[0] = new sent;
	t->nxt[0]->name = "epsilon";
	t->nxt[0]->sz = 0;
	return 1;
}

/*
recursively handles each individual expression i.e. + , -, *, /
*/
bool expression(struct sent * &t)
{
	t = new sent;
	t->name = "expression";
	struct sent *t0,*t1,*t2;
	int save_ptr = ptr;
	if(plus_sign(t0))
	{
		if(expressions(t1)&&expression(t2)){
			t->sz = 3;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	if(minus_sign(t0))
	{
		if(expressions(t1)&&expression(t2)){
			t->sz = 3;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	if(star(t0))
	{
		if(expressions(t1)&&expression(t2)){
			t->sz = 3;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	if(slash(t0))
	{
		if(expressions(t1)&&expression(t2)){
			t->sz = 3;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	t->sz = 1;
	t->nxt[0] = new sent;
	t->nxt[0]->name = "epsilon";
	t->nxt[0]->sz = 0;
	return 1;
}

bool expressions(struct sent* &t)
{
	t = new sent;
	t->name = "expressions";
	struct sent *t0,*t1,*t2,*t3;
	int save_ptr = ptr;
	if(left_br(t0))
	{
		if(expressions(t1)&&right_br(t2)&&expression(t3)){
			t->sz = 4;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	if(id(t0))
	{
		if(expression(t1)){
			t->sz = 2;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	if(number(t0))
	{
		if(expression(t1)){
			t->sz = 2;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	if(strng(t0))
	{
		if(expression(t1)){
			t->sz = 2;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is ID/NUM/STR in place of " + tokens[ptr].S;
	return 0;
}

bool variable_expressions(struct sent * &t)
{
	t = new sent;
	t->name = "variable_expressions";
	struct sent *t0,*t1,*t2;
	int save_ptr = ptr;
	if(expressions(t0))
	{
		save_ptr = ptr;
		if(comma(t1))
		{
			if(variable_expressions(t2))
			{
				t->sz = 3;
				t->nxt[0] = t0;
				t->nxt[1] = t1;
				t->nxt[2] = t2;
				return 1;
			}
			ptr = save_ptr;
			return 0;
		}
		ptr = save_ptr;
		t->sz = 1;
		t->nxt[0] = t0;	
		return 1;
	}
	ptr = save_ptr;
	return 0;
}

bool select_list(struct sent * &t)
{
	t = new sent;
	t->name ="select_list";
	struct sent *t0;
	int save_ptr = ptr;
	if(star(t0)){
		t->sz = 1;
			t->nxt[0] = t0;
		return 1;
	}
	ptr = save_ptr;
	if(variable_expressions(t0)){
		t->sz = 1;
			t->nxt[0] = t0;
		return 1;
	}
	ptr = save_ptr;
	return 0;
}

bool nested_query(struct sent * &t)
{
	t = new sent;
	t->name = "nested_query";
	struct sent *t0,*t1,*t2,*t3,*t4,*t5,*t6;
	int save_ptr = ptr;
	if(select(t0)&&optional_distinct(t1)&&select_list(t2)&&from(t3)&&variables(t4)&&optional_where(t5)){
		t->sz = 6;
		t->nxt[0] = t0;
		t->nxt[1] = t1;
		t->nxt[2] = t2;
		t->nxt[3] = t3;
		t->nxt[4] = t4;
		t->nxt[5] = t5;
		return 1;
	}
	ptr = save_ptr;
	return 0;
}

bool conditions(struct sent * &t)
{
	t = new sent;
	t->name = "conditions";
	struct sent *t0,*t1,*t2,*t3,*t4,*t5;
	int save_ptr = ptr;
	if(expressions(t0))
	{
		int p = ptr;
		if(oprator(t1))
		{
			int p1 = ptr;
			if(left_br(t2))
			{
				if(nested_query(t3)&&right_br(t4)){
					t->sz = 5;
					t->nxt[0] = t0;
					t->nxt[1] = t1;
					t->nxt[2] = t2;
					t->nxt[3] = t3;
					t->nxt[4] = t4;
					return 1;
				}
				ptr = p1;
				return 0;
			}
			ptr = p1;
			if(expressions(t2)){
				t->sz = 3;
				t->nxt[0] = t0;
				t->nxt[1] = t1;
				t->nxt[2] = t2;
				return 1;
			}
			ptr = p1;
			return 0;
		}
		ptr = p;
		if(equal_sign(t1))
		{
			int p1 = ptr;
			if(left_br(t2))
			{
				if(nested_query(t3)&&right_br(t4)){
					t->sz = 5;
					t->nxt[0] = t0;
					t->nxt[1] = t1;
					t->nxt[2] = t2;
					t->nxt[3] = t3;
					t->nxt[4] = t4;
					return 1;
				}
				ptr = p1;
				return 0;
			}
			ptr = p1;
			if(expressions(t2)){
				t->sz = 3;
				t->nxt[0] = t0;
				t->nxt[1] = t1;
				t->nxt[2] = t2;
				return 1;
			}
			ptr = p1;
			return 0;
		}
		ptr = p;
		if(between(t1))
		{
			if(expressions(t2)&&andx(t3)&&expressions(t4)){
				t->sz = 5;
				t->nxt[0] = t0;
				t->nxt[1] = t1;
				t->nxt[2] = t2;
				t->nxt[3] = t3;
				t->nxt[4] = t4;
				return 1;
			}
			ptr = p;
			return 0;
		}
		ptr = p;
		if(in(t1))
		{
			if(left_br(t2))
			{
				if(nested_query(t3)&&right_br(t4)){
					t->sz = 5;
					t->nxt[0] = t0;
					t->nxt[1] = t1;
					t->nxt[2] = t2;
					t->nxt[3] = t3;
					t->nxt[4] = t4;
					return 1;
				}
				ptr = p;
				return 0;
			}
			ptr = p;
			return 0;
		}
		ptr = p;
		if(no(t1))
		{
			int p1 = ptr;
			if(in(t2))
			{
				if(left_br(t3)&&nested_query(t4)&&right_br(t5)){
					t->sz = 6;
					t->nxt[0] = t0;
					t->nxt[1] = t1;
					t->nxt[2] = t2;
					t->nxt[3] = t3;
					t->nxt[4] = t4;
					t->nxt[5] = t5;
					return 1;
				}
				ptr = p1;
				return 0;
			}
			ptr = p1;
			if(between(t2))
			{
				if(expressions(t3)&&andx(t4)&&expressions(t5)){
					t->sz = 6;
					t->nxt[0] = t0;
					t->nxt[1] = t1;
					t->nxt[2] = t2;
					t->nxt[3] = t3;
					t->nxt[4] = t4;
					t->nxt[5] = t5;
					return 1;
				}
				ptr = p1;
				return 0;
			}
			ptr = p1;
			log_msg = "Next expected token is IN/BETWEEN in place of " + tokens[ptr].S;
			return 0;
		}
		ptr = p;
		log_msg = "Next expected token is OPERATOR in place of " + tokens[ptr].S;
		return 0;		
	}
	ptr = save_ptr;
	return 0;
}

bool where_condition(struct sent *&t)
{
	t = new sent;
	t->name= "where_condition";
	struct sent *t0,*t1,*t2,*t3;
	int save_ptr = ptr;
	if(andx(t0))
	{
		if(where_conditions(t1)&&where_condition(t2)){
			t->sz = 3;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	if(orx(t0))
	{
		if(where_conditions(t1)&&where_condition(t2)){
			t->sz = 3;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	log_msg = "Next expected token is AND/OR in place of " + tokens[ptr].S;
	t->sz = 1;
	t->nxt[0] = new sent;
	t->nxt[0]->name = "epsilon";
	t->nxt[0]->sz = 0;
	return 1;
}

bool where_conditions(struct sent * &t)
{
	t = new sent;
	t->name = "where_conditions";
	struct sent *t0,*t1,*t2,*t3;
	int save_ptr = ptr;
	if(left_br(t0))
	{
		if(where_conditions(t1)&&right_br(t2)&&where_condition(t3)){
			t->sz = 4;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	if(conditions(t0))
	{
		if(where_condition(t1)){
			t->sz = 2;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	t->sz = 1;
	t->nxt[0] = new sent;
	t->nxt[0]->name = "epsilon";
	t->nxt[0]->sz = 0;
	return 0;
}

bool optional_where(struct sent * &t)
{
	t = new sent;
	t->name = "optional_where";
	struct sent *t0,*t1,*t2;
	int save_ptr = ptr;
	if(where(t0))
	{
		if(where_conditions(t1)){
			t->sz = 2;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			return 1;
		}
		ptr = save_ptr;
		return 0;
	}
	ptr = save_ptr;
	t->sz = 1;
	t->nxt[0] = new sent;
	t->nxt[0]->name = "epsilon";
	t->nxt[0]->sz = 0;
	return 1;
}

bool key_value_pair(struct sent * &t)
{
	t = new sent;
	t->name = "key_value_pair";
	struct sent *t0,*t1,*t2;
	int save_ptr = ptr;
	if(id(t0)&&equal_sign(t1)&&value(t2))
	{
		t->sz = 3;
		t->nxt[0] = t0;
		t->nxt[1] = t1;
		t->nxt[2] = t2;
		return 1;
	}
	ptr = save_ptr;
	return 0;
}

bool key_value_pairs(struct sent * &t)
{
	t = new sent;
	t->name = "key_value_pairs";
	struct sent *t0,*t1,*t2,*t3;
	int save_ptr = ptr;
	if(key_value_pair(t0))
	{
		save_ptr = ptr;
		if(comma(t1))
		{
			if(key_value_pairs(t2))
			{
				t->sz = 3;
				t->nxt[0] = t0;
				t->nxt[1] = t1;
				t->nxt[2] = t2;
				return 1;
			}
			ptr = save_ptr;
			return 0;
		}
		ptr = save_ptr;
		t->sz = 1;
		t->nxt[0] = t0;	
		return 1;
	}
	ptr = save_ptr;
	return 0;
}


/*
Utility function to print the parse tree in the form of production steps in the order that they occur
*/
void print_tree(struct sent* &t,int cnt)
{
	// printf("\n");
	if(t->sz==0)
		return;
	for(int i=0;i<cnt;i++)
		printf("\t");
	cout << t->name << " ---> ";
	for(int i=0;i<(t->sz);i++)
	{
		cout << t->nxt[i]->name << " ";
	}
	cout << endl;
	for(int i=0;i<(t->sz);i++)
		print_tree(t->nxt[i],cnt+1);
}

/*
The primary function to decide the first production from the start symbol which is labelled as the sql_statement
*/
void parse()
{
	ptr = 0;
	struct sent *t = new sent;
	if(tokens[ptr].F == DROP)
	{
		ptr++;
		struct sent *t0,*t1,*t2,*t3;
		t0 = new sent;
		t0->name = "DROP";
		t0->sz = 0;
		if(table(t1)&&id(t2)&&semicolon(t3))
		{
			t->name = "sql_stmt";
			t->sz = 4;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			
			print_tree(t,0);
			return;
		}
		cout << log_msg << endl;
		return;
	}
	if(tokens[ptr].F == DELETE)
	{
		ptr++;
		struct sent *t0,*t1,*t2,*t3,*t4;
		t0 = new sent;
		t0->name = "DELETE";
		t0->sz = 0;
		if(from(t1)&&id(t2)&&optional_where(t3)&&semicolon(t4))
		{
			t->name = "sql_stmt";
			t->sz = 5;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			t->nxt[4] = t4;
			print_tree(t,0);
			return ;
		}
		cout << log_msg << endl;
		return ;
	}
	if(tokens[ptr].F == ALTER)
	{
		ptr++;
		struct sent *t0,*t1,*t2,*t3,*t4;
		t0 = new sent;
		t0->name = "ALTER";
		t0->sz = 0;
		if(table(t1)&&id(t2)&&drop_add(t3)&&semicolon(t4))
		{
			t->name = "sql_stmt";
			t->sz = 5;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			t->nxt[4] = t4;
			print_tree(t,0);
			return ;
		}
		cout << log_msg << endl;
		return ;
	}
	if(tokens[ptr].F == UPDATE)
	{
		ptr++;
		struct sent *t0,*t1,*t2,*t3,*t4,*t5,*t6,*t7;
		t0 = new sent;
		t0->name = "UPDATE";
		t0->sz = 0;
		if(id(t1)&&setx(t2)&&key_value_pairs(t3)&&optional_where(t4)&&semicolon(t5))
		{
			t->name = "sql_stmt";
			t->sz = 6;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			t->nxt[4] = t4;
			t->nxt[5] = t5;
			print_tree(t,0);
			return ;
		}
		cout << log_msg << endl;
		return ;
	}
	if(tokens[ptr].F == INSERT)
	{
		ptr++;
		struct sent *t0,*t1,*t2,*t3,*t4,*t5,*t6,*t7,*t8;
		t0 = new sent;
		t0->name = "INSERT";
		t0->sz = 0;
		if(into(t1)&&id(t2)&&optional_attributes(t3)&&values(t4)&&left_br(t5)&&values_list(t6)&&right_br(t7)&&semicolon(t8))
		{
			t->name = "sql_stmt";
			t->sz = 9;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			t->nxt[4] = t4;
			t->nxt[5] = t5;
			t->nxt[6] = t6;
			t->nxt[7] = t7;
			t->nxt[8] = t8;
			print_tree(t,0);
			return ;
		}
		cout << log_msg << endl;
		return ;
	}
	if(tokens[ptr].F == SELECT)
	{
		ptr++;
		struct sent *t0,*t1,*t2,*t3,*t4,*t5,*t6,*t7,*t8;
		t0 = new sent;
		t0->name = "SELECT";
		t0->sz = 0;
		if(optional_distinct(t1)&&select_list(t2)&&from(t3)&&variables(t4)&&optional_where(t5)&&semicolon(t6))
		{
			t->name = "sql_stmt";
			t->sz = 7;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			t->nxt[4] = t4;
			t->nxt[5] = t5;
			t->nxt[6] = t6;

			print_tree(t,0);
			return ;
		}
		cout << log_msg << endl;
		return ;
	}
	if(tokens[ptr].F == CREATE)
	{
		ptr++;
		struct sent *t0,*t1,*t2,*t3,*t4,*t5,*t6,*t7,*t8;
		t0 = new sent;
		t0->name = "CREATE";
		t0->sz = 0;
		if(table(t1)&&id(t2)&&left_br(t3)&&table_columns(t4)&&right_br(t5)&&semicolon(t6))
		{
			t->name = "sql_stmt";
			t->sz = 7;
			t->nxt[0] = t0;
			t->nxt[1] = t1;
			t->nxt[2] = t2;
			t->nxt[3] = t3;
			t->nxt[4] = t4;
			t->nxt[5] = t5;
			t->nxt[6] = t6;
			print_tree(t,0);
			return ;
		}
		cout << log_msg << endl;
		return ;
	}
	else
	{
		printf("Syntax error.\n");
		return ;
	}
}

/* 
main function to call the lexical analyser which in turn calls the parser which does the syntax analysis
*/
int main()
{	
	lexical();
	return 0;
}