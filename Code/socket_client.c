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
 *  Δήλωση μεταβλητών
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
 *  Έλεγχος για εισαγωγή του port number και του host για σύνδεση στον socket server 
 */
	if (argc < 3)
	{
		fprintf(stderr, "usage %s portNo serverHost\n", argv[0]);
		exit(1);	
	}
/*  
 *  Άνοιγμα του socket client
 */ 
	portNo = atoi(argv[1]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		printError("Error on opening socket... socket() failed to execute\n");
/*  
 *  Ανάκτηση πληροφορίας για τον socket server host 
 */
	server = gethostbyname(argv[2]);
	if (server == NULL)
	{
		fprintf(stderr, "Error, host %s not found\n", argv[2]);
		exit(1);
	}
/*
 *  Παραμετροποίηση μέτρων για την TCP σύνδεση socket client με socket server
 */    
	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serverAddr.sin_addr.s_addr, server->h_length);
	serverAddr.sin_port = htons(portNo);	
/*  
 *  Σύνδεση σε socket server με ίδιο port number και ίδιο host 
 */
	connectionStatus = connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	if (connectionStatus < 0)
		printError("Error on connecting to socket server... connect() failed to execute\n");
/*
 * 	Αποστολή του id στον socket server
 */	
	pid = getpid();
	printf("[%d] : connected to socket server.\n", pid);
	sendStatus = send(sock, &pid, sizeof(int), 0);
	if (sendStatus < 0)
		printError("Error on sending data to socket server... send() failed to execute.\n");
/*
 * 	Εισαγωγή και αποστολή δεδομένων στον socket server και αναμονή για παραλαβή και εκτύπωση αποτελεσμάτων
 */	
	do
	{
/*
 * 	Εισαγωγή του μεγέθους n των διανυσμάτων X και Y
 */
		printf("Input the size of vectors X and Y : ");
		scanf("%d", &n);
/*
 *  Εισαγωγή του διανύσματος ακεραίων X
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
 * 	Εισαγωγή του διανύσματος ακεραίων Y 
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
 * 	Εισαγωγή της πραγματικής τιμής διπλής ακρίβειας "r" 
 */
		printf("Input a value \"r\" of double range : ");
		scanf("%lf", &r);
/*
 * 	Εκτύπωση των δεδομένων και των επιλογών του μενού 
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
 * 	Εισαγωγή, επιβεβαίωση και αποστολή της έγκυρης επιλογής από το μενού στον socket server 
 */
		checkChoice(&choice);
		sendStatus = send(sock, &choice, sizeof(int), 0);
			if (sendStatus < 0)
				printError("Error on sending data to socket server... send() failed to execute.\n");
/*
 * 	Αποστολή των δεδομένων, στον socket server
 */
		if (choice != 4)
		{
/*
 * 	Αποστολή του μεγέθους n των διανυσμάτων X και Y, στον socket server
 */
			printf("Sending data to socket server, waiting for results...\n");
			sendStatus = send(sock, &n, sizeof(int), 0);
			if (sendStatus < 0)
				printError("Error on sending data to socket server... send() failed to execute.\n");
/*
 * 	Αποστολή της πραγματικής τιμής διπλής ακρίβειας "r", στον socket server
 */
			sendStatus = send(sock, &r, sizeof(double), 0);
			if (sendStatus < 0)
				printError("Error on sending data to socket server... send() failed to execute.\n");
/*
 * 	Αποστολή του διανύσματος X, στον socket server
 */			
			sendStatus = send(sock, X, n * sizeof(int), 0);
			if (sendStatus < 0)
				printError("Error on sending data to socket server... send() failed to execute.\n");
/*
 * 	Αποστολή του διανύσματος Y, στον socket server
 */	
			sendStatus = send(sock, Y, n * sizeof(int), 0);
				if (sendStatus < 0)
					printError("Error on sending data to socket server... send() failed to execute.\n");
		}
/*
 *  Παραλαβή επιθυμητών αποτελεσμάτων από τον socket server και εκτύπωση  
 */
		switch (choice)
		{
/*  [1] Inner product of X * Y
 *  Παραλαβή αποτελέσματος του εσωτερικού γινομένου Χ * Y από τον socket server και εκτύπωση  
 */
			case 1 :
				recvStatus = recv(sock, &recvResults1, sizeof(int), 0);
				if (recvStatus < 0)
					printError("Error on receiving results from socket server... recv() failed to execute.\n");
				printf("\n---------------- Results -----------------\n");
				printf("Inner product X * Y : %d\n\n", recvResults1);
				break;
/*  [2] Average value of each vector
 *  Παραλαβή αποτελεσμάτων των μέσων όρων των διανυσμάτων Χ και Y από τον socket server και εκτύπωση  
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
 *	Παραλαβή αποτελεσμάτων του διανύσματος πραγματικών αριθμών r * (Χ + Υ)από τον socket server και εκτύπωση 		
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
 *  Έλεγχος επιλογής εξόδου από το μενού και τερματισμού σύνδεσης με τον socket server
 */
	} while (choice != 4);
/*  
 *  Κλείσιμο του socket client
 */
	closeStatus = close(sock);
	if (closeStatus < 0)
		printError("Error on closing socket... close() failed to execute\n");
/*  
 *  Αποδέσμευση μνήμης των διανυσμάτων Χ, Υ και r * (X + Y)
 */
	free(X);
	free(Y);
	free(recvResults3);

	return 0;
}

/*  
 *  Εκτύπωση σφάλματος σε περίπτωση αποτυχίας εκτέλεσης κάποιας συνάρτησης 
 */
void printError(char *error_msg)
{
	fprintf(stderr, "%s\n", error_msg);
	exit(1);
}

/*  
 *  Εκτύπωση των δεδομένων 
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
 *  Έλεγχος για τυχόν εισαγωγή άκυρης επιλογής από το μενού (έγκυρες επιλογές 1-4)
 */
void checkChoice(int *ptrChoice)
{
	do
	{
		printf("Input a choice from Menu : ");
		scanf("%d", ptrChoice);
	} while (*ptrChoice < 1 || *ptrChoice > 4);
}