#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>

pthread_mutex_t lock; // creating a mutex lock, as global
void* withdraw(void* amount);
void* deposit(void* amount);

int my_balance = 100; // this is a global variable to store

// this function returns the balance
int get_balance(){
	printf("Your balance is ..%d\n", my_balance);
	usleep(250000); // sleep for 250 ms
	return my_balance;
}
// function to set balance
void set_balance(int new_balance){
	printf(" This is the newb balance %d\n", new_balance); // this printing to the terminal.
	my_balance = new_balance;
	usleep(250000);
	printf("New balance has been successfully set: %d \n", my_balance);
}


int main(){
	pthread_t thread1, thread2;
	int withdraw_amount = 10;
	int deposit_amount = 10;
	int res;
	pthread_mutex_init(&lock, NULL);
	// Creating the Withdrawl thread.
	res = pthread_create(&thread1, NULL, withdraw, &withdraw_amount);
	assert(res == 0);

	res = pthread_create(&thread2, NULL, deposit, &deposit_amount);
	assert(res == 0);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("the new resulting balance is %d\n", my_balance);
	return 0;
}

void* deposit(void* amount){
	// to see t
	pthread_mutex_lock(&lock);
	int balance = get_balance();
	balance =  *(int*)amount + balance;
	set_balance(balance);
	pthread_mutex_unlock(&lock);
	return NULL;
}


void* withdraw(void* amount){
	pthread_mutex_lock(&lock);
	int balance = get_balance();
	balance = balance - *(int*)amount;
	printf(" this is the new balance value %d\n", balance);
	set_balance(balance);
	pthread_mutex_unlock(&lock);
	printf(" this is after set_balance call %d\n", my_balance);
	return NULL;
}
