/*inputChar() uses rand() to generate random character from ASCII 32 
to ASCII 126, the range of printable characters.Because this is a relatively 
small range, the testme program goes through the first 9 states very quickly, 
so fast you can't even really see it in the terminal.

The way I originally wrote it, inputString() malloc'ed a string of length 
5 (+1 for the C-string terminator) and then called inputChar to generate the 
strings. There is something like a 1 in 8 billion chance for the string "reset"
to be generated with this many character possibilities (96^5), so once I realized
that I rewrote inputString to randomly generate its own characters in the range of
a-z. This produced an error on iteration 12,854,123 the first time I ran it.*/

