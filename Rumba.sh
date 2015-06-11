#!/bin/bash
make
ip=$(ip addr show |grep -w inet |grep -v 127.0.0.1|awk '{ print $2}'| cut -d "/" -f 1)
broadcast=$(ip addr show |grep -w inet |grep -v 127.0.0.1|awk '{ print $4}')
./mainRUMBA $ip $broadcast

killall mainRUMBA
echo `rm *.o`
echo 'rm mainRUMBA'
