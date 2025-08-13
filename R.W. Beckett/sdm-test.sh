#!/bin/bash

rsync -ah --progress Downloads/2025-05-13-raspios-bookworm-arm64.img ./final_revision.img

sudo sdm \
    --extend \
    --xmb 2048 \
    --poptions noupdate,noupgrade \
    --plugin disables:"piwiz" \
    --plugin user:"setpassword=pi|password=rwb_pi" \
    --plugin copyfile:"from=./Downloads/dehumidifier.png|to=/usr/local/etc|mkdirif=yes" \
    --plugin apps:"remove=vlc-bin" \
    --plugin runatboot:"script=./Downloads/testpi4.py|output=/home/pi/testpi4output.txt" \
    --plugin vnc:"wayvnc=1600x1200" \
    --plugin L10n:"keymap=us|locale=en_US.UTF-8|timezone=America/New_York" \
    --showapt \
    --autologin \
    --customize \
    --batch \
    --restart \
    final_revision.img

#    --plugin network:"autoconnect=true|ifname=wlan0|wifissid=Guest|wifipassword=Beckett1|wificountry=US"
#    --apt-dist-upgrade