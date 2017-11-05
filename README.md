## SQL Parser
A recursive descent parser for the SQL language written in C++ language. It also displays the syntax tree corresponding to syntactically correct SQL query.

## Installing / Getting started

* Clone the repository by typing the following command in the shell.
```shell
git clone https://github.com/abhiyadav1323/SQL_Parser.git
```
* Use following command to compile the source files.
```shell
g++  -std=c++1y lexical.cpp parser.cpp -o parser
```
* Run the executable.
```shell
./parser
```

## Features
Following queries of SQL were taken into consideration:
* CREATE Query
* SELECT Query 
* INSERT Query
* UPDATE Query
* DELETE Query
* DROP TABLE Query
* ALTER TABLE Query

## Examples

```shell
$ Select * from S where S.name = "Abhishek";
sql_stmt ---> SELECT optional_distinct select_list FROM variables optional_where SEMICOLON
        optional_distinct ---> epsilon
        select_list ---> STAR
        variables ---> IDENTIFIER
                IDENTIFIER ---> S
        optional_where ---> WHERE where_conditions
                where_conditions ---> conditions where_condition
                        conditions ---> expressions EQUAL expressions
                                expressions ---> IDENTIFIER expression
                                        IDENTIFIER ---> S.name
                                        expression ---> epsilon
                                expressions ---> STRING expression
                                        STRING ---> "Abhishek"
                                        expression ---> epsilon
                        where_condition ---> epsilon

$ Delete from S where S.id = 1;
sql_stmt ---> DELETE FROM IDENTIFIER optional_where SEMICOLON
        IDENTIFIER ---> S
        optional_where ---> WHERE where_conditions
                where_conditions ---> conditions where_condition
                        conditions ---> expressions EQUAL expressions
                                expressions ---> IDENTIFIER expression
                                        IDENTIFIER ---> S.id
                                        expression ---> epsilon
                                expressions ---> NUMBER expression
                                        NUMBER ---> 1
                                        expression ---> epsilon
                        where_condition ---> epsilon

$ Drop table Students;
sql_stmt ---> DROP TABLE IDENTIFIER SEMICOLON
        IDENTIFIER ---> Students
```

## Licensing

The MIT License (MIT)

Copyright (c) 2017 Abhishek Yadav

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
