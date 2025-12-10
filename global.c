/* 工具文件 全局变量 */
#include "include/luas.h"
#include "include/dict.h"
#include "include/bin.h"
/*======================================================*/
#define CONFIG_PLUGINS  ".\\config\\plugins.lua"
#define PLUGINS_DIR     ".\\plugins\\"
/*======================================================*/
/*【全局变量】*/
// 全局状态表
Dict *global;
Bin  *bif_bin;
Bin  *sh_bin;
char *bif_words;
// 运行结果结构体定义
typedef struct
{
    int   success;
    char *output;
    char *err;
    void *addtion
} Res;
/*======================================================*/
// 初始化全局状态表
void Init_Global()
{
    global = dict_create(1);
    dict_set(global, "status", value_create('s', "ok"));
    dict_set(global, "version", value_create('n', 1.0)); // 版本号
    
}
// 初始化所有垃圾桶
void Init_Bins()
{
    bif_bin = bin_create();
    sh_bin = bin_create();
}