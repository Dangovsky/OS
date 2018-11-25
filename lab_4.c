#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_READERS 10000
#define MAX_WRITERS 10000
#define TIME_SCALER 7 

//глобальные константы для удобства генерации кравсивого вывода

pthread_mutex_t a_mutex;
sem_t a_sem;

int readers_state[MAX_READERS];
int writers_state[MAX_WRITERS];

int r_count, w_count, r_max;
int r_read_cnt, r_wait_cnt, w_wait_cnt, w_write_cnt;
int r_n = 1, w_n = 1;

void *read_p();
void *write_p();

int main(){
	//ввод кол-ва добавлятелей, поисковиков и удалятелей
	printf("Введите N W K: ");
	scanf("%d %d %d", &r_count, &w_count, &r_max);
	//объявление потоков
	pthread_t write_thread[r_count];
	pthread_t read_thread[w_count];
	//для вывода времени
	struct tm *tm_ptr;
 	time_t the_time;
 	(void)time(&the_time);
 	tm_ptr = gmtime(&the_time);
	//мьютекс и семафор
	pthread_mutex_init(&a_mutex, NULL);
	sem_init(&a_sem, 0, r_max);
	//cоздание потоков
        int i;
	for(i=1; i<=r_count; i++){	
		pthread_create(&write_thread[i], NULL, write_p, &i);
	}
	for(i=1; i<=w_count; i++){	
		pthread_create(&read_thread[i], NULL, read_p, &i);
	}
        //запуск потоков
	for(i=1; i<=w_count; i++){		
		pthread_join(read_thread[i], NULL);
	}
	for(i=1; i<=r_count; i++){
		pthread_join(write_thread[i], NULL);
	}
	return 0;
}

//вспомогательная функция для вывода состояния системы
void write_state(){
        int i;
	printf(" | ");
	if (w_write_cnt){
		printf("writer %d is writing. ", w_write_cnt);
	}
	if (w_wait_cnt)
	{		
		if (w_wait_cnt > 1)
			printf("writers ");
                else
			printf("writer ");
		for (i = 1; i <= w_count; i++){
			if (writers_state[i]) printf("%d ", i);
		}		
		printf("waiting. ");
	}
	if (r_read_cnt)
	{		
		if (r_read_cnt > 1)
			printf("readers ");
                else
			printf("reader ");
		for (i = 1; i <= r_count; i++){
			if (readers_state[i] == 2) printf("%d ", i);
		}		
		printf("reading. ");
	}
	if (r_wait_cnt)
	{		
		if (r_wait_cnt > 1)
			printf("readers ");
                else
			printf("reader ");
		for (i = 1; i <= r_count; i++){
			if (readers_state[i] == 1) printf("%d ", i);
		}		
		printf("waiting. ");
	}
	printf("\n");
}

//поток-читатель
void *read_p(int n1){        
	int n = r_n++;
       	sleep(rand()%(TIME_SCALER));
	//для вывода времени
	struct tm *tm_ptr;
 	time_t the_time;
 	(void)time(&the_time);
 	tm_ptr = gmtime(&the_time);
        //вывод в консоль и изменение глобальных констант
	printf("%02d:%02d:%02d reader #%d wanna read.    ",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, n);
	write_state();
	readers_state[n] = 1;
        r_wait_cnt++;
	//проверка, что писатель не захватил мьютекс
	pthread_mutex_lock(&a_mutex);
	pthread_mutex_unlock(&a_mutex);
        //уменьшение/ожидание семафора
	sem_wait(&a_sem);
        //вывод в консоль и изменение глобальных констант
	readers_state[n] = 0;
	r_wait_cnt--;
	printf("%02d:%02d:%02d reader #%d start reading. ",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, n);
	write_state();
	readers_state[n] = 2;
	r_read_cnt++;
	//"чтение"
	sleep(rand()%(TIME_SCALER));
        //вывод в консоль и изменение глобальных констант
	r_read_cnt--;
	readers_state[n] = 0;
	printf("%02d:%02d:%02d reader #%d stop reading.  ",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, n);
	write_state();
	//увеличение семафора
        sem_post(&a_sem);
}

void *write_p(int n1){
        int n = w_n++;
	sleep(rand()%(TIME_SCALER));
        //для времени
	struct tm *tm_ptr;
 	time_t the_time;
 	(void)time(&the_time);
 	tm_ptr = gmtime(&the_time);
	//вывод в консоль и изменение глобальных констант
	printf("%02d:%02d:%02d writer #%d wanna write.   ",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, n);
	write_state();
        w_wait_cnt++;
	writers_state[n] = 1;
	//захват мьютекса
	pthread_mutex_lock(&a_mutex);
        //проверка, что все семафор отпущен всеми читателями
	int sem_v = 1;
        while(sem_v != r_max)
		sem_getvalue(&a_sem, &sem_v);
	//вывод в консоль и изменение глобальных констант
	w_wait_cnt--;
	writers_state[n] = 0;
	printf("%02d:%02d:%02d writer #%d start writing. ",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, n);
	write_state();
	w_write_cnt = n;
	//"запись"
	sleep(rand()%(TIME_SCALER));
	//вывод в консоль и изменение глобальных констант
	w_write_cnt = 0;
	printf("%02d:%02d:%02d writer #%d stop writing.  ",tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec, n);
	write_state();
	//отпускание мьютекса
	pthread_mutex_unlock(&a_mutex);
}
