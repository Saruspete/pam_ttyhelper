PREFIX = /
VERSION = 1.0
ARCHIVE = pam_ttyhelper-$(VERSION)

.PHONY: install check-password

all: pam_ttyhelper.so

pam_ttyhelper.so:
	gcc -fPIC -DPIC -shared -rdynamic -o pam_ttyhelper.so pam_ttyhelper.c
	strip pam_ttyhelper.so

clean:
	rm pam_ttyhelper.so

install: pam_ttyhelper.so
	cp pam_ttyhelper.so $(DESTDIR)$(PREFIX)/lib64/security/pam_ttyhelper.so

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib64/security/pam_ttyhelper.so
	grep -r pam_ttyhelper.so /etc/pam.d/

#
# Create an archive from the git content
#
archive:
	git archive --format=tar --prefix=$(ARCHIVE)/ master | gzip -c > $(ARCHIVE).tar.gz


#
# Package creation
#
check-password:
ifndef PAMTTYPWD
  $(error Set the password using the environment variable PAMTTYPWD)
endif

# Create RPM archive
rpm: check-password archive
	mkdir -p ~/rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
	cp $(ARCHIVE).tar.gz ~/rpmbuild/SOURCES
	rpmbuild -ta --define "password $(PAMTTYPWD)" ~/rpmbuild/SOURCES/$(ARCHIVE).tar.gz

