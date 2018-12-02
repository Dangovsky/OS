# OS
Для корректного запуска 1, 2 и 3 лабораторной в одной дириктории с запускаемым файлом должен быть [log.txt](https://github.com/Dangovsky/OS/blob/master/log.txt).

Как запускать:
```shell
./lab_*
```
## [lab_1](https://github.com/Dangovsky/OS/blob/master/lab_1.sh)
Как запускать:
```shell
./lab_1.sh
```
## [lab_2](https://github.com/Dangovsky/OS/blob/master/lab_2.c)
Как компилировать: 
```shell
gcc lab_2.c -o lab_2
```
## [lab_3](https://github.com/Dangovsky/OS/blob/master/lab_3.s)
Перед комипляцией: 
```shell
sudo apt-get install gcc-multilib
```
Как компилировать: 
```shell
gcc -m32 -nostartfiles lab_3.s -o lab_3
```
## [lab_4](https://github.com/Dangovsky/OS/blob/master/lab_4.c)
Как компилировать: 
```shell
gcc lab_4.c -pthread -o lab_4
```
После запуска ввести параметры, например:
```shell
5 9 3
```
Вывод не всегда корректен потому, что потоки перехватывают управление друг у друга и мешают красивому выводу

## [lab_5](https://github.com/Dangovsky/OS/blob/master/lab_5.c)
Перед комипляцией: 
```shell
sudo apt-get update && sudo apt-get install libfuse-dev
```
Как компилировать: 
```shell
gcc -Wall -o lab_5 lab_5.c `pkg-config fuse --cflags --libs`
```
Как запускать:
```shell
mkdir fuse
./lab_5 -d -s ./fuse
```
После запуска открыть другой терминал, перейти в дирикторию fuse и использовать стандартые команды навигации файловой системы, например:
```shell
ls
cd *
nano *
vim *
```
Как размонтировать папку:
```shell
fusermount -u ./fuse
```
