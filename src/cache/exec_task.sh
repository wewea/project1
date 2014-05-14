#########################################################################
# File Name: make_dict.sh
# Author: Zhlin
# Mail: vimquee@gmail.com
# Created Time: 2014年05月04日 星期日 17时07分28秒
#########################################################################
#!/bin/bash
CONFPATH=../../conf/dict.conf
DATE=$(date +%Y-%m-%d)
LOGTYPE=.log
LOG=`echo $DATE$LOGTYPE`
LOGPATH=../../log/$LOG
echo $LOGPATH
DICT=dict
QUERY=query
SERVER=server
./$SERVER $CONFPATH $LOGPATH
