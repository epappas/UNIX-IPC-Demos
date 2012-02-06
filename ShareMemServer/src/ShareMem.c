/*
 ============================================================================
 Name        : ShareMemServer.c
 Author      :
 Version     :
 Description : Λειτουργικά Συστήματα (ΗΥ-345) Χειμερινό Εξάμηνο 2011 Άσκηση 2 - Server
 ============================================================================
 */

#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "GameServer.h"
#include "Client.h"


int main(int argc, char *argv[])
{

	return 0;
}

void gameServerInitiator()
{
	//Generate an IPC key for the semaphore set and the shared
	//memory segment.  Typically, an application specific path and
	//id would be used to generate the IPC key.
	gameServer.semKey = ftok(SEMKEYPATH, SEMKEYID);
	if (gameServer.semKey == (key_t) -1)
	{
		printf("main: Server::ftok() for sem failed\n");
		return;
	}
	gameServer.shmKey = ftok(SHMKEYPATH, SHMKEYID);
	if (gameServer.shmKey == (key_t) -1)
	{
		printf("main: Server::ftok() for shm failed\n");
		return;
	}

	//Get the already created semaphore ID associated with key.
	//If the semaphore set does not exist, then it will not be
	// created, and an error will occur.
	gameServer.semId = semget(gameServer.semKey, NUMSEMS, 0666);
	if (gameServer.semId == -1)
	{
		printf("main: Server::semget() failed\n");
		return ;
	}

	//Get the already created shared memory ID associated with key
	//If the shared memory ID does not exist, then it will not be
	//created, and an error will occur.
	gameServer.shmId = shmget(gameServer.shmKey, SIZEOFSHMSEG, 0666);
	if (gameServer.shmId == -1)
	{
		printf("main: Server::shmget() failed\n");
		return;
	}

	//Attach the shared memory segment to the client process.
	gameServer.shmAddr = shmat(gameServer.shmId, NULL, 0);
	if (gameServer.shmAddr == NULL)
	{
		printf("main: Server::shmat() failed\n");
		return;
	}

	return;
}

void gameServerDestructor()
{

	return;
}


void *gameServerConstructor(void *arg)
{
	//initiator first
	gameServerInitiator();



	//Create Playground Thread
	gameServer.gsFPlaygroundID = pthread_create( &gameServer.gsFPlayground, NULL, gameServerFlushPlayground, NULL);
	//Create Gold Raise Thread
	gameServer.gsRGoldID = pthread_create( &gameServer.gsRGold, NULL, gameServerRaiseGold, NULL);
	//Create Clients' Check status
	gameServer.gsCClientID = pthread_create( &gameServer.gsCClient, NULL, gameServerClientCheck, NULL);

	// ( true != NOT(true != Not(true) ) ) == true
	if( gameServer.gsFPlaygroundID != !(gameServer.gsRGoldID != !(gameServer.gsCClientID != 0) ) )
	{
		fprintf(stderr,"Couldn't Create Processes!");
		//Free mem, segmants & semaphones
		gameServerDestructor();
		_exit(1); //Just in case
		exit(1);
	}

	return (void *) NULL;
}



void *gameServerRaiseGold(void *arg)
{

	sleep(2);
	return (void *) NULL;
}

void *gameServerFlushPlayground(void *arg)
{

	sleep(1);
	return (void *) NULL;
}

void *gameServerClientCheck(void *arg)
{

	sleep(1);
	return (void *) NULL;
}

void clientInitiator(int i)
{
	//Generate an IPC key for the semaphore set and the shared
	//memory segment.  Typically, an application specific path and
	//id would be used to generate the IPC key.
	gameClients[i].semKey = ftok(SEMKEYPATH, SEMKEYID);
	if (gameServer.semKey == (key_t) -1)
	{
		printf("main: Server::ftok() for sem failed\n");
		return;
	}
	gameClients[i].shmKey = ftok(SHMKEYPATH, SHMKEYID);
	if (gameServer.shmKey == (key_t) -1)
	{
		printf("main: Client[%d]::ftok() for shm failed\n",i);
		return;
	}

	//Get the already created semaphore ID associated with key.
	//If the semaphore set does not exist, then it will not be
	// created, and an error will occur.
	gameClients[i].semId = semget(gameClients[i].semKey, NUMSEMS, 0666);
	if (gameServer.semId == -1)
	{
		printf("main: Client[%d]::semget() failed\n",i);
		return ;
	}

	//Get the already created shared memory ID associated with key
	//If the shared memory ID does not exist, then it will not be
	//created, and an error will occur.
	gameClients[i].shmId = shmget(gameClients[i].shmKey, SIZEOFSHMSEG, 0666);
	if (gameServer.shmId == -1)
	{
		printf("main: Client[%d]::shmget() failed\n",i);
		return;
	}

	return;
}

