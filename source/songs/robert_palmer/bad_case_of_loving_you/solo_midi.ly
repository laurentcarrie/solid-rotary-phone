\version "2.20.0"

\include "../../../macros/macros.ly"
\include "solo.ly"


    \score {
        \unfoldRepeats {
        <<
            \new DrumStaff
                \tempo 4 = \song_tempo
                <<
                    \new DrumVoice {  \drumbarshh }
                    \new DrumVoice {  \drumbars }
                >>

            %\new Staff {
            %      \rhythm
            %      \set Staff.midiMinimumVolume = #0.2
            %      \set Staff.midiMaximumVolume = #0.2
            %      %\set Staff.midiInstrument = "electric guitar (clean)"
            %      \set Staff.midiInstrument = "bass"
            %      %\set Staff.midiInstrument = "clarinet"
            %}
            \new Staff {
                  \lead
                  \set Staff.midiMinimumVolume = #0.9
                  \set Staff.midiMaximumVolume = #0.9
                  \set Staff.midiInstrument = "electric guitar (clean)"
            }
            %\new Staff {
            %      \song_voice
            %      \set Staff.midiMinimumVolume = #0.9
            %      \set Staff.midiMaximumVolume = #0.9
            %      \set Staff.midiInstrument = "electric guitar (clean)"
            %}
        >>
        }

       \midi {
            \tempo 4 = \song_tempo
      }
    }
