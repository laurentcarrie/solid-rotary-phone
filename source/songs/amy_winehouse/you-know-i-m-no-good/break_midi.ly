\version "2.22.0"


\include "base_break.ly"


\score {

  <<

    \new DrumStaff
      \tempo 4 = \song_tempo
      <<
           \new DrumVoice {  \drumbarshh }
           \new DrumVoice {  \drumbars }
      >>	



    \new Staff {
      \rhythm
    }

    \new TabStaff {
        %instrumentName = "Jazz guitar"	
       %InstrumentName = "Electric guitar"
      % \set 	Staff.midiInstrument = "electric guitar (clean)"
       \set 	Staff.midiInstrument = "Electric"
      %\tabFullNotation
      \lead
    }


  >>
  
  \layout{}

  \midi {
  \tempo 4 = \song_tempo
  }

}
