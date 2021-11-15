
song_tempo = 83

ma = {
  < a, e>8      < a, e>8
  < a, fis>8   < a, fis>8
  < a, e>8      < a, e>8
  < a, fis>8   < a, fis>8

}

mb = {
  <d' a'>1
}



rhythm = {
  \ma \ma \ma \ma
  \mb
}

lead = {
  \relative c'' {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0

    % mes 1
    \grace g'8^\markup { \char ##x2197 " 1 "  }
    a2~
    a8
    \grace g16^\markup {\char ##x2197 "1"}
    a8
    \grace g16^\markup {\char ##x2197 "1"}
    a16
    \grace a16^\markup {\char ##x2198 "1"}
    g16
    f8

    |
    % mes 2
    \grace g16^\markup {\char ##x2197 "1"}
    a1

    |
    % mes 3
    \grace g16^\markup {\char ##x2197 "1"}
    a2~
    a8
    \grace g16^\markup {\char ##x2197 "1"}
    a8
    \grace g16^\markup {\char ##x2197 "1"}
    a16
    \grace a16^\markup {\char ##x2198 "1"}
    g16
    f8

    |
    % mes 4
    \grace d16\2^\markup {\char ##x2197 "1"}
    e2~\2
    e8\2
    \grace d16\2^\markup {\char ##x2197 "1"}
    e8\2
    \grace d16\2^\markup {\char ##x2197 "1"}
    e16\2
    \grace e16\2^\markup {\char ##x2198 "1"}
    d16\2
    c8\2
    |
    \grace g'16\1^\markup {\char ##x2197 "1"}
    a1\1

  }
}

drumbar =  \drummode {  bassdrum4 hihat4  bassdrum hihat }

drums = {
  \drumbar |
  \drumbar |
  \drumbar |
  \drumbar |
  \drumbar |
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



