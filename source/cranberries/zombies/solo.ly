\version "2.20.0"

\paper {
  indent = 0\mm
  line-width = 210\mm
  oddHeaderMarkup = ""
  evenHeaderMarkup = ""
  oddFooterMarkup = ""
  evenFooterMarkup = ""
}

%theChords = \chordmode {
%  \time 2/2
%  Em1 | C | G | D| %\break
%}


% Em
ma = {
  < e, b, e g>1
}

% C
mb = {
  < g, c e g c' e'   >1
}

% G
mc = {
  < g, d b d' >1
}

md = {
  <fis, d a d'>1
}


rhythm = {
  \ma \mb \ma \mb
  \ma \mb \ma \mb


  \ma \mb \mc \md
  \ma \mb \mc \md
  \ma \mb \mc \md
}

lead = {


  r1 | r1 | r1 | r1 |
  b'8 c'' r a' b' b'16 b' b' b' b' r |
  b'8 c'' r a' b' b'16 b' b' b' b' r |
  b'8 c'' r a' b' b'16 b' b' b' b' r |
  b'8 c'' r a' b' <fis' b'>16 <fis' b'><fis' b'><fis' b'><fis' b'> r |

}


drumbar =  \drummode {
  bassdrum4
  snare
  bassdrum
  snare
}

drumbarhh =  \drummode {
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
}


\score {
  <<
    <<

      \new DrumStaff {
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
