echo 'time-format %H:%M:%S
date-format %d/%b/%Y
log-format %h - - [%d:%t %^] "%r" %s %b "%R" "%u"' > goaccess.conf

cd ../04/
make 
cd -
cp ../04/nginx_log_*.log .
rm -rf ../04/nginx_log_*.log
sudo goaccess nginx_log_*.log -o report.html --log-format=COMBINED

sudo python3 -m http.server 8080

