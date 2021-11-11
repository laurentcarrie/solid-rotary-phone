pour enregistrer : 
ctrl-c pour finir

ffmpeg -f pulse -i alsa_input.pci-0000_00_1f.3.analog-stereo -ac 2 recording.m4a


conf audacity:
sudo snap connect audacity:alsa
