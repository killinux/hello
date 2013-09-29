#!/bin/sh
aa=`date "+%Y-%m-%d %H-1"`
echo $aa;
bb=`grep "$aa.*getCdkey   getCdkey" haotest`
echo $bb



