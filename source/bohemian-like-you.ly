\paper {
  indent = 0\mm
  line-width = 110\mm
  oddHeaderMarkup = ""
  evenHeaderMarkup = ""
  oddFooterMarkup = ""
  evenFooterMarkup = ""
}


\include "predefined-guitar-fretboards.ly"






\new ChordNames \with {
  \override BarLine.bar-extent = #'(-2 . 2)
  \consists "Bar_engraver"
          \override VerticalAxisGroup.nonstaff-relatedstaff-spacing = #'((basic-distance . 1))
}

\chordmode {
  f1:maj7 f:7 bes:7 \break
  f1  f:7 bes:7

}
\new ChordNames \with {
  \override BarLine.bar-extent = #'(-2 . 2)
  \consists "Bar_engraver"
}

\chordmode {
  c1 d2:min
}
