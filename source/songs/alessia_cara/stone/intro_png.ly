\version "2.20.0"

\include "../../../../macros/macros.ly"
\include "intro.ly"

\paper {
    #(include-special-characters)
    indent = 0\mm
    line-width = 180\mm
    oddHeaderMarkup = ""
    evenHeaderMarkup = ""
    oddFooterMarkup = ""
    evenFooterMarkup = ""
}


\score {
    <<
      \set Score.currentBarNumber = #0
        \new ChordNames {
            \song_chords
            }

    \new TabStaff {
        \tempo 4 = \song_tempo
        \tabFullNotation
        \override Score.BarNumber.break-visibility = ##(#t #t #t)
        \lead
    }

    >>

    \layout {}
}

