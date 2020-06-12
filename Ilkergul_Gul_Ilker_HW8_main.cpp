#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include <time.h>
#include <ctime>  
#include <iomanip>  
#include "Ilkergul_Gul_Ilker_HW8DynIntQueue.h"

using namespace std;

/******************************************************************************

Username = ilkergul 
Name, Surname = Ilker Gul
ID Number = 26352
Date = 05/09/2020
CS204 Eighth Homework
Purpose = To write a multithreaded C++ program that simulates a queue of customers
waiting in a store to pay their groceries

******************************************************************************/



struct cashier_no
{
	int cashier_number;
	int threshold_value;
	
	cashier_no::cashier_no()
	{
	 cashier_number = 0;
	 threshold_value = 0;
	}

	cashier_no::cashier_no(int num, int threshold)
	{
		cashier_number = num;
		threshold_value = threshold;
	}
};

struct checkout_time
{
	int min_checkout;
	int max_checkout;

	checkout_time::checkout_time()
	{
		min_checkout = 0;
		max_checkout = 0;
	}
	checkout_time::checkout_time(const int & min, const int & max)
	{
		min_checkout = min;
		max_checkout = max;
	}
};


/* --------Taken by the lecture slides-------- */
int random_range(const int & min, const int & max) 
{
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min,max);
	return distribution(generator);
}
/* --------Taken by the lecture slides-------- */

mutex queue_mutex;
//To lock the queue for preventing another reach from another thread at the same time
mutex cout_mutex;
//To lock the display sequence


void customers(const int & total_customer, const int & min_arrival, const int & max_arrival, HW8DynIntQueue & Shopping_queue)
{
	int id_count = 1;               // To check the id number of customers entered in the queue
	while(id_count <= total_customer)
	{
		time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
		struct tm *ptm = new struct tm; 
		localtime_s(ptm, &tt);

		queue_mutex.lock();
		Shopping_queue.enqueue(id_count);
		int i = Shopping_queue.getCurrentSize();
		queue_mutex.unlock();
		cout_mutex.lock();
		
		cout << "New customer with ID " << id_count << " has arrived (queue size is " 
			<< i << "): " << put_time(ptm,"%X") << endl;
		
		cout_mutex.unlock();
		
		id_count++;
		this_thread::sleep_for(chrono::seconds(random_range(min_arrival, max_arrival)));
		
	}
}

void cashier(const cashier_no & cashier_info , const checkout_time & time_values, HW8DynIntQueue & Shopping_queue, int & count, const int & total_customer)
{
	int customer_number = 0;
	this_thread::sleep_for(chrono::seconds(random_range(time_values.min_checkout, time_values.max_checkout)));
	//For the sleeping process
	if(cashier_info.cashier_number == 1)
	{
		
		while(count <= total_customer)
		{
			int queue_size_cashier = -1;
			queue_mutex.lock();
			if(!Shopping_queue.isEmpty())
			{
				
				Shopping_queue.dequeue(customer_number);
				queue_size_cashier = Shopping_queue.getCurrentSize();
				count ++;
			}
			queue_mutex.unlock();
			if(queue_size_cashier != -1)
			{
				time_t tt_initial = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt_initial); 
				cout_mutex.lock();
				cout << "Cashier " << cashier_info.cashier_number << " has started transaction with customer " 
					<< customer_number << " (queue size is " << queue_size_cashier << "): " << put_time(ptm,"%X") << endl;
				cout_mutex.unlock();
				this_thread::sleep_for(chrono::seconds(random_range(time_values.min_checkout, time_values.max_checkout)));

				time_t tt_last = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm1 = new struct tm; 
				localtime_s(ptm1, &tt_last); 

				cout_mutex.lock();
				cout << "Cashier " << cashier_info.cashier_number << " finished transaction with customer " 
					<< customer_number <<  " " << put_time(ptm1,"%X") << endl;
				cout_mutex.unlock();
			}			
		}		
	}
	else 
	{
		while(count <= total_customer)
		{
			int queue_size_cashier_2 = -1;
			queue_mutex.lock();
			if((!Shopping_queue.isEmpty()) && (!(Shopping_queue.getCurrentSize() < cashier_info.threshold_value)))
			{
				 
							
				Shopping_queue.dequeue(customer_number);
				queue_size_cashier_2 = Shopping_queue.getCurrentSize();
				count ++;
				
			}
			queue_mutex.unlock();
			if(queue_size_cashier_2 != -1)
			{
				time_t tt1 = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt1);
				cout_mutex.lock();
				cout << "Cashier " << cashier_info.cashier_number << " has started transaction with customer " 
					<< customer_number << " (queue size is " << queue_size_cashier_2 << "): " << put_time(ptm,"%X") << endl;
				
				cout_mutex.unlock();
				

				this_thread::sleep_for(chrono::seconds(random_range(time_values.min_checkout, time_values.max_checkout)));

				time_t tt_1 = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm1 = new struct tm; 
				localtime_s(ptm1, &tt_1); 
				
				cout_mutex.lock();
				cout << "Cashier " << cashier_info.cashier_number << " finished transaction with customer " 
					<< customer_number <<  " " << put_time(ptm1,"%X") << endl;
				cout_mutex.unlock();
			}
		}
			
	}
	
}

int main()
{
	int total_customer_count, cashier2_threshold, min_arrival,
		max_arrival, min_checkout_time, max_checkout_time;
	cout << "Please enter the total number of customers: ";
	cin >> total_customer_count;
	cout << "Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin >> cashier2_threshold;
	cout << "Please enter the inter-arrival time range between two customers:\n" << "Min: " ;
	cin >> min_arrival;
	cout << "Max: " ;
	cin >> max_arrival;
	cout << "Please enter the checkout time range of cashiers:\n" << "Min: " ;
	cin >> min_checkout_time;
	cout << "Max: " ;
	cin >> max_checkout_time;

	HW8DynIntQueue Shopping_queue;
	//Dynamic queue implementation is given in the homework folder
	checkout_time checkout_process(min_checkout_time, max_checkout_time);
	//To prevent passing the paramter limit in the thread
	cashier_no cashier_information1 (1, cashier2_threshold);
	//To give the number of the cashier
	cashier_no cashier_information2 (2, cashier2_threshold);
	int count = 1;

	time_t tt_start = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt_start); 
	cout << "Simulation starts: " << put_time(ptm,"%X") << endl; 
	//For giving the current time

	//Now I am creating the threads
	thread customers(&customers, total_customer_count, min_arrival, max_arrival, ref(Shopping_queue));
	thread cashier_1(&cashier, cashier_information1, checkout_process, ref(Shopping_queue), ref(count), total_customer_count);
	thread cashier_2(&cashier, cashier_information2, checkout_process, ref(Shopping_queue), ref(count), total_customer_count);

	//Now I am joining them to the main thread
	customers.join();
	cashier_1.join();
	cashier_2.join();

	//Again to display the current time
	time_t tt_end = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm1 = new struct tm; 
	localtime_s(ptm1, &tt_end); 
	cout << "End of the simulation ends: " << put_time(ptm1,"%X") << endl; 

	return 0;
}

// End of Homework 8
// Yours sincerely
// Ilker Gul
