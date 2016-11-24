#!/bin/zsh

name=`date +"sql_backups/backup_%Y%m%d%H%M.sql"`

sqlite3 data.db ".dump" | sed 's/foreign_keys=OFF/foreign_keys=ON/g' > $name

name=`date +"/tmp/finances_backups_%Y%m%d%H%M.tgz"`
tar cf $name sql_backups
gpg -e -r max $name
scp $name.gpg pi-internal:/home/max/backups
