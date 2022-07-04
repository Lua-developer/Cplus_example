#include<stdio.h>
#include<mutex>
#include<thread>
#include<time.h>
#include<iostream>
using namespace std;
enum ROLE {PRODUCER, CONSUMER};

typedef struct {
	char mark;
	mutex* pCS;
	char* pTurn;
} ThreadParam;
#define THREAD_EXIT_CODE 7
void Thread_A(ThreadParam* pParam);
void Thread_B(ThreadParam* pParam);

void main() {
	ThreadParam t1_mark, t2_mark;
	mutex crit;
	t1_mark.mark = 'A';
	t2_mark.mark = 'B';
	t1_mark.pCS = &crit;
	t2_mark.pCS = &crit;
	thread t1(Thread_A, &t1_mark);
	thread t2(Thread_B, &t2_mark);
	char mark = 'M';
	for (int i = 0; i < 100; i++) {
		crit.lock();
		printf("thread_main...");
		for (int j = 0; j < 50; j++) {
			cout << mark;
		}
		printf("\n");
		crit.unlock();
	}
	t1.join();
	t2.join();
}

void Thread_A(ThreadParam* pParam)
{
	char mark = pParam->mark;
	for (int i = 0; i < 100; i++) {
		pParam->pCS->lock();
		cout << "Thread_A Running";
		for (int j = 0; j < 50; j++) {
			cout << mark;
		}
		cout << endl;
		pParam->pCS->unlock();
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

void Thread_B(ThreadParam* pParam)
{
	char mark = pParam->mark;
	for (int i = 0; i < 100; i++) {
		cout << "Thread_B Running";
		pParam->pCS->lock();
		for (int j = 0; j < 50; j++) {
			cout << mark;
		}
		cout << endl;
		pParam->pCS->unlock();
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}
