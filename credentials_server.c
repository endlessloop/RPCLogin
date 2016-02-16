/*
 * Author: Praveen Kumar
 * BITS ID: 2015HT12227
 */

#include "credentials.h"
#include <stdbool.h>

#define SUCCESS 100
#define FAILURE 0

static long registeredUserCount = 0;

/* Name: addUser
 * Desc: Addes a user to the database (users.db)
 * arg:  argp = user credentials
*/
void addUser(cred_in *argp) {
   FILE *fp = fopen("./users.db","ab");

   if(fp != NULL) {
       char data[512]  = "";

       strcpy(data,argp->username);
       strcat(data,"$");
       strcat(data,argp->password);
       strcat(data,"\n");
       fputs(data,fp);
       fclose(fp);
   }
}

/* Name: getLineCount
 * Desc: Returns the total number of registered users
*/
long getLineCount() {

   FILE *fp;
   char *line = NULL;
   size_t len = 0;
   ssize_t read;
   long lineCount = 0;

   fp = fopen("./users.db","r");
   if(fp == NULL){
      return 0;
   }

   while((read = getline(&line, &len, fp)) != -1) {
      lineCount++;
   }

    return lineCount;
}


/* Name: getRegisteredUserCount
 * Desc: Helper method to get the total registered user count
*/
long getRegisteredUserCount() {

  registeredUserCount = getLineCount();

  return registeredUserCount;
}

/* Name: isValidUser
 * Desc: Checks if the user has already been registered
 *       and if his credentials are matching
*/ 
bool isValidUser(cred_in *argp) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    bool validuser = 0;
    char data[512];
	
    strcpy(data,argp->username);
    strcat(data,"$");
    strcat(data,argp->password);
    strcat(data,"\n");

    fp = fopen("./users.db","r");
    if(fp == NULL){
	return validuser;
    }

    while((read = getline(&line, &len, fp)) != -1) {
	if(strcmp(line,data)==0){
	    validuser = 1;
	    break;
	}
    }

 return validuser;
}

/* Name: registerproc_1_svc
 * Desc: Handles client request for registering user
*/
cred_out *
registerproc_1_svc(cred_in *argp, struct svc_req *rqstp)
{
    static cred_out  result;

    if(!isValidUser(argp)) {
       addUser(argp);
       result.rescode = SUCCESS;
       registeredUserCount++;
    }else{
       result.rescode = FAILURE;
    }

  return &result;

}

/* Name: loginproc_1_svc
 * Desc: Handles client request to perfom user login
*/
cred_out *
loginproc_1_svc(cred_in *argp, struct svc_req *rqstp)
{
	static cred_out  result;

	if(isValidUser(argp)) {
	  result.rescode = SUCCESS;
          result.usercount = getRegisteredUserCount();
	}else {
	  result.rescode = FAILURE;
	}

  return &result;

}

