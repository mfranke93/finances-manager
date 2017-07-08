#!/bin/zsh

if [[ $# -lt 2 ]]
then
    echo "Usage: $0 backupfile dblocation"
    exit 1
fi

# first argument is backup file
backup=$1

# second argument is database location
db=$2

# decrypt file
tarfile=/tmp/finances.tar.gz
gpg --decrypt $backup > $tarfile

# backup db
mv $db $db.old

# unpack archive
tar xfO $tarfile | sqlite3 $db

# remove tar file
rm $tarfile

# wait for user input
echo -n "Press [Enter] to close this restore session ..."
f=`read`
