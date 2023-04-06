#include "json.h"

// Allocates a new empty node
Json* json_node_new(void)
{
    return (Json*)calloc(1, sizeof(Json));
}

// Free a specific node and its fields
void json_node_free(Json* node)
{
    // TODO add proper freeing of all sub fields
    free(node);
}

// Allocates a new head node and parses the raw json into nodes
Json* json_parse(const char* raw_json)
{
    if(!raw_json)
    {
        return NULL;
    }

    Json* node = json_node_new();
    if(!node)
    {
        return NULL;
    }

    raw_json = json_internal_parse_value(node, json_internal_skip(raw_json));
    if(!raw_json)
    {
        json_dispose(node);
        return NULL;
    }

    return node;
}

// Recursivly remove all allocated nodes
void json_dispose(Json* node)
{
    // TODO recursive cleaning of all allocated nodes
    json_node_free(node);
}

const char* json_internal_parse_value(Json* node, const char* value)
{
    if(!value)
    {
        return NULL;
    }

    switch(*value)
    {
        case 'n':
            if(!strncmp(value + 1, "ull", 3))
            {
                node->value.value_type = JSON_VALUE_TYPE_ENUM_NULL;
                return value + 4;
            }
            break;
        case 't':
            if(!strncmp(value + 1, "rue", 3))
            {
                node->value.value_type = JSON_VALUE_TYPE_ENUM_TRUE;
                node->value.value_data.json_int = 1;
                return value + 4;
            }
            break;
        case 'f':
            if(!strncmp(value + 1, "alse", 4))
            {
                node->value.value_type = JSON_VALUE_TYPE_ENUM_FALSE;
                node->value.value_data.json_int = 0;
                return value + 5;
            }
            break;
        case '\"':
            return json_internal_parse_string(node, value);
        case '[':
            return json_internal_parse_value(node, value);
        case '{':
            return json_internal_parse_object(node, value);
        default:
            break;
    }

    if((*value >= '0' && *value <= '9') || *value == 45)
    {
        return json_internal_parse_number(node, value);
    }

    return NULL;
}

// Utility to jump whitespace and cr/lf
const char* json_internal_skip(const char* string)
{
    if(!string)
    {
        return NULL;
    }

    while(*string && (u8)*string <= 32)
    {
        string++;
    }

    return string;
}

const char* json_internal_parse_string(Json* node, const char* value)
{
    if(!node || !value)
    {
        return NULL;
    }

    return NULL;
}

const char* json_internal_parse_array(Json* node, const char* value)
{
    return NULL;
}

const char* json_internal_parse_object(Json* node, const char* value)
{
    return NULL;
}

const char* json_internal_parse_number(Json* node, const char* value)
{
    if(!node || !value)
    {
        return NULL;
    }

    char* cursor = (char*)value;

    bool negative = false;
    if(*cursor == '-')
    {
        negative = true;
        ++cursor;
    }

    f64 result = 0.0;
    bool is_int = false;

    while(*cursor >= '0' && *cursor <= '9')
    {
        is_int = true;
        result = result * 10.0 + (*cursor - '0');
        ++cursor;
    }

    if(*cursor == '.')
    {
        is_int = false;
        f64 fraction = 0.0;
        i32 n = 0;
        ++cursor;

        while(*cursor >= '0' && *cursor <= '9')
        {
            fraction = (fraction * 10.0) + (*cursor - '0');
            ++cursor;
            ++n;
        }
        result += fraction / pow(10.0, n);
    }

    if(negative)
    {
        result = -result;
    }

    if(*cursor == 'e' || *cursor == 'E')
    {
        is_int = false;
        f64 exponent = 0;
        i32 exp_negative = 0;
        i32 n = 0;
        ++cursor;

        if(*cursor == '-')
        {
            exp_negative = -1;
            ++cursor;
        }
        else if(*cursor == '+')
        {
            ++cursor;
        }

        while(*cursor >= '0' && *cursor <= '9')
        {
            exponent = (exponent * 10.0) + (*cursor - '0');
            ++cursor;
            ++n;
        }

        if(exp_negative)
        {
            result = result / pow(10, exponent);
        }
        else
        {
            result = result * pow(10, exponent);
        }
    }

    if(cursor != value)
    {
        if(is_int)
        {
            node->value.value_type = JSON_VALUE_TYPE_ENUM_INT;
            node->value.value_data.json_int = (i32)result;
        }
        else
        {
            node->value.value_type = JSON_VALUE_TYPE_ENUM_FLOAT;
            node->value.value_data.json_float = (f64)result;
        }
        return cursor;
    }
    return NULL;
}
