#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <string.h>

struct block {
    int number;
    char color[16];
    char mat[16];
    unsigned int rbr;
};

FILE *f;

void menu(void) {
    printf(
            "\n"
            "1. Добавление кубиков.\n"
            "2. Список Кубиков .\n"
            "3. Поиск кубика.\n"
            "9. Выйти.\n\n"
    );
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Открытие файла ------------------------------
    f = fopen("kub.dat", "ab+");
    if (f == NULL) {
        printf("Не могу открыть 'kub.dat'. Нажмите клавишу...\n");
        _getch();
        return -1;
    }
    int ans;
    menu();

    int select;
    while (true) {
        printf("\rВыберите режим работы: ");
//        c = _getche();
        scanf_s("%d", select);
        block t;
        switch (select) {
            case '1': // Добавление
                printf("\n\nПополнение списка 'kub.dat'.\n"
                       "Для выхода в главное меню введите 0 .\n\n");
                fseek(f, 0, SEEK_END);
                while (true) {
                    printf("Номер: ");
                    scanf_s("%d", &t.number);
                    if (t.number == 0) break;

                    printf("Цвет: ");
                    scanf_s("%15s%*[^\n]5000s", t.color, 16);
                    if (t.color[0] == '0') break;

                    printf("Материал: ");
                    scanf_s("%15s%*[^\n]5000s", t.mat, 16);
                    if (t.mat[0] == '0') break;

                    printf("Длина Ребра: ");
                    scanf_s("%d", &t.rbr);
                    if (t.rbr == 0) break;

                    fwrite(&t, sizeof(t), 1, f);
                    printf("Информация добавлена.\n\n");
                }
                menu();
                break;
            case '2': // Просмотр
                printf(
                        "\n\nСписок Кубиков 'kub.dat'\n\n"
                        "\tНомер:      \tЦвет:       \tМатериал:    \tДлина ребра:\n");
                fseek(f, 0, SEEK_SET);
                setlocale(LC_ALL, ".866");
                while (true) {
                    if (fread(&t, sizeof(block), 1, f) != 1) break;
                    printf("\t%d\t\t%-15s\t%-15s\t%d\n", t.number, t.color, t.mat, t.rbr);//"\t%-15s\t%d\n"//
                }
                setlocale(LC_ALL, ".1251");
                menu();
                break;
            case '3': // Поиск
                printf("\n\nПоиск кубика по его цвету 'kub.dat'\n\n");
                char s[16];
                ans = 0;
                /*int sum;
                double h;
                double v;*/
                printf("Введите цвет: ");
                scanf_s("%15s%*[^\n]5000s", s, 16);

                printf("\tНомер:      \tЦвет:    \tДлина ребра:\n");
                fseek(f, 0, SEEK_SET);
                setlocale(LC_ALL, ".866");
                while (true) {
                    if (fread(&t, sizeof(block), 1, f) != 1) break;
                    if (strstr(t.color, s) != NULL) {
                        printf("\t%d\t\t%-15s\t%d\n", t.number, t.color, t.rbr);
                        ans += (t.rbr * t.rbr * t.rbr);
                    }
                }
                printf("Суммарный объем найденных кубиков : %d\n", ans);
                setlocale(LC_ALL, ".1251");
                menu();
                break;
            case '9': // Выход ---------------------------------------
                fclose(f);
                return 0;
        }
    }
}