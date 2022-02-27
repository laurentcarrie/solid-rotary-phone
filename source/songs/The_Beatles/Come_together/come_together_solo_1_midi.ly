\version "2.22.0"

\include "base_solo_1.ly"

\score {

  <<

    \new DrumStaff {
      \tempo 4 = \song_tempo
      % why not \drums ?
      \drumbar
      \drumbar
      \drumbar
      \drumbar
      \drumbar
    }



    \new Staff {
      \rhythm
    }

    \new Staff {
      \lead
    }


  >>

  \midi {}

}
