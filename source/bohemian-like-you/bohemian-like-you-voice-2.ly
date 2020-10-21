\version "2.20.0"

\paper {
  indent = 0\mm
  line-width = 210\mm
  oddHeaderMarkup = ""
  evenHeaderMarkup = ""
  oddFooterMarkup = ""
  evenFooterMarkup = ""
}


\include "bohemian-like-you-data.ly"


\score {

  <<



    \new Voice = "two" {
      \tempo 4 = 131
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      %\set TabStaff.stringTunings = #custom-tuning
      \othervoiceb
    }

  >>
  \layout {}

  \midi {}
}
