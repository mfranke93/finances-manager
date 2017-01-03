#!/bin/zsh

name=`date +"sql_backups/backup_%Y%m%d%H%M.sql"`

sqlite3 data.db ".dump" | sed 's/foreign_keys=OFF/foreign_keys=ON/g' > $name

name=`date +"/tmp/finances_backups_%Y%m%d%H%M.tgz"`
tar cf $name sql_backups
gpg -e -r max $name

if [[ "$1" != "" ]]
then
    ssh $1 "mkdir -p ~/data"
    scp $name.gpg "$1:~/data/"
fi
