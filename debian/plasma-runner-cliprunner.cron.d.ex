#
# Regular cron jobs for the plasma-runner-cliprunner package
#
0 4	* * *	root	[ -x /usr/bin/plasma-runner-cliprunner_maintenance ] && /usr/bin/plasma-runner-cliprunner_maintenance
