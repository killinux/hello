hello
笔记：
·
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
1. git push ��ʱ�򱨴�
error: The requested URL returned error: 403 while accessing https://jccode@github.com/chyblog/firstPhpSite.git/info/refs

����취��
���������ԭ�򣬴�����Ϊ��û�е�½github�ʺţ�����ûȨ���ϴ������Ծͱ����ˡ�
�������취��
�鿴�����ĿĿ¼�µ� .git Ŀ¼�µ� config�ļ����� .git/config �ļ���
���Կ�����
[remote "origin"]
        fetch = +refs/heads/*:refs/remotes/origin/*
        url = https://github.com/chyblog/firstPhpSite.git

�������url �޸�Ϊ url = https://killinux@github.com/chyblog/firstPhpSite.git
Ȼ�������³���һ�¡�
��ʱӦ�ÿ����ˡ��ᵯ����Ҫ�����������롣 ��ȷ�����Ӧ�þ���push�ˡ�
=====
