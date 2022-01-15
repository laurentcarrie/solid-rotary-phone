import subprocess
import time
from enum import Enum, auto
from pathlib import Path

wave_dir = Path("/home/laurent/yoga")

class PositionEnum(Enum):
    debout_flexion_avant = auto()
    cobra = auto()

    demarrage=auto()
    fin=auto()

    sleep_10=auto()
    sleep_20=auto()
    sleep_30=auto()



def speak(msg:str):
    command=["espeak","-v","fr-fr",msg]
    subprocess.run(command)

def play_wav(position:PositionEnum):
    f = wave_dir / (position.name+".wav")
    if not f.exists():
        raise RuntimeError(f"missing path : {str(f)}")
    command=["play",str(f)]
    subprocess.run(command)


def sleep(n:int):

    def speak_time(n):
        try:
            r = remaining // 1
            p = PositionEnum[f"sleep_{r}"]
            play_wav(p)
        except KeyError as e:
            speak(f"exception caught for remaining  equals {remaining}")


    remaining = n
    speak_time(n)

    first=True
    while remaining>0:
        if not first:
            speak_time(remaining)
        remaining -= 10
        time.sleep(10)
        first=False

def speak_position(position:PositionEnum, duree):
    #speak(msg)
    play_wav(position)
    time.sleep(10)
    play_wav(PositionEnum.demarrage)
    play_wav(position)
    sleep(duree)

def check_waves():
    for position in PositionEnum:
        f = wave_dir / (position.name + ".wav")
        if not f.exists():
            raise RuntimeError(f"missing path : {str(f)}")

def main():
    check_waves()
    #speak( "démarrage")
    #sleep(10)
    speak_position(PositionEnum.debout_flexion_avant, 30)
    speak_position(PositionEnum.cobra, 30)
    speak_position(PositionEnum.fin, 30)


if __name__ == "__main__":
    main()




