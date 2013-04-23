hello
ç¬”è®°ï¼š
Â·
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
1. git push µÄÊ±ºò±¨´í£º
error: The requested URL returned error: 403 while accessing https://jccode@github.com/chyblog/firstPhpSite.git/info/refs

½â¾ö°ì·¨£º
³öÏÖÉÏÃæµÄÔ­Òò£¬´ó¶¼ÊÇÒòÎªÄãÃ»ÓĞµÇÂ½githubÕÊºÅ£¬ËùÒÔÃ»È¨ÏŞÉÏ´«£¬ËùÒÔ¾Í±¨´íÁË¡£
¾ßÌå½â¾ö°ì·¨£º
²é¿´ÄãµÄÏîÄ¿Ä¿Â¼ÏÂµÄ .git Ä¿Â¼ÏÂµÄ configÎÄ¼ş£¬¼´ .git/config ÎÄ¼ş¡£
¿ÉÒÔ¿´µ½£º
[remote "origin"]
        fetch = +refs/heads/*:refs/remotes/origin/*
        url = https://github.com/chyblog/firstPhpSite.git

°ÑÉÏÃæµÄurl ĞŞ¸ÄÎª url = https://killinux@github.com/chyblog/firstPhpSite.git
È»ºóÔÙÖØĞÂ³¢ÊÔÒ»ÏÂ¡£
´ËÊ±Ó¦¸Ã¿ÉÒÔÁË¡£»áµ¯³öÀ´ÒªÇóÄãÊäÈëÃÜÂë¡£ ÕıÈ·ÊäÈëºó£¬Ó¦¸Ã¾ÍÄÜpushÁË¡£
=====
