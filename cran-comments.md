## Test environments 

* rhub
    * Windows Server 2008 R2 SP1, R-devel, 32/64 bit
        * OK
        
    * Ubuntu Linux 16.04 LTS, R-release, GCC
        * 2 NOTEs
        
    * Fedora Linux, R-devel, clang, gfortran
        * 2 NOTEs
        
    * Debian Linux, R-devel, GCC ASAN/UBSAN
        * OK
        
* local
    * Debian Linux, R-devel
        * OK
    
    * Windows 7, R-devel, 32/64 bit
        * OK
        
* win-builder
    * R-devel
        * OK
        
    * R-release
        * 1 NOTE
        
----------

## R CMD check details

0 ERRORs | 0 WARNINGs | 2 NOTEs


* Ubuntu Linux 16.04 LTS, R-release, GCC

checking installed package size ... NOTE
    installed size is  7.4Mb
    sub-directories of 1Mb or more:
        libs   7.2Mb

checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Nathan Russell <russell.nr2012@gmail.com>’
  
License components with restrictions and base license permitting such:
  MIT + file LICENSE
File 'LICENSE':
  YEAR: 2017
  COPYRIGHT HOLDER: Nathan Russell
  
    
* Fedora Linux, R-devel, clang, gfortran
    
checking installed package size ... NOTE
    installed size is  7.4Mb
    sub-directories of 1Mb or more:
        libs   7.1Mb

checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Nathan Russell <russell.nr2012@gmail.com>’
  
License components with restrictions and base license permitting such:
  MIT + file LICENSE
File 'LICENSE':
  YEAR: 2017
  COPYRIGHT HOLDER: Nathan Russell
      
     
* win-builder

checking CRAN incoming feasibility ... NOTE
Maintainer: 'Nathan Russell <russell.nr2012@gmail.com>'

License components with restrictions and base license permitting such:
  MIT + file LICENSE
File 'LICENSE':
  YEAR: 2017
  COPYRIGHT HOLDER: Nathan Russell

----------
     
Re: License notes

I'm not sure what this means. This note does not currently show up on CRAN, 
and the only change I've made to the LICENSE file is updating the year from 
2016 to 2017. I was not able to reproduce this locally on Debian using 
R CMD check --as-cran, even with _R_CHECK_LICENSE=TRUE.


Re: libs sizes

This note appears on most platforms of the current CRAN version as well. The 
package uses template-heavy C++ code, so there is not much that can be done 
about this. 

----------

## Downstream dependencies

0 errors | 0 warnings | 0 notes

