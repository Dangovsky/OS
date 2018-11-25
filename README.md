# OS
Для корректного запуска в одной дириктории с запускаемым файлом должен быть [log.txt](https://github.com/Dangovsky/OS/blob/master/log.txt).

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
Перед комипляцией: 
Как компилировать: 
```shell
gcc lab_4.c -pthread -o lab_4
```
