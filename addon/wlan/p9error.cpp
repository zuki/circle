#include "p9error.h"
#include "p9proc.h"
#include "p9util.h"
#include <assert.h>

// エラーをupにセットしてエラースタックの一番上にあるjmp_bufにlong_jmpする
void error (const char *str)
{
	print ("%s\n", str);

	up->errstr = str;

	error_stack_t *s = get_error_stack ();
	assert (s != 0);

	assert (s->stackptr < ERROR_STACK_SIZE);
	s->stackptr++;
	longjmp (s->stack[s->stackptr-1], 1);
}

// エラースタックの一番上にあるjmp_bufを返す
jmp_buf *pusherror (void)
{
	error_stack_t *s = get_error_stack ();
	assert (s != 0);

	return &s->stack[--s->stackptr];
}

// エラースタックからエラーを取り出して返す
void nexterror (void)
{
	error_stack_t *s = get_error_stack ();
	assert (s != 0);

	assert (s->stackptr < ERROR_STACK_SIZE);
	s->stackptr++;
	longjmp (s->stack[s->stackptr-1], 1);
}

// エラースタックからエラーを1つ取り出して捨てる
void poperror (void)
{
	error_stack_t *s = get_error_stack ();
	assert (s != 0);

	assert (s->stackptr < ERROR_STACK_SIZE);
	s->stackptr++;
}

// 何もしない
void okay (int status)
{
}
