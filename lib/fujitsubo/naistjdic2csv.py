#! /usr/bin/env python
# -*- coding: utf-8 -*-
import csv
import re
import codecs

def make_function_hiragana():
  re_katakana = re.compile(ur'[ァ-ヴ]')
  def hiragana(text):
    """ひらがな変換"""
    return re_katakana.sub(lambda x: unichr(ord(x.group(0)) - 0x60), text)
  return hiragana
hiragana = make_function_hiragana()

csvfile = 'naist-jdic.csv'
f = open(csvfile, "r")
reader = csv.reader(f)

for row in reader:
  if row[11] != "" :
    text = row[11].decode('utf-8')
    hira = hiragana(text)
    print "0," + row[0] + "," + hira.encode('utf-8') + "," + row[0] + "," + hira.encode('utf-8') + ",,0,0"

f.close()
