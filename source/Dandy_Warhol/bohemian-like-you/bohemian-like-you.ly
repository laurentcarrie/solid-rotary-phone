\version "2.20.0"

\paper {
  indent = 0\mm
  line-width = 110\mm
  oddHeaderMarkup = ""
  evenHeaderMarkup = ""
  oddFooterMarkup = ""
  evenFooterMarkup = ""
}


\include "predefined-guitar-fretboards.ly"
custom-tuning = \stringTuning <d g d' g' b' d''>

\addChordShape #'flatbar #guitar-tuning "0-1-(;0-1;0-1;0-1;0-1;0-1-);"

\storePredefinedDiagram #default-fret-table
\chordmode { e }
#guitar-tuning
#(offset-fret 2 (chord-shape 'flatbar guitar-tuning))

\storePredefinedDiagram #default-fret-table
\chordmode { b }
#guitar-tuning
#(offset-fret 4 (chord-shape 'flatbar guitar-tuning))

\storePredefinedDiagram #default-fret-table
\chordmode { d }
#guitar-tuning
#(offset-fret 7 (chord-shape 'flatbar guitar-tuning))

\storePredefinedDiagram #default-fret-table
\chordmode { a }
#guitar-tuning
#(offset-fret 2 (chord-shape 'flatbar guitar-tuning))

\storePredefinedDiagram #default-fret-table
\chordmode { e }
#guitar-tuning
#(offset-fret 9 (chord-shape 'flatbar guitar-tuning))

mynotes = {
  <fis b fis' b' dis'' fis''>4
  <fis b fis' b' dis'' fis''>4
  <fis b fis' b' dis'' fis''>4
  <fis b fis' b' dis'' fis''>4
  |
  <a e a' e' cis'' a''>4
  <a e a' e' cis'' a''>4
  <a e a' e' cis'' a''>4
  <a e a' e' cis'' a''>4
  |
  <d a d' a' fis'' d''>4
  <d a d' a' fis'' d''>4
  <d a d' a' fis'' d''>4
  <d a d' a' fis'' d''>4
  |
  <b e b' e' gis'' b''>4
  <b e b' e' gis'' b''>4
  <b e b' e' gis'' b''>4
  <b e b' e' gis'' b''>4

}
mychords = \chordmode {
  b1 d1 a1 e1
}

\score {

  <<
    % \new ChordNames {
    %  \chordmode {
    %    c1 d:m e
    %    }
    %



    \new ChordNames {
      \mychords
    }

    \new FretBoards {
      \mychords
    }

    %  \new Staff {
    %    \clef treble
    %    \mynotes
    %  }

    \new Staff {
      \tempo 4 = 200
      % \set TabStaff.stringTunings = #custom-tuning
      \mynotes
    }


  >>
  \layout {}

  \midi {}
}
