#ifndef JSON_H
#define JSON_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

typedef enum JSON_VALUE_TYPE_ENUM
{
    JSON_VALUE_TYPE_ENUM_FALSE,
    JSON_VALUE_TYPE_ENUM_TRUE,
    JSON_VALUE_TYPE_ENUM_NULL,
    JSON_VALUE_TYPE_ENUM_STRING,
    JSON_VALUE_TYPE_ENUM_INT,
    JSON_VALUE_TYPE_ENUM_FLOAT,
    JSON_VALUE_TYPE_ENUM_ARRAY,
    JSON_VALUE_TYPE_ENUM_OBJECT,
    JSON_VALUE_TYPE_ENUM_COUNT
} JSON_VALUE_TYPE_ENUM;

typedef union json_value_union
{
    const char* json_string;
    i32 json_int;
    f64 json_float;
} json_value_union;

typedef struct json_value
{
    JSON_VALUE_TYPE_ENUM value_type;
    json_value_union value_data;
} json_value;

typedef struct Json
{
    struct Json* next;
    struct Json* prev;
    u32 children_count;
    json_value value;
    const char* name;
} Json;

extern Json* json_parse(const char* raw_json);
extern void json_dispose(Json* node);
Json* json_node_new(void);
void json_node_free(Json* node);

const char* json_internal_parse_value(Json* node, const char* value);
const char* json_internal_skip(const char* string);

const char* json_internal_parse_string(Json* node, const char* value);
const char* json_internal_parse_array(Json* node, const char* value);
const char* json_internal_parse_object(Json* node, const char* value);
const char* json_internal_parse_number(Json* node, const char* value);

Json* json_get_item_by_name(Json* node, const char* name);
json_value json_get_value(Json* node, const char* name);
const char* json_get_value_as_string(Json* node, const char* name, const char* defualt_value);
f32 json_get_value_as_f32(Json* node, const char* name, f32 defualt_value);
i32 json_get_value_as_i32(Json* node, const char* name, i32 defualt_value);

const char* json_get_error(void);

#endif
