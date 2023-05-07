#ifndef __PARSER_H
#define __PARSER_H

#include <map>

typedef std::map<String, String> PayloadData;

PayloadData parseRequest(String request);

#include "parser.cpp"

#endif