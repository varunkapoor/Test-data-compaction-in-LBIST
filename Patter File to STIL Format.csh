#!/bin/csh -f
sed -e ' s/X/N /g ' -e ' s/1/1 /g ' -e ' s/0/0 /g ' $1 > a1
rm $1
awk ' {\
printf("\"SCAN_IN\"=");\
for(i=1;i<=425;)\
{\
printf("%s",$i);\
i++;\
}\
printf(";\n");\
}' a1 > x
#sed -e ' s/$/\;/g ' -e ' s/^\;$//g ' x1 > a2
rm a1
awk ' {\
if($0 ~ "SCAN_IN\"")\
{\
printf("\"pattern %d\"\: Call \"load_unload\" { \n", (NR-1)/1);\
printf("%s\n", $0);\
}\
else printf("%s\n", $0);\
}' x > a3
rm x
awk '{\
if($0 ~ "SCAN_IN")\
{\
printf("\n %s", $0);\
printf(" \n } \n Call \"multiclock_capture\" { \n
\"_pi\"=NNNNNNNNNNPN1NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN0; \n
\"_po\"==XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX;} \n ");\
}\
else printf("%s\n", $0);\
} ' a3 > a4
rm a3
awk ' { print $0 } END { printf(" \"end 10 unload\": Call \"load_unload\" { } \n } ") }' a4 > a44
cat base_file_linflex a44 > $1.stil
rm a4 a44