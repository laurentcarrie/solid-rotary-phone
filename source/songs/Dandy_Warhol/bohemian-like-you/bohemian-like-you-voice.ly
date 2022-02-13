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

mychords = \chordmode {
  b1 d1 a1 e1
}


\score {

  <<



    \new Voice = "one" {
      \tempo 4 = 131
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      %\set TabStaff.stringTunings = #custom-tuning
      \mainvoice
    }

    \new Lyrics \lyricsto "one" {
      \verseOne
    }

    \new Voice = "second" {
      \tempo 4 = 131
      % \set TabStaff.stringTunings = #custom-tuning
      \othervoicea
      |
      \othervoiceb
    }

  >>
  \layout {}

  \midi {}
}
