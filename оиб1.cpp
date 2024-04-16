#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#define SIZE 100
#define SEQUENCE 8 //каждая буква кодируется 8 битами

//план действий для выполнения шиф и дешиф по алгоритму Меркля-Хеллмана
/*
1	Создадим закрытый ключ – это некая сверхвозрастающая последовательность а, то есть каждый её член больше суммы всех предыдущих.
2	Выберем модуль m, такой что он больше суммы элементов а.
3	Выберем множитель n, такой что m и n взаимно простые.
4	Создадим открытый ключ – это некоторая последовательность б, такая что б1 = а1 * n(mod m)
Зашифруем сообщение.
5	Каждый элемент сообщения представим в двоичном виде
6	Получим шифр
Расшифруем сообщение
7	Найдём k : (n * k % m = 1) – то есть k – обратное к n по модулю m
8	Расшифруем поэлементно сообщение
*/

//Функция генерирует закрытый ключ случайным образом и возвращает значение суммы элементов последовательности
int cr_pr_key(int* priv_key,int sum) {
	// 30 - просто число
	for (int i = 0; i < SEQUENCE; i++) {
		priv_key[i] = rand() % 30 + (sum + 1);
		sum += priv_key[i];
	}
	return sum;
}

//Вычисление взаимно простого n для m путём перебора (перебор реализован ниже)
int rel_prime(int n, int m) {
	while (n != m)
	{
		if (n > m) n -= m;
		else m -= n;
	}
	if (n == 1) return 1; // если нод == 1
	else return 0;
}

//Генерация открытого ключа
int cr_pub_key(int* priv_key, int* pub_key, int n, int m) {
	for (int i = 0; i < SEQUENCE; i++) {
		pub_key[i] = (priv_key[i] * n) % m;
	}
	return 0;
}

//Поиск длины введённого сообщения
int len(char* msg) {
	int s = 0;
	while (*msg++) s++;
	return s;
}

int main()
{
	srand(time(NULL));
	
	//1 step
	int* priv_key = (int*)calloc(SEQUENCE, sizeof(int));
	int sum = cr_pr_key(priv_key, 0);

	printf("Your private key: ");
	for (int i = 0; i < SEQUENCE; i++) {
		printf("%d ", priv_key[i]);
	}
	printf("\n");

	//2 step
	int m = (sum + 1) + rand() % 30;
	
	//3 step
	int n = 2;
	while (!rel_prime(n, m)) n++;
	

	//4 step
	int* pub_key = (int*)calloc(SEQUENCE, sizeof(int));
	cr_pub_key(priv_key, pub_key, n, m);

	printf("Your public key: ");
	for (int i = 0; i < SEQUENCE; i++) {
		printf("%d ", pub_key[i]);
	}
	printf("\n");

	//5 step
	//до 100 символов тк SIZE = 100
	char* msg = (char*)calloc(SIZE, sizeof(char));
	printf("Enter your message: ");
	gets(msg);

	int l_msg = len(msg);

	int* crypt = (int*)calloc(l_msg, sizeof(int));
	for (int i = 0; i < l_msg; i++) {
		int t = msg[i];
		int shifr = 0;
		int j = 0;
		while (t) {
			shifr += (t % 2) * pub_key[SEQUENCE - 1 - j];
			t /= 2;
			j++;
		}
		crypt[i] = shifr;
	}
	
	//6 step
	printf("Encrypted message: ");
	for (int i = 0; i < l_msg; i++) {
		printf("%d ", crypt[i]);
	}

	//7 step
	int k = 0, t = 0;
	while (!k) {
		if (n * t % m == 1) k = t; t++;
	}
	
	//8 step
	int* decrypt = (int*)calloc(l_msg, sizeof(int));

	for (int i = 0; i < l_msg; i++) {
		decrypt[i] = (crypt[i] * k)%m;
		//printf("%d ", decrypt[i]);
	}
	printf("\n");

	for (int x = 0; x < l_msg; x++) {
		double s = 0;
		for (int i = SEQUENCE - 1; i >= 0; i--) {
			//s = 0;
			if (priv_key[i] <= decrypt[x]) {
				
				s += pow(2, SEQUENCE - i-1);
				decrypt[x] -= priv_key[i];
			}
		}
		decrypt[x] = s;
	}

	printf("Decrypted message: ");
	for (int i = 0; i < l_msg; i++) {
		printf("%c", decrypt[i]);
	}

	free(priv_key);
	free(pub_key);
	free(msg);
	free(crypt);
	free(decrypt);	
}