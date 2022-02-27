\version "2.22.0"


\include "base_solo_final.ly"


\score {

  <<

    \new DrumStaff
      % \tempo 4 = \song_tempo
      <<
           \new DrumVoice { \voiceOne \drumbarshh }
            %\new DrumVoice { \voiceTwo \drumbars }
      >>



    %\new Staff {
    %  \rhythm
    %}

    \new Staff {
      \lead
    }


  >>

  \midi {}

}
