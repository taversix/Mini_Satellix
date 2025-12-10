/* 负责纯内置函数 */
#include "include/include.h"
#include "include/global.h"
#include "include/global.h"
#include "include/luas.h"

#define STR_SIZE (4*1024)

const Res err_type = { 0, NULL, "Type error" };
const Res err_input = { 0, NULL, "Input error" };
const Res err_loc = { 0, NULL, "Fail to locate" };
const Res err_set = { 0, NULL, "Fail to set result struct" };
const Res err_x = { 0, NULL, "Unknown" };
const Res err_openf = { 0, NULL, "Fail to open file" };
const Res err_writef = { 0, NULL, "Fail to write file" };
const Res err_readf = { 0, NULL, "Fail to read file" };

void Init_bif_words();
void res_free(Res *r);
Res *print(const char *t);
Res *println(const char *t);
Res *input(char type);
Res *write(char *filename, char *content, char* mode);
Res *read(char *filename);