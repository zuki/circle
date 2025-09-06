#include <circle/string.h>
#include <assert.h>
#include "p9chan.h"
#include "p9error.h"

static CString *s_pPath = 0;

// ファームウェアディレクトリのファイル名 nameのファームウェアファイルを
// チャンネルとして開く
Chan *namec (const char *name, unsigned func, unsigned flags, unsigned opt)
{
	Chan *c = new Chan;
	assert (c != 0);

	c->type = 0;
	c->open = 0;

	assert (s_pPath != 0);
	// Path: ファームウェアファイルの完全名
	CString Path;
	Path.Format ("%s%s", (const char *) *s_pPath, name);

	// ファームウェアファイルをオープンする
	FRESULT Result = f_open (&c->file, Path, FA_READ | FA_OPEN_EXISTING);
	if (Result != FR_OK)
	{
		delete c;

		print ("File: %s\n", (const char *) Path);
		error (Enonexist);

		return 0;
	}

	c->open = 1;
	c->offset = 0;

	return c;
}

// チャンネルを閉じる
void cclose (Chan *c)
{
	assert (c->open);

	f_close (&c->file);

	c->open = 0;

	delete c;
}

// チャンネルcをオフセットoffsetから長さlenだけbufに読み込み、
// 読み込んだバイト数を返す
static int readchan (Chan *c, void *buf, size_t len, ulong offset)
{
	assert (c->open);

	FRESULT Result;
	if (c->offset != offset)
	{
		Result = f_lseek (&c->file, offset);
		assert (Result == FR_OK);

		c->offset = offset;
	}

	unsigned nBytesRead;
	Result = f_read (&c->file, buf, len, &nBytesRead);
	if (Result != FR_OK)
	{
		error (Eio);

		return -1;
	}

	c->offset += nBytesRead;

	return (int) nBytesRead;
}

// struct device_t変数: チャンネルの操作関数
static struct device_t devchan
{
	readchan
};

// struct device_tの配列
struct device_t *devtab[1] =
{
	&devchan
};

void p9chan_init (const char *path)
{
	assert (s_pPath == 0);
	// ファームウェアが存在するパスをセット
	s_pPath = new CString (path);
	assert (s_pPath != 0);
}
