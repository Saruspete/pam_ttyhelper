PREFIX = /

.PHONY: install


all: pam_ttyphelper.so

pam_ttyhelper.so:
	gcc -fPIC -DPIC -shared -rdynamic -o pam_ttyhelper.so pam_ttyhelper.c
	strip pam_ttyhelper.so

install: pam_ttyhelper.so
	cp pam_ttyhelper.so $(DESTDIR)$(PREFIX)/lib64/security/pam_ttyhelper.so

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib64/security/pam_ttyhelper.so
	grep -r pam_ttyhelper.so /etc/pam.d/
