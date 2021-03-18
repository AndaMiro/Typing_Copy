#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <Windows.h>
#include <time.h>

#define TIMER 1000 * 10
#define TRUE 1
#define FALSE 0

typedef int bool;

typedef struct text {
	char info;
	int second;
	bool isBack;
	bool isEnter;
	struct text* n_text;
} TEXT;

void inputText(TEXT**, TEXT**, TEXT*);

TEXT* makeText(char, int, bool, bool);

void showTime(TEXT*);

int main(void) {
	char text;
	TEXT* h_text = NULL, * t_text = NULL;
	clock_t start = clock(), end;
	while (1) {
		end = clock();
		if (_kbhit()) {
			text = _getch();

			switch (text) {
			case 8: //Back-Space
				fputs("\b ", stdout);
				fputc(text, stdout);
				inputText(&h_text, &t_text, makeText(text, end - start, TRUE, FALSE));
				break;

			case 13: //Enter
				fputs("\n", stdout);
				fputc(text, stdout);
				inputText(&h_text, &t_text, makeText(text, end - start, FALSE, TRUE));
				break;

			case 27: //Esc
				system("cls");
				fputs("입력 복제 완료, 입력을 따라합니다.\n", stdout);
				showTime(h_text);
				return 0;

			default:
				fputc(text, stdout);
				inputText(&h_text, &t_text, makeText(text, end - start, FALSE, FALSE));
				break;
			}

			start = clock();
		}
		if (end - start >= TIMER) {
			system("cls");
			fputs("입력 복제 완료, 입력을 따라합니다.\n", stdout);
			showTime(h_text);
			return 0;
		}
	}
}

void showTime(TEXT* h_text) {
	if (h_text == NULL) {
		fputs("\n\n입력이 끝났습니다.\n", stdout);
		return;
	}
	Sleep(h_text->second);
	if (h_text->isBack) {
		fputs("\b ", stdout);
		fputc(h_text->info, stdout);
		showTime(h_text->n_text);
		free(h_text);
		return;
	}
	if (h_text->isEnter) {
		fputs("\n", stdout);
		showTime(h_text->n_text);
		free(h_text);
		return;
	}

	fputc(h_text->info, stdout);
	showTime(h_text->n_text);
	free(h_text);
	return;
}

TEXT* makeText(char info, int second, bool isBack, bool isEnter) {
	TEXT* text = (TEXT*)malloc(sizeof(TEXT));
	text->info = info;
	text->second = second;
	text->isBack = isBack;
	text->isEnter = isEnter;
	text->n_text = NULL;
	return text;
}

void inputText(TEXT** h_text, TEXT** t_text, TEXT* text) {
	if (*h_text == NULL) {
		*h_text = *t_text = text;
		return;
	}
	(*t_text)->n_text = text;
	*t_text = text;
	return;
}
