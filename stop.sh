pid=`ps -ef | grep imagehandle | grep -v grep | awk '{print $2}'`
kill -9 $pid