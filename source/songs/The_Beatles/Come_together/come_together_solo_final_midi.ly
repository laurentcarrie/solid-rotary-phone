\version "2.22.0"


\include "base_solo_final.ly"


\score {

  <<

    \new DrumStaff
      % \tempo 4 = \song_tempo
      <<
           \new DrumVoice {  \drumbarshh }
           \new DrumVoice {  \drumbars }
      >>	



    %\new Staff {
    %  \rhythm
    %}

    \new TabStaff {
        %instrumentName = "Jazz guitar"	
       %InstrumentName = "Electric guitar"
       \set 	Staff.∏midiInstrument = "electric guitar (clean)"
      %\tabFullNotation
      \lead
    }


  >>
  
  \layout{}

  \midi {}

}
