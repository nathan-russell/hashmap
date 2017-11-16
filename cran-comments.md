## Bugfix note 

This release (0.2.2, 2017-11-16) contains a fix for an issue in the previous 
release (0.2.1, 2017-11-15) which was causing a build error on macOS and 
Fedora + clang, due to the inclusion of a C++ TR1 header file. The problematic 
'#include' statements have been removed, and the revised version was able to be 
installed successfully on macOS, tested via rhub. 

## Release summary

This is a minor update which replaces the default hash table used internally 
on non-Solaris platforms in order to improve performance and reduce memory 
usage. 

## Test environments 

* rhub
    * Ubuntu Linux 16.04 LTS, R-release, GCC
        * 1 NOTE
        
    * Ubuntu Linux 16.04 LTS, R-devel, GCC
        * 1 NOTE
        
    * Debian Linux, R-devel, GCC
        * 1 NOTE
        
    * Debian Linux, R-patched, GCC
        * 1 NOTE
        
    * Debian Linux, R-devel, GCC ASAN/UBSAN
        * OK
        
    * Windows Server 2008 R2 SP1, R-patched, 32/64 bit
        * OK
        
    * macOS 10.11 El Capitan, R-release
        * OK
        
* local
    * Fedora Linux, R-release, clang
        * 1 NOTE
        
* win-builder
    * R-devel
        * OK
        
    * R-release
        * OK
        
    * R-oldrelease
        * 1 NOTE
        
----------

## R CMD check details

0 ERRORs | 0 WARNINGs | 2 NOTEs

* (All Linux platforms)

checking installed package size ... NOTE
  
* win-builder R-oldrelease
 
checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Nathan Russell <russell.nr2012@gmail.com>’
  
License components with restrictions and base license permitting such:
  MIT + file LICENSE
File 'LICENSE':
  YEAR: 2017
  COPYRIGHT HOLDER: Nathan Russell
  
----------
     
Re: License notes

This note showed up for my previous release on only win-builder R-release, 
and now shows up on only win-builder R-oldrelease, so I'm assuming this is a 
quirk specific to R 3.3.

Re: libs sizes

This note appears on most platforms of the current CRAN version as well. The 
package uses template-heavy C++ code, so there is not much that can be done 
about this. 

----------

## Reverse dependencies

0 errors | 0 warnings | 0 notes
