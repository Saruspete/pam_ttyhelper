#
# Main tags
#
Name:		pam_ttyhelper
Summary:	Help recover a locked server through local tty
Version:	1.0
Release:	1%{?dist}

Packager:	Adrien Mahieux <adrien.mahieux@gmail.com>
License:	GPLv3
Group:		System Environment/Base

# Build parameters
BuildArch:	x86_64
BuildRequires:	pam-devel

Source0:	%{name}-%{version}.tar.gz

Requires:	pam
AutoReqProv: no

%define debug_package %{nil}

# Multi-line description
%description
Help recover a locked-down server through local tty (kvm/bmc/ilo/idrac...)

# =========================================================
# Preparation of the build environment
# =========================================================
%prep

# Usual setup macro: tar -xf %{Source0} && cd %{name}-%{version}
%setup

# Edit the password if provided in the command line
%if %{?password}0
	sed -Ee 's/^(#define TTY_PASS )".+"/\1 "%{password}"/' -i pam_ttyhelper.c
%endif

# =========================================================
# Compilation of the source
# =========================================================
%build
make %{?_smp_mflags}


# =========================================================
# Installation in buildroot
# =========================================================
%install

[[ -n "$RPM_BUILD_ROOT" ]] && [[ "$RPM_BUILD_ROOT" != "/" ]] && rm -fr "$RPM_BUILD_ROOT"
mkdir -p $RPM_BUILD_ROOT%{?prefix}

install -m644 -D pam_ttyhelper.so $RPM_BUILD_ROOT/lib64/security/pam_ttyhelper.so


# =========================================================
# Clean of the build environment
# =========================================================
%clean

[[ -n "$RPM_BUILD_ROOT" ]] && [[ "$RPM_BUILD_ROOT" != "/" ]] && rm -fr "$RPM_BUILD_ROOT"


# =========================================================
# Files to be embedded in final RPM
# =========================================================
%files
%defattr(-,root,root)
/lib64/security/pam_ttyhelper.so


# =========================================================
# Changelog
# =========================================================
%changelog
* Fri Apr 14 2017 Adrien Mahieux <adrien.mahieux@gmail.com>
- initial specfile
