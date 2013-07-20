#!/usr/bin/expect 
set timeout 30 
spawn mysql -ubooktest -p 
expect "password:" 
send "booktest\r" 
interact 
