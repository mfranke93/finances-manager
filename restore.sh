#!/bin/zsh

if [[ $# -lt 2 ]]
then
    echo "Usage: $0 backupfile output-directory"
    exit 1
fi

# first argument is backup file
backup=$1

# second argument is database location
dir=$2

# decrypt file, unpack archive
gpg --decrypt $backup | tar --extract --to-stdout --gzip > ${dir}/restore.sql

# wait for user input
echo -n "Press [Enter] to close this restore session ..."
f=`read`
