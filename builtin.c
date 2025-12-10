/* 负责纯内置函数 */
#include "include/include.h"
#include "include/global.h"
#include "include/global.h"
#include "include/luas.h"

#define STR_SIZE (4*1024)

// 常用错误类型
const Res err_type = { 0, NULL, "Type error" };
const Res err_input = { 0, NULL, "Input error" };
const Res err_loc = { 0, NULL, "Fail to locate" };
const Res err_set = { 0, NULL, "Fail to set result struct" };
const Res err_x = { 0, NULL, "Unknown" };
const Res err_openf = { 0, NULL, "Fail to open file" };
const Res err_writef = { 0, NULL, "Fail to write file" };
const Res err_readf = { 0, NULL, "Fail to read file" };

// api:get 应当转移到 builtin.c

void Init_bif_words()
{
    char *words = {
        "print",
        "println",
        "input",
        "write",
        "read",
        "get"
    };
    bif_words = words;
}

Res *__set_res(int s, char *o, char *e)
{
    Res *r = calloc(1, sizeof(Res));
    if(!r) return &err_set;
    r->success = s;
    r->output = o;
    r->err = e;
    return r;
}

void res_free(Res *r)
{
    if(!r) return;
    if(r == &err_type || r == &err_input || r == &err_loc || r == &err_set || r == &err_x) return;
    free(r->output);
    free(r->err);
    free(r);
}

char *__str(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    char *tmp = calloc(STR_SIZE, sizeof(char));
    if(!tmp) { va_end(ap); return NULL; }
    if(vsnprintf(tmp, STR_SIZE, fmt, ap) < 0) { va_end(ap); return NULL; }
    va_end(ap);

    bin_drop(bif_bin, tmp);
    return tmp;
}

Res *print(const char *t)
{
    if(printf("%s", t) >= 0)
        return __set_res(1, NULL, NULL);
    else
        return &err_x;
}

Res *println(const char *t)
{
    if(printf("%s\n", t) >= 0)
        return __set_res(1, NULL, NULL);
    else
        return &err_x;
}

Res *input(char type)
{
    void *result;
    switch (type)
    {
    case 's':
        result = calloc(STR_SIZE, sizeof(char));
        if(!result) { bin_drop(bif_bin, result); return &err_loc; }
        if(!fgets(result, STR_SIZE, stdin)) { bin_drop(bif_bin, result); return &err_input; }

        int c;
        while((c=getchar())!='\n' && c!=EOF);

        bin_drop(bif_bin, result);
        return __set_res(1, __str("%s", result), NULL);
    case 'n':
        result = calloc(1, sizeof(double));
        if(!result) return &err_loc;
        if(scanf("%lf", (double *)result) != 1) { bin_drop(bif_bin, result); return &err_input; }

        int c;
        while((c=getchar())!='\n' && c!=EOF);

       bin_drop(bif_bin, result);
        return __set_res(1, __str("%f", *(double *)result), NULL);
    case 'b':
        result = calloc(1, sizeof(char));
        if(!result) { bin_drop(bif_bin, result); return &err_loc; }
        if(scanf("%d", (int *)result) != 1) { bin_drop(bif_bin, result); return &err_input; }

        int c;
        while((c=getchar())!='\n' && c!=EOF);

        bin_drop(bif_bin, result);
        return __set_res(1, __str("%d", *(int *)result), NULL);
    default:
        bin_drop(bif_bin, result);
        return &err_type;
    }
}

Res *write(char *filename, char *content, char* mode)
{
    FILE *f = fopen(filename, mode);
    if(!f) { fclose(f); bin_drop(bif_bin, f); return &err_openf; }
    if(fprintf(f, content) < 0) { fclose(f); bin_drop(bif_bin, f); return &err_writef; }
    fclose(f);
    bin_drop(bif_bin, f);
    return __set_res(1, NULL, NULL);
}

Res *read(char *filename)
{
    FILE *f = fopen(filename, "r");
    if(!f) { fclose(f); bin_drop(bif_bin, f); return &err_openf; }
    char *content = calloc(STR_SIZE, sizeof(char));

    int bytes = fread(content, 1, STR_SIZE-1, f);
    content[bytes] = '\0';

    fclose(f);
    bin_drop(bif_bin, content);
    return __set_res(1, content, NULL);
}

Res *set_config(char *config, char *key)
{
    ;
}