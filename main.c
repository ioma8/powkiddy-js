#include <stdio.h>
#include <stdlib.h> // Added for malloc and free
#include <unistd.h> // Added for usleep
#include "duktape-2.7.0/src/duktape.h"

static duk_ret_t native_print(duk_context *ctx);
static duk_ret_t native_sleep(duk_context *ctx);
char *read_file(const char *filename);

int main(int argc, char *argv[])
{
    char *js_code = read_file("test.js");
    if (js_code == NULL)
    {
        printf("Failed to read JS file\n");
        return 1;
    }
    duk_context *ctx = duk_create_heap_default();
    duk_push_c_function(ctx, native_print, 1 /*nargs*/);
    duk_put_global_string(ctx, "print");
    duk_push_c_function(ctx, native_sleep, 1 /*nargs*/);
    duk_put_global_string(ctx, "sleep");
    duk_eval_string_noresult(ctx, js_code);
    duk_destroy_heap(ctx);
    free(js_code); // Free the allocated memory
    return 0;
}

static duk_ret_t native_print(duk_context *ctx)
{
    printf("%s\n", duk_to_string(ctx, 0));
    return 0; /* no return value (= undefined) */
}

static duk_ret_t native_sleep(duk_context *ctx)
{
    duk_int_t ms = duk_require_int(ctx, 0);
    // Sleep for the specified number of milliseconds
    usleep(ms * 1000);
    return 0; /* no return value */
}

char *read_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = (char *)malloc(length + 1);
    buffer[length] = '\0';
    fread(buffer, 1, length, file);
    fclose(file);
    return buffer;
}