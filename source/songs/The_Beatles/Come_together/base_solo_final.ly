\version "2.22.1"
song_tempo = 83

ma = {

  d8 d8 c'8 b8~ b8 d8 c'8 a8~

}

mb = {

  a8 b16 r16 r4 r2

}



rhythm = {
  \ma | \mb | \ma |  \mb |
  \ma | \mb | \ma |  \mb |
  \ma | \mb | \ma |  \mb |
}

lead = {
  \relative c'' {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0

    % mes 1
    \grace c8\2^\markup { \char ##x2197 " 1 "  }
    d1\2
    |
    % mes 2
    r2
    r8
    g8\1
    g16\1
    f16\1
    d8\2
    |
    % mes 3
    d1\2
    |
    % mes 4
    r2
    r8
    f,8\3
    a16\3
    g16\3
    f8\3
    |
    % mes 5
    d'1\2
    |
    % mes 6
    r2
    r8
    g8\1
    g16\1
    f16\1
    d8\2
    |
    % mes 7
    d1\2
  }
}

drumbar =  \drummode {  bd4 sn4  bd4 sn4 }

drumbars = {
  \drumbar |
  \drumbar |
  \drumbar |
  \drumbar |
  \drumbar |
  \drumbar |
  \drumbar |
  \drumbar |
  \drumbar |
  \drumbar |
  \drumbar |
  \drumbar |
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
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |
  \drumbarhh |

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
