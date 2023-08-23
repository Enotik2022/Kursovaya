#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

#define MAX_TRACKS 1000 // ������������ ���������� ������ � ���� ������
#define MAX_NAME 50 // ������������ ����� �������� �����
#define MAX_ARTIST 50 // ������������ ����� ����� �����������
#define MAX_GENRE 20 // ������������ ����� ����� �����

// ��������� ��� �������� ���������� � ����������� �����
typedef struct {
    char name[MAX_NAME]; //�������� �����
    char artist[MAX_ARTIST]; //����������� �����
    int year; //���� ������� �����
    char genre[MAX_GENRE]; //���� �����
    float duration; //������������ ����� � �������
} Track;

// ������� ��� ���������� ������ �� �������� 
int sort_by_name(Track tracks[], int num_tracks) {
    Track temp; // ��������� ��������� ���������� ��� ������ ��������� �������
    int i, j;
    for (i = 0; i < num_tracks - 1; i++) { // ������� ���� ��� ������� �� ���� ��������� �������, ����� ����������
        for (j = i + 1; j < num_tracks; j++) { // ���������� ���� ��� ������� �� ���� ��������� �������, ������� �� ���������� �� i
            if (strcmp(tracks[i].name, tracks[j].name) > 0) { // ���� �������� i-�� ����� ������ �������� j-�� �����
                temp = tracks[i]; // ��������� i-� ���� �� ��������� ����������
                tracks[i] = tracks[j]; // �������� i-� ���� �� j-� ����
                tracks[j] = temp; // �������� j - � ���� �� ��������� ����������(�.�.�� i - � ����)
            }
        }
    }

    return 0;
}

// ������� ��� ���������� ������ �� ���� ������� 
int sort_by_year(Track tracks[], int num_tracks) {
    Track temp; // ��������� ��������� ���������� ��� ������ ��������� �������
    int i, j;
    for (i = 0; i < num_tracks - 1; i++) { // ������� ���� ��� ������� �� ���� ��������� �������, ����� ����������
        for (j = i + 1; j < num_tracks; j++) { // ���������� ���� ��� ������� �� ���� ��������� �������, ������� �� ���������� �� i
            if (strcmp(tracks[i].year, tracks[j].year) > 0) { // ���� �������� i-�� ����� ������ �������� j-�� �����
                temp = tracks[i]; // ��������� i-� ���� �� ��������� ����������
                tracks[i] = tracks[j]; // �������� i-� ���� �� j-� ����
                tracks[j] = temp; // �������� j - � ���� �� ��������� ����������(�.�.�� i - � ����)
            }
        }
    }

    return 0;
}
// ������� ��� ���������� ������ � ������ � ���� 
int save_to_file(Track tracks[], int num_tracks, char* filename) {
    FILE* fp;
    int i;
    fp = fopen(filename, "w"); // ��������� ���� ��� ������ � ��������� ������
    if (fp == NULL) {
        printf("������ �������� �����!n");
        return -1; // ���������� -1 � ������ ������ �������� �����
    }
    fprintf(fp, "���������� ������: %dn", num_tracks); // ���������� ���������� ������ � ����
    fprintf(fp, "%-25st%-25st%-15st%-4st%-10sn", "��������", "�����������", "����", "���", "������������"); // ���������� ��������� �������
    for (i = 0; i < num_tracks; i++) {
        fprintf(fp, "%-25st%-25st%-15st%-4dt%-10.2fn", tracks[i].name, tracks[i].artist, tracks[i].genre, tracks[i].year, tracks[i].duration); // ���������� ������ ���� � ���� � ���������� � ���������� �������� �����
    }
    fclose(fp);
    return 0; // ���������� 0 � ������ ��������� ���������� � ����
}

// ������� ��� ������ ������ � ������ �� ����� 
int read_from_file(Track tracks[], int* num_tracks, char* filename) {
    FILE* fp;
    int i;
    fp = fopen(filename, "r"); // ��������� ���� ��� ������ � ��������� ������
    if (fp == NULL) {
        printf("������ �������� �����!\n");
        exit(1);
    }
    fscanf(fp, "���������� ������: %d\n", num_tracks); // ��������� ���������� ������ �� �����
    for (i = 0; i < *num_tracks; i++) {
        fscanf(fp, "\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%f\n", tracks[i].name, tracks[i].artist, tracks[i].genre, &tracks[i].year, &tracks[i].duration); // ��������� ������ ���� �� ����� � ������� �������������� �������
    }
    fclose(fp);
    return 0;
}

// ������� ��� ���������� ����� ������ � ���� ������ 
int add_tracks(Track tracks[], int* num_tracks) {
    int num_new_tracks, i;
    printf("������� ����� ����� ������: ");
    scanf("%d", &num_new_tracks);
    getchar();
    if (*num_tracks + num_new_tracks > MAX_TRACKS) {
        printf("������: ������� ����� ������!n");
        return -1; // ���������� -1 � ������ ������ ������� �������� ���������� ������
    }
    for (i = 0; i < num_new_tracks; i++) {
        printf("������� ���������� � ������ %d:n", *num_tracks + i + 1);
        printf("������� �������� �����: ");
        fgets(tracks[*num_tracks + i].name, MAX_NAME, stdin);
        tracks[*num_tracks + i].name[strcspn(tracks[*num_tracks + i].name, "n")] = '0';
        printf("������� ��� �����������: ");
        fgets(tracks[*num_tracks + i].artist, MAX_ARTIST, stdin);
        tracks[*num_tracks + i].artist[strcspn(tracks[*num_tracks + i].artist, "n")] = '0';
        printf("������� ���: ");
        scanf("%d", &tracks[*num_tracks + i].year);
        getchar();
        printf("������� ����: ");
        fgets(tracks[*num_tracks + i].genre, MAX_GENRE, stdin);
        tracks[*num_tracks + i].genre[strcspn(tracks[*num_tracks + i].genre, "n")] = '0';
        printf("������� ������������ (� �������): ");
        scanf("%f", &tracks[*num_tracks + i].duration);
        getchar();
    }
    *num_tracks += num_new_tracks;
    return 0; // ���������� 0 � ������ ��������� ���������� ������
}
// ������� ��� ��������� ���������� � ����� 
int edit_track(Track tracks[], int num_tracks) {
    char name[MAX_NAME]; // ��������� ���������� �������� �����
    int i;
    printf("������� �������� ����� ��� ��������������: ");
    fgets(name, MAX_NAME, stdin); // ��������� �������� ����� � ������� fgets
    name[strcspn(name, "n")] = '0'; // ������� ������ �������� ������ �� ��������
    for (i = 0; i < num_tracks; i++) { // ���������� ��� ����� � �������
        if (strcmp(tracks[i].name, name) == 0) { // ���� �������� ����� ��������� � ���������
            printf("������� ����� ���������� ��� ����� %d:n", i + 1); // ������� ��������� � ������ �����
            printf("������� �������� �����: ");
            fgets(tracks[i].name, MAX_NAME, stdin);
            tracks[i].name[strcspn(tracks[i].name, "n")] = '0';
            printf("������� ��� �����������: ");
            fgets(tracks[i].artist, MAX_ARTIST, stdin);
            tracks[i].artist[strcspn(tracks[i].artist, "n")] = '0';
            printf("������� ���: ");
            scanf("%d", &tracks[i].year);
            getchar();
            printf("������� ����: ");
            fgets(tracks[i].genre, MAX_GENRE, stdin);
            tracks[i].genre[strcspn(tracks[i].genre, "n")] = '0';
            printf("������� ������������ (� �������): ");
            scanf("%f", &tracks[i].duration);
            getchar();
            return 0; // ���������� 0 � ������ ��������� �������������� �����
        }
    }
    printf("������: ���� �� ������!n");
    return -1; // ���������� -1 � ������, ���� ���� �� ������
}
// ������� ��� ������ ����� �� �������� 
int search_by_name(Track tracks[], int num_tracks) {
    char name[MAX_NAME];
    int i;
    printf("������� �������� ����� ��� ������: ");
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "n")] = '0';
    for (i = 0; i < num_tracks; i++) {
        if (strcmp(tracks[i].name, name) == 0) {
            printf("���� ������:n");
            printf("%-30s %-20s %-10d %-20s %-10.2fn", tracks[i].name, tracks[i].artist, tracks[i].year, tracks[i].genre, tracks[i].duration);
            return i; // ���������� ������ ���������� �����
        }
    }
    printf("������: ���� �� ������!n");
    return -1; // ���������� -1, ���� ���� �� ������
}
// ������� ��� ������ ������ �� ����� 
int search_by_genre(Track tracks[], int num_tracks) {
    char genre[MAX_GENRE];
    int i, count = 0;
    printf("������� ���� ��� ������: ");
    fgets(genre, MAX_GENRE, stdin);
    genre[strcspn(genre, "n")] = '0';
    printf("����� � ���� ������ '%s':n", genre);
    for (i = 0; i < num_tracks; i++) {
        if (strcmp(tracks[i].genre, genre) == 0) {
            printf("%-30s %-20s %-10d %-20s %-10.2fn", tracks[i].name, tracks[i].artist, tracks[i].year, tracks[i].genre, tracks[i].duration);
            count++;
        }
    }
    if (count == 0) {
        printf("�� ������� ������ � ������ '%s'!n", genre);
    }
    return count; // ���������� ���������� ��������� ������ � �������� ������
}

int main() {
    setlocale(LC_ALL, "RUS");
    system("chcp 1251");
    Track tracks[MAX_TRACKS];
    int num_tracks = 0, choice;
    while (1) {
        printf("\n����:\n");
        printf("1. �������� ����� �����\n");
        printf("2. �������� ����\n");
        printf("3. ����� �� ��������\n");
        printf("4. ����� �� �����\n");
        printf("5. ���������� �� ��������\n");
        printf("6. ���������� �� ����\n");
        printf("7. ������ ���� ������\n");
        printf("8. ��������� � ����\n");
        printf("9. ������ �� �����\n");
        printf("0. �����\n");
        printf("������� �����: ");
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
            printf("����� ����������� �� �����:\n");
            for (int i = 0; i < num_tracks; i++) {
                printf("%-30s %-20s %-10d %-20s %-10.2f\n", tracks[i].name, tracks[i].artist, tracks[i].year, tracks[i].genre, tracks[i].duration);
            }
            break;
        case 6:
            sort_by_year(tracks, num_tracks);
            printf("����� ����������� �� ����:\n");
            for (int i = 0; i < num_tracks; i++) {
                printf("%-30s %-20s %-10d %-20s %-10.2f\n", tracks[i].name, tracks[i].artist, tracks[i].year, tracks[i].genre, tracks[i].duration);
            }
            break;
        case 7:
            printf("��� �����:\n");
            for (int i = 0; i < num_tracks; i++) {
                printf("%-30s %-20s %-10d %-20s %-10.2f\n", tracks[i].name, tracks[i].artist, tracks[i].year, tracks[i].genre, tracks[i].duration);
            }
            break;
        case 8:
            save_to_file(tracks, num_tracks, "tracks.txt");
            printf("������ ��������� � ����!\n");
            break;
        case 9:
            read_from_file(tracks, &num_tracks, "tracks.txt");
            printf("������ ��������� �� �����!\n");
            break;
        case 0:
            exit(0);
        default:
            printf("������������ �����!\n");
        }
    }

    return 0;
}