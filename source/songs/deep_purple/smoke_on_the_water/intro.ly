\version "2.22.1"

song_tempo = 114

% Bb
ma = {

}




rhythm = {

}

lead = {
  \absolute  {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0

    % mes 1
          < d\4 g\3 b\2 >8
          r8
          < f\4 bes\3 d'\2 >8
          r8
          < g\4 c'\3 e'\2 >4
          r8
          < d\4 g\3 b\2 >8
    |
    % mes2
          r8
          < f\4 bes\3 d'\2 >8
          r8
          < gis\4 cis'\3 eis'\2 >8
          < g\4 c'\3 e'\2 >4
          r4
    |
    % mes 3
          < d\4 g\3 b\2 >8
          r8
          < f\4 bes\3 d'\2 >8
          r8
          < g\4 c'\3 e'\2 >4
          r8
          < f\4 bes\3 d'\2 >8
    |
    % mes 4
          r8
          < d\4 g\3 b\2 >2
          r8
          r4
  }
}

drumbar =  \drummode {  bd4 sn4  bd4 sn4 }

drumbars = {
  \drumbar |   \drumbar |  \drumbar |  \drumbar |

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

drumbarshh = {
  \drumbarhh |  \drumbarhh |  \drumbarhh |  \drumbarhh |

}
