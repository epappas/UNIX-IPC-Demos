/*
 * GameServer.h
 *
 */

#ifndef GAMESERVER_H_
#define GAMESERVER_H_

//---Includes
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

//---Variables & Definitions

//Path used on ftok for semget key
#define SEMKEYPATH "/tmp"
//Id used on ftok for semget key
#define SEMKEYID 1
//Path used on ftok for shmget key
#define SHMKEYPATH "/tmp"
/* Id used on ftok for shmget key    */
#define SHMKEYID 1
//Num of sems in created sem set
#define NUMSEMS 10
//Size of the shared mem segment
#define SIZEOFSHMSEG 50

//playground width & height
#define PlaygroundWidth 	10
#define PlaygroundHeight 	10



typedef struct GameServer
{
	pthread_t 	gsThread;
	int 		gsThreadID;
	pthread_t 	gsFPlayground;
	int		 	gsFPlaygroundID;
	pthread_t 	gsRGold;
	int		 	gsRGoldID;
	pthread_t 	gsCClient;
	int		 	gsCClientID;
	int 		rc;
	int 		semId;
	int			shmId;
	key_t 		semKey;
	key_t		shmKey;
	void 		*shmAddr;
} GameServer;

GameServer gameServer;

/**
 * Game PLayground
 */
int playground[PlaygroundHeight][PlaygroundWidth] = {0};

//---Functions

/**
 * The Game Server Constructor
 */
void *gameServerConstructor(void *);

/**
 * The Game Server Destructor
 */
void gameServerDestructor();
/**
 * A function that initiates the very first steps of the GameServer
 */
void gameServerInitiator();

/**
 * A thread function tha handle gold production
 */
void *gameServerRaiseGold(void *);

/**
 * A thred function that flushes the status of the playground
 */
void *gameServerFlushPlayground(void *);

/**
 * A thread that checks Clients
 */
void *gameServerClientCheck(void *);

#endif /* GAMESERVER_H_ */
