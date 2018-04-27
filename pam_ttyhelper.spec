Name:		pam_ttyhelper
Version:	1.0
Release:	1%{?dist}
Summary:	Help recover a locked server through local tty

Group:		System Environment/Base
License:	GPLv3
URL:		
Source0:	

BuildRequires:	pam-devel
Requires:	pam

%description
Help recover a locked-down server through local tty (kvm/bmc/ilo/idrac...)

%prep
%setup -q

%build
make %{?_smp_mflags}


%install
%make_install


%files
%doc



%changelog

