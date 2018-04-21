
all:
	gcc -fPIC -DPIC -shared -rdynamic -o pam_ttyhelper.so pam_ttyhelper.c
	strip pam_ttyhelper.so
