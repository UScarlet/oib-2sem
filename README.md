# oib-2sem

Небольшое дополнение по поводу этих ЛР.

1 лр:
Источники
1.  Хабр - Криптография и алгоритмы - Алгоритмы поиска простых чисел - Теорема Ферма и тест Миллера-Рабина - https://habr.com/ru/post/468833/, NeverWalkAloner, 30.09.2019.
2.  Фоксфорд – Математика – Целые числа - Алгоритм Евклида - https://foxford.ru/wiki/matematika/algoritm-evklida.
3.  Криптография – Шифр Цезаря – Математическая модель - https://sites.google.com/site/kriptografics/sifr-cezara.
4.  ИНТУИТ - Криптографические методы защиты информации - Лекция «Алгоритмы с открытыми ключами» – Рюкзачный шифр - https://www.intuit.ru/studies/courses/13837/1234/lecture/31200?page=6.
5.  Матрица и алгоритм Евклида – Пример решения задачи - https://www.youtube.com/watch?v=M6iqKMqLIqs.

2 лр:
Важно следить, в какой сети выполняется лабораторная работа. Если захардкодить айпи ДОМАШНЕГО вайфая, то в главном здании, раздав МОБИЛЬНЫЙ интернет с телефона, показать лабу не получится. Нужно следить, какой айпи актуален в этой сети.

12 лр: всё давным давно придумали за нас, есть icacls

14 лр:
вспомогательные команды
sudo hping3 -d 120 -S -w 64 -p 80 --flood --rand-source "ваш айпи"
sudo sysctl -w net.ipv4.tcp_max_syn_backlog=100 //4096
sudo iptables -I INPUT -p tcp --syn --dport 80 -m connlimit --connlimit-above 10 -j DROP //ACCEPT

sudo ping -f "ваш айпи"
sudo sysctl net.ipv4.icmp_echo_ignore_all=1
