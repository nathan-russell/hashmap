## Test environments 
* rhub
    * Platform:   Windows Server 2008 R2 SP1, R-devel, 32/64 bit
        * OK
        
    * Platform:   Ubuntu Linux 16.04 LTS, R-release, GCC
        * sub-directories of 1Mb or more: libs   7.2Mb
        
    * Platform:   Fedora Linux, R-devel, clang, gfortran
        * sub-directories of 1Mb or more: libs   7.1Mb
        
    * Platform:   Debian Linux, R-devel, GCC ASAN/UBSAN
        * OK

## Resubmission 
This is a resubmission, where I have: 
* Used the correct MIT LICENSE template 
* Fixed the DESCRIPTION to begin with 'Provides...'


## Test environments
* local CentOS 7 (64-bit), R 3.2.3
* local Ubuntu 14.04 (64-bit), R 3.2.4
* travis-ci Ubuntu 12.04, R 3.2.4
* local Windows 7 (64-bit), R 3.2.3
* win-builder R version 3.3.0 beta

## R CMD CHECK results
There were no ERRORs or WARNINGs. The travis-ci 
build NOTEs that 'installed size is  6.2Mb', 
and win-builder NOTEs 'New submission'.

## Downstream dependencies
There are currently no downstream dependencies for this package.
