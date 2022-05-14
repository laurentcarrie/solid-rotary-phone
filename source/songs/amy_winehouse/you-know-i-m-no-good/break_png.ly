\version "2.20.0"

\include "../../../macros/macros.ly"
\include "break.ly"

\paper {
    #(include-special-characters)
    indent = 0\mm
    line-width = 100\mm
    oddHeaderMarkup = ""
    evenHeaderMarkup = ""
    oddFooterMarkup = ""
    evenFooterMarkup = ""

    #(add-text-replacements!
    '(
    ("100" . "hundred")
    ("dpi" . "dots per inch")
    ))

}


\score {
    <<
    \new TabStaff {
        \tempo 4 = \song_tempo
        \tabFullNotation
        \override Score.BarNumber.break-visibility = ##(#t #t #t)
        \lead
    }

    >>

    \layout {}
}

