#!/bin/csh -f
awk ' { if ( $0 ~ "SCAN_IN" && $0 !~ "+" && $0 !~ "Scan" && $0 !~ "In") print $0 }' $1 > 1
sed -e ' s/N/X/g ' -e ' s/}/:/g ' -e ' s/"SCAX_IX.*"=//g ' 1 > 2
rm 1
awk 'BEGIN{FS=":"}\
{ \
if ($0 ~ ":") \
{ \
print $1, $2 ; \
} \
else printf("%s",$0); \
} END{ }' 2 > 3
rm 2
sed -e ' s/;//g ' -e ' s/^$\n//g ' -e ' s/ //g ' 3 > 4
rm 3
sed -e ' s/X//g ' -e ' s/1/1 /g ' -e ' s/0/0 /g ' 4 > check_cb
awk ' { print NF } ' check_cb >> care_bit_file
rm check_cb
paste -d " " 4 care_bit_file > canvas_file
rm 4 care_bit_file
sort -nr -k2 canvas_file > 7
rm canvas_file
awk ' { print $1 } ' 7 > ip_file
rm 7