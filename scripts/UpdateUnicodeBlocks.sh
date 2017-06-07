#! /bin/bash
#
# Generate header and implementation for Unicode Blocks.

curl http://www.unicode.org/Public/UNIDATA/Blocks.txt > Blocks.txt

cat Blocks.txt | \
	grep -vE "^#|^$" | \
	sed 's/\.\./,/g' | \
	sed 's/; /,/g' | \
	tr '[:lower:]' '[:upper:]' | \
	sed 's/[ -]/_/g' \
	> Blocks.csv

# create header data.
awk -F "\"*,\"*" '{print "\n/// \\brief The " $3 " Unicode Block.\nstatic const Block " $3 ";"}' Blocks.csv > header.txt


# create implementation data.
awk -F "\"*,\"*" '{print "const Unicode::Block " $3 " {" "0x" $1 ", 0x" $2 ", \"" $3 "\"};"}' Blocks.csv > impl.txt

# clean up
rm Blocks.txt
rm Blocks.csv
