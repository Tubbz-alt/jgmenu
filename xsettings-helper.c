/*
 * Copyright (C) 2016 Ovidiu M <mrovi9000@gmail.com>
 * Modified by Johan Malm
 */

#include <stdio.h>
#include <stdlib.h>

#include "sbuf.h"
#include "xsettings-helper.h"
#include "xsettings.h"

static void print_setting(XSetting *setting)
{
	printf("%s: ", setting->name);
	if (setting->type == XSETTINGS_TYPE_INT)
		printf("%d\n", setting->value.int_value);
	else if (setting->type == XSETTINGS_TYPE_STRING)
		printf("%s\n", setting->value.string_value);
	else if (setting->type == XSETTINGS_TYPE_COLOR)
		printf("%2x%2x%2x %d\n", setting->value.color_value.red,
		       setting->value.color_value.green,
		       setting->value.color_value.blue,
		       setting->value.color_value.alpha);
	else
		printf("??\n");
}

static void print_settings(XSetting *settings, size_t count, const char *key,
			   struct sbuf *s)
{
	for (size_t i = 0; i < count; i++) {
		if (key[0] == '*') {
			print_setting(&settings[i]);
		} else {
			if (settings[i].type == XSETTINGS_TYPE_STRING &&
			    !strcmp(settings[i].name, key)) {
				sbuf_cpy(s, settings[i].value.string_value);
				break;
			}
		}
	}
}

int xsettings_get(struct sbuf *s, const char *key)
{
	Display *display;
	size_t count;
	static int ret;
	XSetting *settings;

	if (!key)
		return 1;

 	display = XOpenDisplay(NULL);
	if (!display) {
		fprintf(stderr, "Could not open display\n");
		return 1;
	}

	settings = get_xsettings(display, &count);
	if (settings) {
		print_settings(settings, count, key, s);
		free_xsettings(settings, count);
	} else {
		fprintf(stderr, "Could not read settings\n");
		ret = 1;
		goto close_disp;
	}

close_disp:
	XCloseDisplay(display);
	return ret;
}