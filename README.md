# keyfilter
Hi, the programme you've just opened is emulation of the virtual keyboard in navigation-like system when searching for the address in search bar. This algorithm let's you easily display only those characters, which are present in the database (no matter the size) after providing wanted address

$ gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter

./keyfilter (lettersToLookFor) <database.txt
