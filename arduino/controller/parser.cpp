#include "parser.h"
#include <malloc.h>
#include <map>

#define BUFSZ 64

enum ParseState
{
    INITIAL,
    PATH,
    KEY,
    VALUE,
    COMPLETED,
};

void _saveToMap(PayloadData &result, String &key, String &value)
{
    result[String(key)] = String(value);
    key = String();
    value = String();
}

PayloadData parseRequest(String request)
{
    const char *req = request.c_str();
    char *pReq = (char *)req;
    enum ParseState state = INITIAL;
    String key = String("");
    String val = String("");
    PayloadData result;

    while (*pReq != '\0')
    {
        switch (state)
        {
        case INITIAL:
            switch (*pReq)
            {
            case '/':
                state = PATH;
                key = String("_PATH");
                break;
            case '?':
                state = KEY;
                key = String("");
                break;
            }
            break;

        case PATH:
            switch (*pReq)
            {
            case '?':
                state = KEY;
                _saveToMap(result, key, val);
                break;
            default:
                val += *pReq;
            }
            break;

        case KEY:
            switch (*pReq)
            {
            case '&':
                state = KEY;
                _saveToMap(result, key, val);
                break;
            case '=':
                state = VALUE;
                val = String("");
                break;
            case '\r':
            case '\n':
            case ' ':
                state = COMPLETED;
                _saveToMap(result, key, val);
                break;
            default:
                key += String(*pReq);
            }
            break;
        case VALUE:
            switch (*pReq)
            {
            case '&':
                state = KEY;
                _saveToMap(result, key, val);
                break;
            case ' ':
            case '\r':
            case '\n':
                state = COMPLETED;
                _saveToMap(result, key, val);
                break;
            default:
                val += String(*pReq);
            }
        }

        if (state == COMPLETED)
            break;
        pReq++;
    }
    if (key.length() > 0)
        _saveToMap(result, key, val);
    return result;
}