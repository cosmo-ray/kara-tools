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

struct frms {
	int frm_in, frm_out;
	LIST_ENTRY(frms) entries;
};

LIST_HEAD(frm_head, frms);

int main(int ac, char **av)
{
	RET_ON(ac < 3, "%s usage: file.ass, frm per ms (so an int)\n", av[0]);
	int fd_in = open(av[1], 0, O_RDONLY);
	/* so i can use 2398 instead of 23.98 and not dealing with float */
	int frm_per_cs = atoi(av[2]);
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
	struct frms *frm = NULL;
	struct frms *new;

	while (ret = read(fd_in, in + tot_write, 1024)) {
		RET_ON(ret < 0, "error reading %s\n", av[1]);
		tot_write += ret;
		if (tot_write + 1024 >= in_bufsize) {
			in = realloc(in, in_bufsize * 2);
			in_bufsize *= 2;
			assert(in);
		}
	}

	printf("%s\n", in);

	char *events = strstr(in, "[Events]");
	RET_ON(!events, "Events not found");

	/* for now the style is fix */
	printf("[lyr]\n"
		";%%style Default SecondaryColour=&H0000FFFF KaraokeColour=&H000000FF PrimaryColour=&H00FFAA55 OutlineColour=&H00000000 BackColour=&H00000000 Fontname='DejaVu Sans' Fontsize=25 Bold=0 Italic=0 \
Underline=0 StrikeOut=0 ScaleX=200 ScaleY=200 Spacing=0 Angle=0 BorderStyle=1 Outline=5 Shadow=2 Alignment=8 MarginL=10 MarginR=10 MarginV=10 Encoding=1\n");

	events = strstr(events, "Dialogue:");
	char *next_events;
	RET_ON(!events, "no dialogue found\n");
	int line_fmr = 0;

new_line:
	/* get line starting frame here */
	events += sizeof "Dialogue:";
	/* time format: 0,0:00:11.29 */
	events = strchr(events, ':') + 1;
	line_fmr = 60 * atoi(events) * frm_per_cs;
	events = strchr(events, ':') + 1;
	line_fmr += atoi(events) * frm_per_cs;
	events = strchr(events, '.') + 1;
	line_fmr = line_fmr / 100;
	line_fmr += atoi(events) * frm_per_cs / 10000;
	next_events = strstr(events, "Dialogue:");

	putchar(';');
	char *syl = events;
	while (syl = strstr(syl, "{\\")) {
		int have_print = 0;
		if (!syl || (next_events && syl > next_events))
			break;
		/* parse time here */
		for (; !(*syl > '0' && *syl < '9'); ++syl);
		new = malloc(sizeof *frm);
		new->frm_in = line_fmr + 1;
		line_fmr += (atoi(syl) * frm_per_cs / 10000 );
		new->frm_out = line_fmr;

		syl = strchr(syl, '}');
		RET_ON(!syl, "unclose sylabe\n");
		++syl;
		for (; *syl && *syl != '{'  && *syl != '\n'; ++syl) {
			if (!have_print) {
				printf("&");
				have_print = 1;
			}
			putchar(*syl);
		}
		if (have_print) {
			if (!frm) {
				LIST_INIT(&frm_head);
				LIST_INSERT_HEAD(&frm_head, new, entries);
			} else {
				LIST_INSERT_AFTER(frm, new, entries);
			}
			frm = new;
		} else {
			free(new);
		}
		--syl;
	}
	if (next_events) {
		events = next_events;
		printf("\n", events);
		goto new_line;
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
