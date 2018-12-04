# OS
Для корректного запуска 1, 2 и 3 лабораторной в одной дириктории с запускаемым файлом должен лежать [log.txt](https://github.com/Dangovsky/OS/blob/master/log.txt).

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
Как запускать:
```shell
./lab_2
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
Как запускать:
```shell
./lab_3
```
## [lab_4](https://github.com/Dangovsky/OS/blob/master/lab_4.c)
Как компилировать: 
```shell
gcc lab_4.c -pthread -o lab_4
```
Как запускать:
```shell
./lab_4
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
Как размонтировать:
```shell
fusermount -u ./fuse
```
## [lab_6](https://github.com/Dangovsky/OS/blob/master/lab_6.c)
Перед комипляцией: 
```shell
sudo apt-get update && sudo apt-get install collectd
```
В файле `/etc/collectd/collectd.conf`:
* раскомментировать `BaseDir`, `Plugin`, `LoadPlugin csv`, `LoadPlugin unixsock`, `LoadPlugin network`,
* раскомментировать и заменить `localhost` на `this-host`.
* раскомментировать тег `<Plugin csv>` и `<Plugin unixsock>` со всем содержимым.  
* раскомментировать тег `<Plugin network>` и его внутренний тег `<Server >`, адрес заменить на (0.0.0.0)

Как компилировать: 
```shell
gcc -o lab_6 lab_6.c
```
Как запускать:
```shell
./lab_6 тест 1179574444:123:456
```
После запуска перейти в `/var/lib/collectd/csv/this-host/stdout` и найти там фаил с названием `load-тест-yyyy-mm-dd` где `yyyy-mm-dd` - сегодняшняя дата. В нем будет наша запись.
