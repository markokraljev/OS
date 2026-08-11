#!/usr/bin/env python3
import sys
import re
import datetime


def main():
    if len(sys.argv)<=1 | len(sys.argv)>3:
        print("Greska! Treba da pratite 3 argumenti! Kako se koristi: *.py primer.txt YYYY-MM-DD")
        sys.exit(1)
    else:
        path=sys.argv[1] #Prv argument vnesen dat.txt
        if len(sys.argv)==3:
            datum=sys.argv[2] #Datumot 2026-11-10 primer
            print("Ova e prviot argument praten: ",path) #Pecatenje na istite 
            print("Ova e vtoriot argument praten: ",datum) #Ova e optional i za da mi bide jasno go imam staveno

        if len(sys.argv)==2:
            with open(path, "r") as f: #Pecatenje na ls -al dokumentot dokolku ne e naveden vtor argument
                print(f.read()) 
main()