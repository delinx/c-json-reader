#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "types.h"

int main()
{
    // Json* reader = json_parse("null");
    Json* reader = json_parse("1.0E-6");
    printf("%f", reader->value.value_data.json_float);
    json_dispose(reader);

    return 0;
}
