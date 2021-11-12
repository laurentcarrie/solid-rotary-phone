\version "2.20.0"

\include "base_solo_1.ly"

\score {

  <<



    \new DrumStaff {
      \tempo 4 = 83

      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
    }


    \new Staff {
      \clef "treble_8"
      \tempo 4 = 83
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      %\set TabStaff.stringTunings = #custom-tuning
      \rhythm
    }

    \new Staff	 {
      \clef "treble_8"
      \tempo 4 = 83
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      \omit StringNumber
      \lead

    }

    \new TabStaff {
      \tempo 4 = 83
      \tabFullNotation
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      \lead
    }



  >>

  \midi {}
}
}
