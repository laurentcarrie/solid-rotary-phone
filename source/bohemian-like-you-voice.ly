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

verseOne = \lyricmode {
  you've got a great car, what's wrong with it to -- day,
  I used to have one too,
  ba -- by oh come and have a look I real -- ly love,
  your hair -- do yeah, I'm glad you like mine too, see
  we're look -- ing pret -- ty cool look at you,
  cause I like you, yeah I like you, and I'm fee -- ling
  so bo -- he -- mi -- an like you, yeah I like you,
  yea I like you, and I feel whoa woo
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
      \othervoice
    }

  >>
  \layout {}

  \midi {}
}
