\version "2.20.0"

\paper {
  indent = 0\mm
  line-width = 210\mm
  oddHeaderMarkup = ""
  evenHeaderMarkup = ""
  oddFooterMarkup = ""
  evenFooterMarkup = ""
}

\include "base_solo.ly"


\score {
  <<
    \time 6/8
    %\new ChordNames { \theChords }

    \new TabStaff {
      \tempo 4 = \song_tempo
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      \tabFullNotation

      \lead
    }



  >>
  \layout {}

}
