#!/bin/zsh

if [[ $# -lt 1 ]]
then
    echo "Usage: $0 dblocation [ssh-location]"
    exit 1
fi

# first argument is database location
db=$1

# second argument is ssh location
if [[ $# -ge 2 ]]
then
    addr=$2
else
    # default: use raspi
    addr=pi
fi

# write backup to temp file
name=`date +"/tmp/finances_backup_%Y%m%d%H%M.sql"`
echo "Dumping database $db to $name ..."
sqlite3 $db ".dump" | sed 's/foreign_keys=OFF/foreign_keys=ON/g' > $name

name2=`date +"/tmp/finances_backups_%Y%m%d%H%M.tar.gz"`
echo "Creating archive $name2 ..."
tar czf $name2 $name

echo "Encrypting archive $name2 to self ..."
gpg -e -r max $name2

echo "Creating folder in remote location. You may be prompted for a password ..."
ssh $addr "mkdir -p ~/data"
echo "Copying encrypted archive to remote location ..."
scp $name2.gpg "$addr:~/data/"

# cleanup
echo "Cleaning up temporary files ..."
rm -v $name $name2 $name2.gpg

# wait for user input
echo -n "Press [Enter] to close this backup session ..."
f=`read`
