<div id="top"></div>
<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#output">Output</a></li>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#usage">Usage</a></li>
      </ul>
    </li>
    <li><a href="#license">License</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

This projects implements a Super Maximal Repeat Algorithm for finding all occurrences of a super maximal repeat. The repeat algorithm works with the below implementation
* Compute suffix array and rank array using Manber-Myers construction of suffix arrays and saving the group array.
* Compute the adjacent lcp array using the suffix array and rank array.
* Compute the super maximal repeats with a post order visit of a simulated suffix tree. Only processing relevant super maximal nodes.
* Burrows Wheeler Transform was also implemented within the library.

Current todos
* I would like to implement an extension that does not require a G prime array to be initialized. Current implementation does use this array that may be a little unnecessary.

Interesting implementation designs
* An extension to the suffix array algorithm avoids iterating over singleton groups by keeping track of group intervals and creating new ones.


<p align="right">(<a href="#top">back to top</a>)</p>

### Output

* [Burrows Wheeler Transform](https://github.com/wustl-cse584/homework-2-problem-4-ThomasGibbonsIV/blob/main/output/BurrowsWheelerTransformOutput.txt)
* [Supermaximal Matches](https://github.com/wustl-cse584/homework-2-problem-4-ThomasGibbonsIV/blob/main/output/SuperMaximalMatches.txt)

<p align="right">(<a href="#top">back to top</a>)</p>

### Built With

* [CMake](https://cmake.org/)
* [C++](https://www.cplusplus.com/)
* [GoogleTest](https://github.com/google/googletest)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

This project requires at least C++11 because of calls to std::stack::emplace

### Installation

A few example installations are provided for compilers [clang](https://github.com/wustl-cse584/homework-2-problem-4-ThomasGibbonsIV/blob/main/build-clang.sh), [gcc](https://github.com/wustl-cse584/homework-2-problem-4-ThomasGibbonsIV/blob/main/build-gcc.sh), [minGW](https://github.com/wustl-cse584/homework-2-problem-4-ThomasGibbonsIV/blob/main/build-minGW.sh), and [msvc](https://github.com/wustl-cse584/homework-2-problem-4-ThomasGibbonsIV/blob/main/build-msvc.sh).

Running any of these scripts will create a build and install directory with a subdirectory with the chosen compiler. The install should look like the following (example done with Windows)

* include
  * AdjacentLcp.h
  * BurrowsWheelerTransform.h
  * SuffixArray.h
  * SuperMaximal.h
* lib
  * SuperMaximalLib.lib
* test
  * SuperMaximalTest.exe
  
### Usage

To run simply place the sequence file `human-seq.txt` in the same directory as the executable and then kick off the executable. If these files aren't included, then it will just run against smaller test case inputs.

./SuperMaximalTest.exe



<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Used [README-Template](https://github.com/othneildrew/Best-README-Template) to create this readme.