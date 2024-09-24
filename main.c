#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define LETTER_LENGTH 52
#define DIGIT_LENGTH 10
#define SYMBOL_LENGTH 32
#define CHAR_LENGTH LETTER_LENGTH + DIGIT_LENGTH + SYMBOL_LENGTH

int main() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    char letter_pool[LETTER_LENGTH] = {0};
    char digit_pool[DIGIT_LENGTH] = {0};
    char symbol_pool[SYMBOL_LENGTH] = {0};
    char char_pool[CHAR_LENGTH] = {0};

    for (int i = 0; i < LETTER_LENGTH; i++) {
        letter_pool[i] = (char)(i + (i <= 25 ? 65 : 71));
    }

    for (int i = 0; i < DIGIT_LENGTH; i++) {
        digit_pool[i] = (char)(i + 48);
    }

    for (int i = 0; i < SYMBOL_LENGTH; i++) {
        if (i < 15) {
            symbol_pool[i] = i + 33;
        } else if (i < 22) {
            symbol_pool[i] = i + 43;
        } else if (i < 28) {
            symbol_pool[i] = i + 69;
        } else {
            symbol_pool[i] = i + 95;
        }
    }

    for (int i = 0; i < CHAR_LENGTH; i++) {
        if (i < DIGIT_LENGTH) {
            char_pool[i] = digit_pool[i];
        } else if (i < DIGIT_LENGTH + LETTER_LENGTH) {
            char_pool[i] = letter_pool[i - DIGIT_LENGTH];
        } else {
            char_pool[i] = symbol_pool[i - DIGIT_LENGTH - LETTER_LENGTH];
        }
    }

    int digit_start_index = 0;
    int digit_end_index = DIGIT_LENGTH - 1;
    int letter_start_index = DIGIT_LENGTH;
    int letter_end_index = DIGIT_LENGTH + LETTER_LENGTH - 1;
    int symbol_start_index = DIGIT_LENGTH + LETTER_LENGTH;
    int symbol_end_index = DIGIT_LENGTH + LETTER_LENGTH + SYMBOL_LENGTH - 1;

    while (1) {
        char choose;
        char char_eater;
        int input_too_much_char;
        do {
            input_too_much_char = 0;
            SetConsoleTextAttribute(std_output_handle, 11);
            printf("选择密码类型：\n");
            SetConsoleTextAttribute(std_output_handle, 7);
            printf(
                "1. 字母\n2. 字母 + 数字\n3. 字母 + 符号\n4. 字母 + 数字 + "
                "符号\n");
            SetConsoleTextAttribute(std_output_handle, 10);
            printf("输入序号并回车：");
            SetConsoleTextAttribute(std_output_handle, 7);

            choose = getchar();
            while ((char_eater = getchar()) != EOF && char_eater != '\n') {
                input_too_much_char = 1;
            }

            if ((choose != '1' && choose != '2' && choose != '3' &&
                 choose != '4') ||
                input_too_much_char) {
                SetConsoleTextAttribute(std_output_handle, 4);
                printf("选择错误，请重选！！！\n\n");
                SetConsoleTextAttribute(std_output_handle, 7);
            }
        } while ((choose != '1' && choose != '2' && choose != '3' &&
                  choose != '4') ||
                 input_too_much_char);

        unsigned int length;
        int length_is_correct;
        do {
            SetConsoleTextAttribute(std_output_handle, 11);
            printf("输入密码长度[至少为6]：");
            SetConsoleTextAttribute(std_output_handle, 7);

            length_is_correct = scanf("%d", &length);
            if (!length_is_correct || length < 6) {
                SetConsoleTextAttribute(std_output_handle, 4);
                printf("密码长度错误，请重新输入！！！\n\n");
                SetConsoleTextAttribute(std_output_handle, 7);
            }

            while ((char_eater = getchar()) != EOF && char_eater != '\n') {
            }
        } while (!length_is_correct || length < 6);

        int index_start;
        int index_end;

        if (choose == '1') {
            index_start = letter_start_index;
            index_end = letter_end_index;
        } else if (choose == '2') {
            index_start = 0;
            index_end = letter_end_index;
        } else if (choose == '3') {
            index_start = letter_start_index;
            index_end = symbol_end_index;
        } else {
            index_start = 0;
            index_end = symbol_end_index;
        }

        srand(time(NULL));
        int letter_fixed_index = rand() % length;
        int digit_fixed_index;
        int symbol_fixed_index;

        if (choose == '2') {
            do {
                digit_fixed_index = rand() % length;
            } while (digit_fixed_index == letter_fixed_index);
        } else if (choose == '3') {
            do {
                symbol_fixed_index = rand() % length;
            } while (symbol_fixed_index == letter_fixed_index);
        } else if (choose == '4') {
            do {
                digit_fixed_index = rand() % length;
            } while (digit_fixed_index == letter_fixed_index);

            do {
                symbol_fixed_index = rand() % length;
            } while (symbol_fixed_index == letter_fixed_index ||
                     symbol_fixed_index == digit_fixed_index);
        }

        char password[CHAR_LENGTH] = {'\0'};

        for (int i = 0; i < length; i++) {
            if (choose == '1') {
                password[i] = letter_pool[rand() % LETTER_LENGTH];
            } else if (choose == '2') {
                if (i == digit_fixed_index) {
                    password[i] = digit_pool[rand() % DIGIT_LENGTH];
                } else if (i == letter_fixed_index) {
                    password[i] = letter_pool[rand() % LETTER_LENGTH];
                } else {
                    password[i] = char_pool[rand() % (index_end + 1)];
                }
            } else if (choose == '3') {
                if (i == letter_fixed_index) {
                    password[i] = letter_pool[rand() % LETTER_LENGTH];
                } else if (i == symbol_fixed_index) {
                    password[i] = symbol_pool[rand() % SYMBOL_LENGTH];
                } else {
                    password[i] =
                        char_pool[rand() % (index_end - index_start + 1) +
                                  index_start];
                }
            } else {
                if (i == digit_fixed_index) {
                    password[i] = digit_pool[rand() % DIGIT_LENGTH];
                } else if (i == letter_fixed_index) {
                    password[i] = letter_pool[rand() % LETTER_LENGTH];
                } else if (i == symbol_fixed_index) {
                    password[i] = symbol_pool[rand() % SYMBOL_LENGTH];
                } else {
                    password[i] = char_pool[rand() % CHAR_LENGTH];
                }
            }

            if ((password[i] >= 48 && password[i] <= 57)) {
                SetConsoleTextAttribute(std_output_handle, 9);
            } else if ((password[i] >= 65 && password[i] <= 90) ||
                       (password[i] >= 97 && password[i] <= 122)) {
                SetConsoleTextAttribute(std_output_handle, 12);
            } else {
                SetConsoleTextAttribute(std_output_handle, 6);
            }
            putchar(password[i]);
        }

        printf("\n\n");
    }
}
