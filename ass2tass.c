//#!/usr/local/bin/tcc -run

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/queue.h>

#define RET_ON(condition, ...) if (condition) {printf(__VA_ARGS__); return -1;}

void auto_str(char **s) {
	free(*s);
   }

/*
 * In theory I should have a struct for each lines, one for each sylabes, and one for each timestamp
 * But doing without seems like less code.
 */
struct lyrs {
	int frm_in, frm_out;
	int len;
	char buf[1024];
	char *dialogue;
	int dial_start;
	LIST_ENTRY(lyrs) entries;
};

LIST_HEAD(frm_head, lyrs);

int main(int ac, char **av)
{
	RET_ON(ac < 2, "%s usage: file.ass\n", av[0]);
	int fd_in = open(av[1], 0, O_RDONLY);
	/* let's use VLA */
	int in_len = strlen(av[1]);
	if (in_len < 5)
		return -1;
	int in_bufsize = 2048;
	int tot_write = 0;
	__attribute__((cleanup(auto_str))) char *in = malloc(in_bufsize);
	assert(in);
	int ret;
	struct frm_head frm_head;
	struct lyrs *frm = NULL;
	struct lyrs *new;

	while (ret = read(fd_in, in + tot_write, 1024)) {
		RET_ON(ret < 0, "error reading %s\n", av[1]);
		tot_write += ret;
		if (tot_write + 1024 >= in_bufsize) {
			in = realloc(in, in_bufsize * 2);
			in_bufsize *= 2;
			assert(in);
		}
	}


	char *events = strstr(in, "[Events]");
	RET_ON(!events, "Events not found");

	/* print headers */
	*events = 0;
	printf("%s\n", in);
	events += sizeof("[Events"); /* ']' imgmore on purpose, as sizeof contain the \0 */

	/* for now the style is fix */
	events = strstr(events, "Dialogue:");
	char *next_events;
	RET_ON(!events, "no dialogue found\n");
	int line_tim = 0;
	char *cur_dialogue;
	int line_start_tim;

new_line:
	/* get line starting frame here */
	cur_dialogue = events;
	events += sizeof "Dialogue:";
	/* time format: 0,0:00:11.29 */
	events = strchr(events, ':') + 1;
	line_tim = 60 * atoi(events) * 100;
	events = strchr(events, ':') + 1;
	line_tim += atoi(events) * 100;
	events = strchr(events, '.') + 1;
	line_tim += atoi(events);
	next_events = strstr(events, "Dialogue:");
	line_start_tim = line_tim;

	char *syl = events;
	while (syl = strstr(syl, "{\\")) {
		int have_print = 0;
		if (!syl || (next_events && syl > next_events))
			break;
		*syl = 0; /* \0 so I can just print dialogue stuff then */
		/* parse time here */
		for (; !(*syl >= '0' && *syl <= '9'); ++syl);
		new = malloc(sizeof *frm);
		new->frm_in = line_tim + 1;
		new->len = atoi(syl);
		line_tim += new->len;
		new->frm_out = line_tim;
		new->dialogue = cur_dialogue;
		new->dial_start = line_start_tim;
		char *syl_buf = new->buf;

		syl = strchr(syl, '}');
		RET_ON(!syl, "unclose sylabe\n");
		++syl;
		for (; *syl && *syl != '{'  && *syl != '\n'; ++syl) {
			if (!have_print) {
				have_print = 1;
			}
			*syl_buf++ = *syl;
			*syl_buf = 0;
		}
		if (have_print) {
			if (!frm) {
				LIST_INIT(&frm_head);
				LIST_INSERT_HEAD(&frm_head, new, entries);
			} else {
				LIST_INSERT_AFTER(frm, new, entries);
			}
			frm = new;
			cur_dialogue = NULL;
		} else {
			free(new);
		}
		--syl;
	}
	if (next_events) {
		events = next_events;
		goto new_line;
	}

	printf("[Events]\n"
	       "Format: Layer, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text");

	struct lyrs *back = LIST_FIRST(&frm_head);
	LIST_FOREACH(frm, &frm_head, entries) {
		if (frm->dialogue) {
			while(back != frm) {
				printf("{\\pc(%d,%d)}%s", back->frm_in - back->dial_start,
				       back->frm_out - back->dial_start, back->buf);
				back = LIST_NEXT(back, entries);
			}
			printf("\n%s{\\fade(750, 500)}", frm->dialogue);
		}
		printf("{\\kt(%d,%d)}%s", frm->frm_in - frm->dial_start,
		       frm->frm_out - frm->dial_start, frm->buf);
	}
	while(back != NULL) {
		printf("{\\pc(%d,%d)}%s", back->frm_in - back->dial_start,
		       back->frm_out - back->dial_start, back->buf);
		back = LIST_NEXT(back, entries);
	}


	printf("\n\n[lyr]\n"
	       ";%%style Default SecondaryColour=&H0000FFFF KaraokeColour=&H000000FF PrimaryColour=&H00FFAA55 OutlineColour=&H00000000 BackColour=&H00000000 Fontname='DejaVu Sans' Fontsize=25 Bold=0 Italic=0 \
Underline=0 StrikeOut=0 ScaleX=200 ScaleY=200 Spacing=0 Angle=0 BorderStyle=1 Outline=5 Shadow=2 Alignment=8 MarginL=10 MarginR=10 MarginV=10 Encoding=1");
	LIST_FOREACH(frm, &frm_head, entries) {
		if (frm->dialogue) {
			printf("\n;");
		}
		printf("&%s", frm->buf);
	}


	printf("\n\n[tim]\n");
	frm = LIST_FIRST(&frm_head);
	while(frm != NULL) {
		new = LIST_NEXT(frm, entries);
		printf(";%d %d\n", frm->frm_in, frm->frm_out);
		free(frm);
		frm = new;
	}
}
