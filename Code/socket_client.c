#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

void printError(char *error_msg);
void printData(int n, int *X, int *Y, double r, int pid);
void checkChoice(int *ptr_choice);

int main (int argc, char *argv[])
{
/*  
 *  Variable Declaration
 */
	int i;
	int sock, portNo, pid;
	int connectionStatus, sendStatus, recvStatus, closeStatus;
	int recvResults1;
	int n, choice;
	int *X, *Y;
	double r;
	double recvResults2[2];
	double *recvResults3;
	struct sockaddr_in serverAddr;
	struct hostent *server;
/*  
 *  Check for port number and host for connecting to the socket server 
 */
	if (argc < 3)
	{
		fprintf(stderr, "usage %s portNo serverHost\n", argv[0]);
		exit(1);	
	}
/*  
 *  Opening the socket client
 */ 
	portNo = atoi(argv[1]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		printError("Error on opening socket... socket() failed to execute\n");
/*  
 *  Retrieve information for the socket server host 
 */
	server = gethostbyname(argv[2]);
	if (server == NULL)
	{
		fprintf(stderr, "Error, host %s not found\n", argv[2]);
		exit(1);
	}
/*
 *  Parameterization for TCP connection between the socket client and socket server
 */    
	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serverAddr.sin_addr.s_addr, server->h_length);
	serverAddr.sin_port = htons(portNo);	
/*  
 *  Connect to the socket server with the same port number and host 
 */
	connectionStatus = connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	if (connectionStatus < 0)
		printError("Error on connecting to socket server... connect() failed to execute\n");
/*
 * 	Send the id to the socket server
 */	
	pid = getpid();
	printf("[%d] : connected to socket server.\n", pid);
	sendStatus = send(sock, &pid, sizeof(int), 0);
	if (sendStatus < 0)
		printError("Error on sending data to socket server... send() failed to execute.\n");
/*
 * 	Input and send data to the socket server, then wait to receive and print results
 */	
	do
	{
/*
 * 	Input the size n of vectors X and Y
 */
		printf("Input the size of vectors X and Y : ");
		scanf("%d", &n);
/*
 *  Input the integer vector X
 */
		X = (int *) malloc(n * sizeof(int));
		if (X == NULL)
			printError("Error on allocating memory...\n");
		printf("Input the %d elements of vector X\n", n);
		for (i = 0; i < n; i++)
		{
			printf("X[%d] : ", i);
			scanf("%d", &X[i]);
		}
/*
 * 	Input vector Y of integers 
 */		
		Y = (int *) malloc(n * sizeof(int));
		if (Y == NULL)
			printError("Error on allocating memory...\n");
		printf("Input the %d elements of vector Y\n", n);
		for (i = 0; i < n; i++)
		{
			printf("Y[%d] : ", i);
			scanf("%d", &Y[i]);
		}
/*
 * 	Input the double precision value "r" 
 */
		printf("Input a value \"r\" of double range : ");
		scanf("%lf", &r);
/*
 * 	Print the data and menu options 
 */
		system("clear"); 
		printf("\n---------------- Data ----------------\n");
		printData(n, X, Y, r, pid);
		printf("\n---------------- Menu ----------------\n");
		printf("[1] Inner product of X * Y\n");
		printf("[2] Average value of each vector\n");
		printf("[3] Product of r * (X + Y)\n");
		printf("[4] Exit\n");
/*
 * 	Input, validate, and send the valid menu choice to the socket server 
 */
		checkChoice(&choice);
		sendStatus = send(sock, &choice, sizeof(int), 0);
			if (sendStatus < 0)
				printError("Error on sending data to socket server... send() failed to execute.\n");
/*
 * 	Send data to the socket server
 */
		if (choice != 4)
		{
/*
 * 	Send the size n of vectors X and Y to the socket server
 */
			printf("Sending data to socket server, waiting for results...\n");
			sendStatus = send(sock, &n, sizeof(int), 0);
			if (sendStatus < 0)
				printError("Error on sending data to socket server... send() failed to execute.\n");
/*
 * 	Send the double precision value "r" to the socket server
 */
			sendStatus = send(sock, &r, sizeof(double), 0);
			if (sendStatus < 0)
				printError("Error on sending data to socket server... send() failed to execute.\n");
/*
 * 	Send vector X to the socket server
 */			
			sendStatus = send(sock, X, n * sizeof(int), 0);
			if (sendStatus < 0)
				printError("Error on sending data to socket server... send() failed to execute.\n");
/*
 * 	Send vector Y to the socket server
 */	
			sendStatus = send(sock, Y, n * sizeof(int), 0);
				if (sendStatus < 0)
					printError("Error on sending data to socket server... send() failed to execute.\n");
		}
/*
 * 	Receive the desired results from the socket server and print 
 */
		switch (choice)
		{
/*  [1] Inner product of X * Y
 * 	Receive the result of the inner product X * Y from the socket server and print 
 */
			case 1 :
				recvStatus = recv(sock, &recvResults1, sizeof(int), 0);
				if (recvStatus < 0)
					printError("Error on receiving results from socket server... recv() failed to execute.\n");
				printf("\n---------------- Results -----------------\n");
				printf("Inner product X * Y : %d\n\n", recvResults1);
				break;
/*  [2] Average value of each vector
 * 	Receive the results of the averages of vectors X and Y from the socket server and print  
 */
			case 2 :
				recvStatus = recv(sock, recvResults2, 2 * sizeof(double), 0);
				if (recvStatus < 0)
					printError("Error on receiving results from socket server (rpc client)... recv() failed to execute.\n");
				printf("\n---------------- Results -----------------\n");
				printf("Average value of vector X : %lf\n", recvResults2[0]);
				printf("Average value of vector Y : %lf\n\n", recvResults2[1]);
				break;
/*  [3] Product of r * (X + Y)
 *	Receive the results of vector r * (X + Y) from the socket server and print 		
 */
            case 3 :
				recvResults3 = (double *) malloc (n * sizeof(double));
				if (recvResults3 == NULL)
					printError("Error on allocating heap memory.\n");
				recvStatus = recv(sock, recvResults3, n * sizeof(double), 0);
				if (recvStatus < 0)
					printError("Error on receiving results from socket server... recv() failed to execute.\n");
				printf("\n---------------- Results -----------------\n");
				for (i = 0; i < n; i++)
					printf("r * (X + Y)[%d] : %lf\n", i, recvResults3[i]);
				printf("\n");
				break;
		}
/*  [4] Exit
 * 	Check the choice to exit from the menu and terminate the connection with the socket server
 */
	} while (choice != 4);
/*  
 * 	Close the socket client
 */
	closeStatus = close(sock);
	if (closeStatus < 0)
		printError("Error on closing socket... close() failed to execute\n");
/*  
 * 	Free the memory for vectors X, Y, and r * (X + Y)
 */
	free(X);
	free(Y);
	free(recvResults3);

	return 0;
}

/*  
 * 	Print an error message in case of function execution failure 
 */
void printError(char *error_msg)
{
	fprintf(stderr, "%s\n", error_msg);
	exit(1);
}

/*  
 * 	Print the data 
 */
void printData(int n, int *X, int *Y, double r, int pid)
{
	int i;

	printf("Id : %d\n", pid);
	printf("Size of vectors X and Y : %d\n", n);
	for (i = 0; i < n; i++)
		printf("X[%d] : %d \t Y[%d] : %d\n", i, X[i], i, Y[i]);
	printf("Double value r : %lf\n", r);
}

/*  
 * 	Check for invalid input choice from the menu (valid choices are 1-4)
 */
void checkChoice(int *ptrChoice)
{
	do
	{
		printf("Input a choice from Menu : ");
		scanf("%d", ptrChoice);
	} while (*ptrChoice < 1 || *ptrChoice > 4);
}
