rpm -Uvh http://repo.webtatic.com/yum/centos/5/latest.rpm
yum install --enablerepo=webtatic git-all
hello
git:
mkdir hello
cd hello
git clone https://github.com/killinux/hello.git
cd hello/
vim hello.c
git add .
git commit -m "hello first"
git log
git pull
ls
vim README.md 
git commit -a -m "readme"
git push
-----------------
1. git push error:
error: The requested URL returned error: 403 while accessing https://jccode@github.com/chyblog/firstPhpSite.git/info/refs
[remote "origin"]
        fetch = +refs/heads/*:refs/remotes/origin/*
        url = https://github.com/chyblog/firstPhpSite.git

 url = https://killinux@github.com/chyblog/firstPhpSite.git
=====
url = https://killinux@github.com/chyblog/firstPhpSite.git
vimrc:
syntax on
set fileencoding=gb18030
set fileencodings=utf-8,gb18030,utf-16,big5
PATH=$PATH:/usr/libexec/git-core
=====
