#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

#define MAX_TRACKS 1000 // максимальное количество треков в базе данных
#define MAX_NAME 50 // максимальная длина названия трека
#define MAX_ARTIST 50 // максимальная длина имени исполнителя
#define MAX_GENRE 20 // максимальная длина жанра трека

// структура для хранения информации о музыкальном треке
typedef struct {
    char name[MAX_NAME]; //название трека
    char artist[MAX_ARTIST]; //исполнитель трека
    int year; //дата выпуска трека
    char genre[MAX_GENRE]; //жанр трека
    float duration; //длительность трека в минутах
} Track;

// функция для сортировки треков по названию 
int sort_by_name(Track tracks[], int num_tracks) {
    Track temp; // объявляем временную переменную для обмена элементов массива
    int i, j;
    for (i = 0; i < num_tracks - 1; i++) { // внешний цикл для прохода по всем элементам массива, кроме последнего
        for (j = i + 1; j < num_tracks; j++) { // внутренний цикл для прохода по всем элементам массива, начиная со следующего за i
            if (strcmp(tracks[i].name, tracks[j].name) > 0) { // если название i-го трека больше назавния j-го трека
                temp = tracks[i]; // сохраняем i-й трек во временной переменной
                tracks[i] = tracks[j]; // заменяем i-й трек на j-й трек
                tracks[j] = temp; // заменяем j - й трек на временную переменную(т.е.на i - й трек)
            }
        }
    }

    return 0;
}

// функция для сортировки треков по году выпуска 
int sort_by_year(Track tracks[], int num_tracks) {
    Track temp; // объявляем временную переменную для обмена элементов массива
    int i, j;
    for (i = 0; i < num_tracks - 1; i++) { // внешний цикл для прохода по всем элементам массива, кроме последнего
        for (j = i + 1; j < num_tracks; j++) { // внутренний цикл для прохода по всем элементам массива, начиная со следующего за i
            if (strcmp(tracks[i].year, tracks[j].year) > 0) { // если название i-го трека больше назавния j-го трека
                temp = tracks[i]; // сохраняем i-й трек во временной переменной
                tracks[i] = tracks[j]; // заменяем i-й трек на j-й трек
                tracks[j] = temp; // заменяем j - й трек на временную переменную(т.е.на i - й трек)
            }
        }
    }

    return 0;
}
// функция для сохранения данных о треках в файл 
int save_to_file(Track tracks[], int num_tracks, char* filename) {
    FILE* fp;
    int i;
    fp = fopen(filename, "w"); // открываем файл для записи в текстовом режиме
    if (fp == NULL) {
        printf("Ошибка открытия файла!n");
        return -1; // Возвращаем -1 в случае ошибки открытия файла
    }
    fprintf(fp, "Количество треков: %dn", num_tracks); // записываем количество треков в файл
    fprintf(fp, "%-25st%-25st%-15st%-4st%-10sn", "Название", "Исполнитель", "Жанр", "Год", "Длительность"); // записываем заголовок таблицы
    for (i = 0; i < num_tracks; i++) {
        fprintf(fp, "%-25st%-25st%-15st%-4dt%-10.2fn", tracks[i].name, tracks[i].artist, tracks[i].genre, tracks[i].year, tracks[i].duration); // записываем каждый трек в файл с табуляцией и корректным размером полей
    }
    fclose(fp);
    return 0; // Возвращаем 0 в случае успешного сохранения в файл
}

// функция для чтения данных о треках из файла 
int read_from_file(Track tracks[], int* num_tracks, char* filename) {
    FILE* fp;
    int i;
    fp = fopen(filename, "r"); // открываем файл для чтения в текстовом режиме
    if (fp == NULL) {
        printf("Ошибка открытия файла!\n");
        exit(1);
    }
    fscanf(fp, "Количество треков: %d\n", num_tracks); // считываем количество треков из файла
    for (i = 0; i < *num_tracks; i++) {
        fscanf(fp, "\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%f\n", tracks[i].name, tracks[i].artist, tracks[i].genre, &tracks[i].year, &tracks[i].duration); // считываем каждый трек из файла с помощью спецификаторов формата
    }
    fclose(fp);
    return 0;
}

// функция для добавления новых треков в базу данных 
int add_tracks(Track tracks[], int* num_tracks) {
    int num_new_tracks, i;
    printf("Введите число новых треков: ");
    scanf("%d", &num_new_tracks);
    getchar();
    if (*num_tracks + num_new_tracks > MAX_TRACKS) {
        printf("Ошибка: слишком много треков!n");
        return -1; // Возвращаем -1 в случае ошибки слишком большого количества треков
    }
    for (i = 0; i < num_new_tracks; i++) {
        printf("Введите информацию о треках %d:n", *num_tracks + i + 1);
        printf("Введите название трека: ");
        fgets(tracks[*num_tracks + i].name, MAX_NAME, stdin);
        tracks[*num_tracks + i].name[strcspn(tracks[*num_tracks + i].name, "n")] = '0';
        printf("Введите имя исполнителя: ");
        fgets(tracks[*num_tracks + i].artist, MAX_ARTIST, stdin);
        tracks[*num_tracks + i].artist[strcspn(tracks[*num_tracks + i].artist, "n")] = '0';
        printf("Введите год: ");
        scanf("%d", &tracks[*num_tracks + i].year);
        getchar();
        printf("Введите жанр: ");
        fgets(tracks[*num_tracks + i].genre, MAX_GENRE, stdin);
        tracks[*num_tracks + i].genre[strcspn(tracks[*num_tracks + i].genre, "n")] = '0';
        printf("Введите длительность (в минутах): ");
        scanf("%f", &tracks[*num_tracks + i].duration);
        getchar();
    }
    *num_tracks += num_new_tracks;
    return 0; // Возвращаем 0 в случае успешного добавления треков
}
// функция для изменения информации о треке 
int edit_track(Track tracks[], int num_tracks) {
    char name[MAX_NAME]; // объявляем переменную названия трека
    int i;
    printf("Введите название трека для редактирования: ");
    fgets(name, MAX_NAME, stdin); // считываем название трека с помощью fgets
    name[strcspn(name, "n")] = '0'; // удаляем символ переноса строки из названия
    for (i = 0; i < num_tracks; i++) { // перебираем все треки в массиве
        if (strcmp(tracks[i].name, name) == 0) { // если название трека совпадает с введенным
            printf("Введите новую информацию для трека %d:n", i + 1); // выводим сообщение о номере трека
            printf("Введите название трека: ");
            fgets(tracks[i].name, MAX_NAME, stdin);
            tracks[i].name[strcspn(tracks[i].name, "n")] = '0';
            printf("Введите имя исполнителя: ");
            fgets(tracks[i].artist, MAX_ARTIST, stdin);
            tracks[i].artist[strcspn(tracks[i].artist, "n")] = '0';
            printf("Введите год: ");
            scanf("%d", &tracks[i].year);
            getchar();
            printf("Введите жанр: ");
            fgets(tracks[i].genre, MAX_GENRE, stdin);
            tracks[i].genre[strcspn(tracks[i].genre, "n")] = '0';
            printf("Введите длительность (в минутах): ");
            scanf("%f", &tracks[i].duration);
            getchar();
            return 0; // Возвращаем 0 в случае успешного редактирования трека
        }
    }
    printf("Ошибка: трек не найден!n");
    return -1; // Возвращаем -1 в случае, если трек не найден
}
// функция для поиска трека по названию 
int search_by_name(Track tracks[], int num_tracks) {
    char name[MAX_NAME];
    int i;
    printf("Введите название трека для поиска: ");
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "n")] = '0';
    for (i = 0; i < num_tracks; i++) {
        if (strcmp(tracks[i].name, name) == 0) {
            printf("Трек найден:n");
            printf("%-30s %-20s %-10d %-20s %-10.2fn", tracks[i].name, tracks[i].artist, tracks[i].year, tracks[i].genre, tracks[i].duration);
            return i; // Возвращаем индекс найденного трека
        }
    }
    printf("Ошибка: трек не найден!n");
    return -1; // Возвращаем -1, если трек не найден
}
// функция для поиска треков по жанру 
int search_by_genre(Track tracks[], int num_tracks) {
    char genre[MAX_GENRE];
    int i, count = 0;
    printf("Введите жанр для поиска: ");
    fgets(genre, MAX_GENRE, stdin);
    genre[strcspn(genre, "n")] = '0';
    printf("Треки с этим жанром '%s':n", genre);
    for (i = 0; i < num_tracks; i++) {
        if (strcmp(tracks[i].genre, genre) == 0) {
            printf("%-30s %-20s %-10d %-20s %-10.2fn", tracks[i].name, tracks[i].artist, tracks[i].year, tracks[i].genre, tracks[i].duration);
            count++;
        }
    }
    if (count == 0) {
        printf("Не найдено треков с жанром '%s'!n", genre);
    }
    return count; // Возвращаем количество найденных треков с заданным жанром
}

int main() {
    setlocale(LC_ALL, "RUS");
    system("chcp 1251");
    Track tracks[MAX_TRACKS];
    int num_tracks = 0, choice;
    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить новые треки\n");
        printf("2. Изменить трек\n");
        printf("3. Поиск по названию\n");
        printf("4. Поиск по жанру\n");
        printf("5. Сортировка по названию\n");
        printf("6. Сортировка по году\n");
        printf("7. Печать всех треков\n");
        printf("8. Сохранить в файл\n");
        printf("9. Чтение из файла\n");
        printf("0. Выход\n");
        printf("Введите выбор: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
        case 1:
            add_tracks(tracks, &num_tracks);
            break;
        case 2:
            edit_track(tracks, num_tracks);
            break;
        case 3:
            search_by_name(tracks, num_tracks);
            break;
        case 4:
            search_by_genre(tracks, num_tracks);
            break;
        case 5:
            sort_by_name(tracks, num_tracks);
            printf("Треки сортированы по имени:\n");
            for (int i = 0; i < num_tracks; i++) {
                printf("%-30s %-20s %-10d %-20s %-10.2f\n", tracks[i].name, tracks[i].artist, tracks[i].year, tracks[i].genre, tracks[i].duration);
            }
            break;
        case 6:
            sort_by_year(tracks, num_tracks);
            printf("Треки сортированы по году:\n");
            for (int i = 0; i < num_tracks; i++) {
                printf("%-30s %-20s %-10d %-20s %-10.2f\n", tracks[i].name, tracks[i].artist, tracks[i].year, tracks[i].genre, tracks[i].duration);
            }
            break;
        case 7:
            printf("Все треки:\n");
            for (int i = 0; i < num_tracks; i++) {
                printf("%-30s %-20s %-10d %-20s %-10.2f\n", tracks[i].name, tracks[i].artist, tracks[i].year, tracks[i].genre, tracks[i].duration);
            }
            break;
        case 8:
            save_to_file(tracks, num_tracks, "tracks.txt");
            printf("Данные сохранены в файл!\n");
            break;
        case 9:
            read_from_file(tracks, &num_tracks, "tracks.txt");
            printf("Данные прочитаны из файла!\n");
            break;
        case 0:
            exit(0);
        default:
            printf("Неправильный выбор!\n");
        }
    }

    return 0;
}