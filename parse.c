/* 负责解格式化文本 */

/* 格式化文本：
 * $VAR$
 * $DLR$ = $
 * $QOT$ = "
 */

// 从配置、全局状态表里寻找
char *match(char unit);

char *parse(char *fmt);

// 别忘了管理垃圾桶