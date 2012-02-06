/*
 * Client.h
 *
 */

#ifndef CLIENT_H_
#define CLIENT_H_

//---Includes
#include <stdio.h>

//---Variables & Definitions

//playground width & height
#define MaxClients 	5


typedef struct GameClient
{
	//available moves
	int 		moves;
	//The Gold score
	int 		score;
	//Client's ID
	int 		id;
	int 		rc;
	int 		semId;
	int			shmId;
	key_t 		semKey;
	key_t		shmKey;
} GameClient;

int clientStaticCounter=0;

/**
 * Clients' Instances
 */
GameClient gameClients[MaxClients];

//---Functions

/**
 * The Client Constructor
 */
void *clientConstructor(void *);

/**
 * The Client Destructor
 */
void clientDestructor();
/**
 * A function that initiates the very first steps of the Client
 */
void clientInitiator();


/**
 * get Client's score
 */
int getClientScore(int id);

/**
 * adds Client's Score
 */
void addClientScore(int id, int score);

/**
 * sets Client's Score
 */
void setClientScore(int id, int score);

/**
 * get Client's Moves
 */
int getClientMoves(int id);

/**
 * sets Client's Score
 */
void setClientMoves(int id, int moves);

#endif /* CLIENT_H_ */
