/*
 * Author: Praveen Kumar
 * BITS ID: 2015HT12227
 */

#include "credentials.h"

/* Name: loginUser
 * Desc: Handles user login request
*/
void
loginUser(char *host) {

       CLIENT *clnt;

       cred_out  *result;
       cred_in  login;

       char username[256];
       char password[256];

       // Create the client
       clnt = clnt_create (host, CREDENTIALS_PROG, CREDENTIALS_VERS, "udp");
       if (clnt == NULL) {
               clnt_pcreateerror (host);
               exit (1);
       }

       printf("\n============================ Login ==============================\n");
       printf("Enter Username: ");
       scanf("%s", username);

       printf("Enter Password: ");
       scanf("%s%*c", password);

       strcpy(login.username,username);
       strcpy(login.password,password);

       result = loginproc_1(&login, clnt);
       if (result == (cred_out *) NULL) {
           clnt_perror (clnt, "call failed");
       }

       if(result->rescode != 0){
           printf("\nWelcome %s !\n",username);
	   if(strcmp(username,"admin")==0) {
		printf("\nNumber of registered Users are: %ld\n", (result->usercount - 1));
	   }
	   exit(0);
       }else {
           printf("Invalid user. Try again!");
       }

       clnt_destroy(clnt);
}

/* Name: registerUser
   Desc: Handles user registration request
*/
void
registerUser(char *host)
{
	CLIENT *clnt;

	cred_out  *result;
	cred_in  uregister;

	char req;
	char username[256];
	char password[256];

	// Create the client
	clnt = clnt_create (host, CREDENTIALS_PROG, CREDENTIALS_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	printf("\n============================ Registration ==========================\n");

	printf("Enter Username: ");
	scanf("%s", username);

	printf("Enter Password: ");
	scanf("%s%*c", password);

	strcpy(uregister.username,username);
	strcpy(uregister.password,password);

	result = registerproc_1(&uregister, clnt);
	if (result == (cred_out *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	if(result->rescode != 0) {
	  printf("\n Registration Successful !\n");
	  printf("Do you wish to login? (Y/N): ");
	  scanf("%c",&req);
	  if(req == 'Y' || req == 'y'){
	     loginUser(host);
	  }else {
	     exit(0);
          }

	}else {
	  printf("Username already exists. Try a different one\n");
	} 
	
	clnt_destroy (clnt);
}

int
main (int argc, char *argv[])
{
	char *host;
	int type;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}

	host = argv[1];

	while(type != 3 ) {
	   system("clear"); 
	   printf("Welcome Guest!!\n");
	   printf("1. Register\n");
	   printf("2. Login\n");
	   printf("3. Exit\n");
	   printf("Enter Choice: ");
           scanf("%d",&type);
	
	   switch(type){
		case 1:
		  registerUser(host);
		break;

		case 2:
		  loginUser(host);
		  break;

		case 3:
		break;

		default:
		  printf("Invalid Option\n");
		  type = 3;
		  break;
	    }	
	}

	exit (0);
}
