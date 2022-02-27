\version "2.20.0"

\include "base_solo.ly"

\paper {
  indent = 0\mm
  line-width = 210\mm
  oddHeaderMarkup = ""
  evenHeaderMarkup = ""
  oddFooterMarkup = ""
  evenFooterMarkup = ""
}

\score {
  <<
    <<

      \new DrumStaff {
        \drumbar |
        \repeat percent 7 \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
        \drumbar |
      }

      \new DrumStaff {
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |
        \drumbarhh |

      }
    >>



    %\new ChordNames { \theChords }

    \new Staff {
      \clef "treble_8"
      % \transposition c
      \tempo 4 = 84
      %\set Staff.midiInstrument = "electric guitar (clean)"
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      %\set TabStaff.stringTunings = #custom-tuning
      \set Staff.midiMinimumVolume = #0.4
      \set Staff.midiMaximumVolume = #0.4

      \rhythm
    }

    %\new Staff	 {
    %  \clef "treble_8"
    %  %\transposition c
    %  %\set Staff.midiInstrument = "electric guitar (clean)"
    %  \tempo 4 = 84
    %  \override Score.BarNumber.break-visibility = ##(#t #t #t)
    %  \lead
    %}

    \new TabStaff {
      \tempo 4 = 84
      % \set Staff.midiInstrument = "electric guitar (clean)"
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      \tabFullNotation
      \set Staff.midiMinimumVolume = #0.7
      \set Staff.midiMaximumVolume = #0.9

      \lead
    }



  >>
  \layout {}

  \midi {}
}
