\version "2.20.0"

song_tempo = 80



bar_ema= {
\repeat     unfold 6 { < g\4 d'\3 g'\2 bes'\1>8 }
\repeat     unfold 6 { < f\5 d'\3 g'\2 bes'\1>8 }

}

bar_emb= {
\repeat     unfold 6 { < ees\5 g\4 f'\2 bes'\1>8 }
\repeat     unfold 2 { < d\5 fis\4 c'\3 f'\2>8 }
d8\5 f8\4 d8\5 f8\4
}

bar_six= {
\repeat unfold 6 {  <e\4 g\3 d'\2 g'\1>8 }
\repeat unfold 6 {  <ees\4 g\3 d'\2 g'\1>8 }
}

bar_sept={
\repeat unfold 6 {  <d\5 g\4 bes\3 d'\2>8 }
\repeat unfold 6 {  <c\5 g\4 c'\3 e'\2 >8 }
}

bar_huit={
\repeat unfold 6 {  <bes,\5 f\4 bes\3 d'\2>8 }
\repeat unfold 6 {  <a,\5 e\4 g\3 c'\2 >8 }
}

bar_neuf={
\repeat unfold 5 {  <c\5 g\4 c'\3 e'\2>8 }
<des\5 aes\4 des'\3 f'\2>8
<d\5 a\4 d'\3 fis'\2>8
r8 r8 r8 r8 r8
}

lead = {
\time 6/4

  \absolute  {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0

    \repeat percent 2 {\bar_ema     \bar_emb }
    \bar_ema |
    \bar_six |
    \bar_sept |
    \bar_huit |
    \bar_neuf |
}
}

rhythmbar = {
}

rhythm = {
\time 6/8
  \absolute  {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0
}
}

song_chords = {
    \time 6/8
    \chordmode {
        g2.:m    f2.:m  c   g:sus4  f  e
    }
}

drumbar =  \drummode {  bd8 r8 r8 sn8 r8 r8 }

drumbars = {
\time 6/8
\repeat unfold 24 \drumbar |
}


drumbarhh =  \drummode {
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8


}

drumbarshh = {

\repeat unfold 24 { \drumbarhh }

}
