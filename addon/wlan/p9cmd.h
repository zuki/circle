#ifndef _p9cmd_h
#define _p9cmd_h

#include "p9util.h"

#ifdef __cplusplus
extern "C" {
#endif

/* コマンド構造体 : 例 {CMauth,	"auth", 2} */
typedef struct
{
	unsigned index;		/* コマンドインデックス */
	const char *cmd;	/* コマンド名 */
	unsigned maxargs;	/* 引数の最大数 */
}
Cmdtab;

/* コマンドバッファ構造体 */
typedef struct
{
	char buf[200];		/* バッファ */
	unsigned argc;		/* 引数の数 */
	char *f[10];		/* コマンドと引数の配列 */
}
Cmdbuf;

void cmderror (Cmdbuf *cb, const char *err);
Cmdbuf *parsecmd (const void *str, long n);
Cmdtab *lookupcmd (Cmdbuf *cb, Cmdtab *ct, size_t nelem);

#ifdef __cplusplus
}
#endif

#endif
