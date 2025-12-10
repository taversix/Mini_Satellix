/* 负责初始化、Shell外壳、命令分割、命令执行 */
#include "include/include.h"
#include "include/luas.h"
#include "include/dict.h"
#include "include/api.h"
#include "include/global.h"
#include "include/plugin.h"
#include "include/builtin.h"

void handle(char *head, ...);
/*======================================================*/
int main()
{
    /* 程序开始 */
    Init_Global();
    Init_Bins();
    Init_Plugins();
    Init_bif_words();
    Broadcast("pre_shell_start", "");
    /* 初始化完成 */
    char *line = calloc(4*1024, sizeof(char));
    Res *r = calloc(1, sizeof(Res));
    while("Never gonna give you up")
    {
        ;
    }
    
    
    bin_empty(sh_bin);
    return 0;
}