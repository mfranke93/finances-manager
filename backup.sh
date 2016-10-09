#!/bin/zsh

name=`date +"sql_backups/backup_%Y%m%d%H%M.sql"`

sqlite3 data.db ".dump" | sed 's/foreign_keys=OFF/foreign_keys=ON/g' > $name