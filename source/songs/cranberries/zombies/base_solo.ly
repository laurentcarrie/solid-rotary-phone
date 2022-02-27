\version "2.20.0"

song_tempo = 84

% Em
ma = {
  < e, b, e g>1
}

% C
mb = {
  < g, c e g c' e'   >1
}

% G
mc = {
  < g, d b d' >1
}

md = {
  <fis, d a d'>1
}


rhythm = {
  \ma \mb \ma \mb
  \ma \mb \ma \mb


  \ma \mb \mc \md
  \ma \mb \mc \md
  \ma \mb \mc \md
}

lead = {


  r1 | r1 | r1 | r1 |
  b'8 c'' r a' b' b' b' b' |
  b'8 c'' r a' b' b' b' b' |
  b'8 c'' r a' b' b' b' b' |
  b'8 c'' r a' b' <fis' b'>16 <fis' b'><fis' b'><fis' b'><fis' b'> r |
  b'8 c'' r a' b' <fis' b'>16 <fis' b'><fis' b'><fis' b'><fis' b'> r |

}


drumbar =  \drummode {
  bassdrum4
  snare
  bassdrum
  snare
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



staff_rhythm =   {
  \clef "treble_8"
  \tempo 4 = \song_tempo
  \override Score.BarNumber.break-visibility = ##(#t #t #t)
  %\set TabStaff.stringTunings = #custom-tuning
  \rhythm
}

staff_lead =    {
  \clef "treble_8"
  \tempo 4 = \song_tempo
  \override Score.BarNumber.break-visibility = ##(#t #t #t)
  \omit StringNumber
  \lead

}

staff_lead_tab = {
  \tempo 4 = \song_tempo
  \tabFullNotation
  \override Score.BarNumber.break-visibility = ##(#t #t #t)
  \lead
}


