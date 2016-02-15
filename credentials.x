struct cred_in {
	char username[256];
	char password[256];
};
struct cred_out {
	long rescode;
	long usercount;
};
program CREDENTIALS_PROG {
	version CREDENTIALS_VERS {
		cred_out REGISTERPROC(cred_in) = 1;
		cred_out LOGINPROC(cred_in) = 2;
		} = 1;
} = 0x13451111;
