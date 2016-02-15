/*
 * Author: Praveen Kumar
 * BITS ID: 2015HT12227
 */

#include "credentials.h"
#include <stdbool.h>

#define SUCCESS 100
#define FAILURE 0

static long registeredUserCount = 0;

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

long getRegisteredUserCount() {
  
  if(registeredUserCount != 0) {
    return registeredUserCount;
  }

  registeredUserCount = getLineCount();

  return registeredUserCount;
}

bool validUser(cred_in *argp) {
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


cred_out *
registerproc_1_svc(cred_in *argp, struct svc_req *rqstp)
{
	static cred_out  result;
	if(!validUser(argp)) {
	   addUser(argp);
	   result.rescode = SUCCESS;
           registeredUserCount++;
	}else{
	  result.rescode = FAILURE;
	}
	return &result;
}

cred_out *
loginproc_1_svc(cred_in *argp, struct svc_req *rqstp)
{
	static cred_out  result;

	if(validUser(argp)) {
	  result.rescode = SUCCESS;
          result.usercount = getRegisteredUserCount();
	}else {
	  result.rescode = FAILURE;
	}
	return &result;
}

