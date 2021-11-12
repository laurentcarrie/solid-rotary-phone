
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
    \grace g'8^\markup { \char ##x2197 " 1 "  }
    a2~
    a8
    \grace g16^\markup {\char ##x2197 "1"}

    a8
    \grace g16^"pull 1."
    a16
    \grace a16^"release 1."
    g16
    f8
    |
    \grace g16^\markup {\char ##x2197 "1"}
    a1
    |
    a2~
    a8
    a8
    a16
    g16
    f8
    |
    e2~\2
    e8\2
    c8\2
    e16\2
    d16\2
    c8\2
    |
    a'1\1

  }
}

drumbar =  \drummode {  bassdrum4 hihat4  bassdrum hihat }

staff_drums =    \new DrumStaff {
      \tempo 4 = 83

      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |



    }


staff_rhythm =    \new Staff {
      \clef "treble_8"
      \tempo 4 = 83
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      %\set TabStaff.stringTunings = #custom-tuning
      \rhythm
    }

staff_lead    \new Staff	 {
      \clef "treble_8"
      \tempo 4 = 83
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      \omit StringNumber
      \lead

    }

staff_lead_tab = \new TabStaff {
      \tempo 4 = 83
      \tabFullNotation
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      \lead
    }



