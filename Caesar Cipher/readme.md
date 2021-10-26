# caesar.c  
  
Simple implementation of the caesar cipher  
that can encode and decode txt files.  

Alphabet consists of the characters matching the regex  
[a-zA-Z ,.:;\_!?'"\-] as well as the '\\n' character.  
This is equivalent to the ASCII values ranging from  
[32, 126] (both inclusive) plus the value 10  
Any characters found in the ciphertext that are not in  
this range will be mapped to the underscore ('_') character
  
Usage:  
./caesar [input filename] [output filename] [key (int)] [Operation en|de]

Appended are an example plain- and ciphertext encoded  
with a key value of 69