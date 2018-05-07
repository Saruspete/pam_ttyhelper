PREFIX = /
VERSION = 1.1
ARCHIVE = pam_ttyhelper-$(VERSION)

.PHONY: install check-password

# from https://stackoverflow.com/questions/10858261/abort-makefile-if-variable-not-set
check_defined = \
    $(strip $(foreach 1,$1, \
        $(call __check_defined,$1,$(strip $(value 2)))))
__check_defined = \
    $(if $(value $1),, \
      $(error Undefined $1$(if $2, ($2))))



#
# Targets
#

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
	$(call check_defined, PAMTTYPWD, Set the password using envvar PAMTTYPWD)

# Create RPM archive
rpm: check-password archive
	mkdir -p ~/rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
	cp $(ARCHIVE).tar.gz ~/rpmbuild/SOURCES
	rpmbuild -ta --define "password $(PAMTTYPWD)" ~/rpmbuild/SOURCES/$(ARCHIVE).tar.gz

