# ICURPP - Interactive Common User Reconstructed Password Profiler

## About

This C++ program is a remake of a tool called [CUPP](https://github.com/Mebus/cupp) by [Mebus](https://github.com/Mebus). It generates potential password combinations based on a victim's information provided by the user.
The name reflects the interactive nature of the program and acknowledges that it's a reconstructed version of the original cupp, tailored for C++ users.

## Planned improvements and optimizations
  * Reducing Redundancy: 
    I'm considering using a single function to handle capitalization variations (upper, lower, mixed case) instead of separate functions for flipping and capitalization.

  * Enhance Efficiency: 
    For very large profiles, generating all combinations might become slow. I might xplore techniques like pruning unlikely combinations or using more efficient data structures for storing potential passwords.

  * Thread-Safety: 
    I'm planning to scale the program to handle larger profiles in the future, and considering adding thread-safety mechanisms when modifying the combinations set concurrently.


## Original author

  Muris Kurgas aka j0rgan  
  j0rgan@remote-exploit.org  
  http://www.remote-exploit.org  
  http://www.azuzi.me  

## Contributors to the original [CUPP](https://github.com/Mebus/cupp)

  * Bosko Petrovic aka bolexxx  
  bole_loser@hotmail.com  
  http://www.offensive-security.com  
  http://www.bolexxx.net  

  * Mebus  
    https://github.com/Mebus/  

  * Abhro  
    https://github.com/Abhro/  

  * Andrea Giacomo  
    https://github.com/codepr

  * quantumcore  
    https://github.com/quantumcore

## Disclaimer

This tool is intended for educational puposes only and should not be used for malicious activities. Password cracking without victim's concent is a crime in most jurisdictions.
