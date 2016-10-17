#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filter.h"
#include "sbuf.h"
#include "util.h"

static struct sbuf needle;
static int has_been_inited;

void filter_init(void)
{
	sbuf_init(&needle);
	has_been_inited = 1;
}

void filter_addstr(const char *str, size_t n)
{
	int i;

	if (!has_been_inited)
		die("filter has not been initiated");

	for (i = 0; i < n; i++)
		sbuf_addch(&needle, str[i]);

	printf("%s\n", needle.buf);
}

void filter_backspace(void)
{
	if (!has_been_inited)
		die("filter has not been initiated");

	if (needle.len > 0) {
		needle.buf[--needle.len] = '\0';
		printf("%s\n", needle.buf);
	}
}

int filter_ismatch(const char *haystack)
{
	int ret = 0;

	if ((needle.len) && strstr(haystack, needle.buf))
		ret = 1;

	return ret;
}