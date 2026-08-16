#!/usr/bin/env python3
import sys
import re
import datetime


def main():
    if len(sys.argv)==1 and len(sys.argv)<3:
        print("Greska! Treba da pratite 3 argumenti! Kako se koristi: *.py primer.txt YYYY-MM-DD")
        sys.exit(1)
    else:
        print("Imate vneseno ",len(sys.argv), " argumenti od komandna linija") #Ova mi e za da znam kolku argumenti prakjam cisto mi bese za da proveram dali vleguva i izleguva od if
        if len(sys.argv)==3:
            path=sys.argv[1] #Prv argument vnesen dat.txt
            datum=sys.argv[2] #Datumot 2026-11-10 primer
            print("Ova e prviot argument praten: ",path) #Pecatenje na istite 
            print("Ova e vtoriot argument praten: ",datum) #Ova e optional i za da mi bide jasno go imam staveno


        if len(sys.argv)==2:
            path=sys.argv[1] #Prv argument vnesen dat.txt
            with open(path, "r") as f: #Pecatenje na ls -al dokumentot dokolku ne e naveden vtor argument
                #words=f.read() #Words go citaat file-ot ama go cita kako eden giganten string i neama da vleze vo dolniot if bidejkji ne pocnuva toj string so -
                for words in f:
                    words=words.strip() #Potoa mu pravam strip i posle toa
                    if(words.startswith('-')): #Proveruvam dali pocnuva so -
                        print(words) #Pecati go zborot ako pocnuva so minus ova go proveruvam samo za da vidam dali mi vleguva vo if
                         

main()