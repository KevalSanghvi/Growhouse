#Copyright (c) 2016, The Linux Foundation. All rights reserved.
#
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions are
#met:
#    * Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above
#      copyright notice, this list of conditions and the following
#      disclaimer in the documentation and/or other materials provided
#      with the distribution.
#    * Neither the name of The Linux Foundation nor the names of its
#      contributors may be used to endorse or promote products derived
#      from this software without specific prior written permission.
#
#THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
#WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
#MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
#ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
#BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
#CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
#SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
#BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
#OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
#IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#!/bin/sh
# play WAV audio on analog speakers by using ALSA aplay utility checks for errors or warnings 

# needs to be connected to the DUT: 
# Analog speaker (#TODO add a connected analog speaker illustration )


date
echo "=============> Running Test: Analog-WAV-Audio-ALSA-Playback-test <==============="
echo

# defines general variables used in most tests
source $(dirname $(readlink -f $0))/../../util/generally-used-variables.txt

ALSA_LOG_FILE="alsa.log"
FILE_TO_PLAY="$CONTENT_PATH/$($GET_ENV_VARS SOUND_FILE_WAV)"
echo file to play - $FILE_TO_PLAY

#define audio Hardware configuration:
ANALOG_SPEAKER_HW_CONFIG=plughw:0,1

echo "==== check if the file to play appears in the file system ===="
if [ -e "$FILE_TO_PLAY" ]
then 
  echo File $FILE_TO_PLAY found on the file system, Ok!
else
  echo ERROR: File $FILE_TO_PLAY NOT found on file system
  echo  
  date
  exit 1
fi

# do some cleanup (kill and clean any remainders from previous runs)
echo "some cleanup & setup ..."
echo  
eval kill -9 $(pidof "aplay") &>/dev/null
rm $ALSA_LOG_FILE &>/dev/null
sleep 1
echo
echo "done cleanup & setup, running test..."

#configuring sound card
#routing the Tombak codec
#======================================
amixer -c 0 cset name='PRI_MI2S_RX Audio Mixer MultiMedia1' 1 &>/dev/null
amixer -c 0 cset name='RX1 MIX1 INP1' 'RX1' &>/dev/null
amixer -c 0 cset name='RX2 MIX1 INP1' 'RX2' &>/dev/null
amixer -c 0 cset name='RDAC2 MUX' 'RX2' &>/dev/null

#Turn on both sides of the headphones
#========================================
amixer -c 0 cset name='HPHL' 'Switch' &>/dev/null
amixer -c 0 cset name='HPHR' 'Switch' &>/dev/null
amixer -c 0 cset name='MI2S_RX Channels' 'Two' &>/dev/null

# Before analog playback
amixer cset iface=MIXER,name='RX1 MIX1 INP1' 'RX1' &>/dev/null
amixer cset iface=MIXER,name='RX2 MIX1 INP1' 'RX2' &>/dev/null
amixer cset iface=MIXER,name='RDAC2 MUX' 'RX2' &>/dev/null
amixer cset iface=MIXER,name='HPHL' 1 &>/dev/null
amixer cset iface=MIXER,name='HPHR' 1 &>/dev/null
amixer cset iface=MIXER,name='RX1 Digital Volume' 80 &>/dev/null
amixer cset iface=MIXER,name='RX2 Digital Volume' 80 &>/dev/null
sleep 1

# executing aplay
COMMAND="aplay -l -L && aplay -vv $FILE_TO_PLAY -D $ANALOG_SPEAKER_HW_CONFIG"
echo "Running Command: $COMMAND"
eval $COMMAND &> $ALSA_LOG_FILE

# test finished, post processing data
# look into the log file and search for any errors
ERROR_COUNT="$(cat $ALSA_LOG_FILE | grep -c "error")"
WARNING_COUNT="$(cat $ALSA_LOG_FILE | grep -c "arning")"
ERROR_COUNT=$(( $WARNING_COUNT + $ERROR_COUNT))

echo  
echo Number of Errors or Warnings: $ERROR_COUNT
echo  
if [ "$ERROR_COUNT" -gt "0" ]
then 
  RESULT=1
  echo "Errors found!.."
  cat $ALSA_LOG_FILE | grep "arning"
  cat $ALSA_LOG_FILE | grep "error"
  echo 
  echo " - - F A I L - - "
else
  RESULT=0
  echo " + + P A S S + + "
fi

# garbage cleaning 
eval kill -9 $(pidof "aplay") &>/dev/null
rm $ALSA_LOG_FILE &>/dev/null
sleep 1

echo
echo "=============> Finished Test: Analog-WAV-Audio-ALSA-Playback-test <==============="
echo

date
exit $RESULT


