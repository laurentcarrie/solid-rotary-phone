\version "2.22.1"

song_tempo = 114





lead = {
  \absolute  {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0


    d2\5 dis2\5 | e2\5 dis2\5
}
}

drumbar =  \drummode {  bd4 sn4  bd4 sn4 }

drumbars = {
\repeat unfold 2 \drumbar |
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
  \repeat unfold 2 {  \drumbarhh }

}
