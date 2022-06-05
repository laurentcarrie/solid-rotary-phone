\version "2.20.0"

song_tempo = 92



bar_em= {
< e,\6 b,\5 e\4 g\3 b\2 fis'\1>8
r16
< e,\6 b,\5 e\4 g\3 b\2 g'\1>16~
< e,\6 b,\5 e\4 g\3 b\2 g'\1>8
r8

r2
}

bar_c= {
< c\5 g\3 c'\2 fis'\1>8
r16
< c\5 g\3 c'\2 g'\1>16~
< c\5 g\3 c'\2 g'\1>8
r8
r2
}

bar_d= {
< d\4 a\3 d'\2 fis'\1>8
r16
< d\4 a\3 d'\2 g'\1>16~
< d\4 a\3 d'\2 g'\1>8
r8
r2
}


lead = {
\time 4/4

  \absolute  {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0
    \bar_em | \bar_c | \bar_d | \bar_em
}
}

rhythmbar = {
}

rhythm = {
\time 4/4
  \absolute  {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0
}
}


drumbar =  \drummode {  bd8 bd8 sn8 r8 bd8 r8 sn8 r8  }

drumbars = {
\time 4/4
\repeat unfold 4     \drumbar |
}


drumbarhh =  \drummode {
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8


}

drumbarshh = {

\repeat unfold 4 { \drumbarhh }

}



song_chords = \chordmode {
\time 4/4
e1:m |
c1 |
d1 |
e1:m

}

